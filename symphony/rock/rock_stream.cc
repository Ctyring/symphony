#include "rock_stream.h"
#include "symphony/config.h"
#include "symphony/log.h"
#include "symphony/worker.h"

namespace symphony {

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");
static symphony::ConfigVar<
    std::unordered_map<std::string,
                       std::unordered_map<std::string, std::string> > >::ptr
    g_rock_services = symphony::Config::Lookup(
        "rock_services",
        std::unordered_map<std::string,
                           std::unordered_map<std::string, std::string> >(),
        "rock_services");

// static symphony::ConfigVar<std::unordered_map<std::string
//     ,std::unordered_map<std::string, std::string> > >::ptr g_rock_services =
//     symphony::Config::Lookup("rock_services", std::unordered_map<std::string
//     ,std::unordered_map<std::string, std::string> >(), "rock_services");

std::string RockResult::toString() const {
    std::stringstream ss;
    ss << "[RockResult result=" << result << " used=" << used
       << " response=" << (response ? response->toString() : "null")
       << " request=" << (request ? request->toString() : "null") << "]";
    return ss.str();
}

RockStream::RockStream(Socket::ptr sock)
    : AsyncSocketStream(sock, true), m_decoder(new RockMessageDecoder) {
    SYMPHONY_LOG_DEBUG(g_logger) << "RockStream::RockStream " << this << " "
                                 << (sock ? sock->toString() : "");
}

RockStream::~RockStream() {
    SYMPHONY_LOG_DEBUG(g_logger) << "RockStream::~RockStream " << this << " "
                                 << (m_socket ? m_socket->toString() : "");
}

int32_t RockStream::sendMessage(Message::ptr msg) {
    if (isConnected()) {
        RockSendCtx::ptr ctx(new RockSendCtx);
        ctx->msg = msg;
        enqueue(ctx);
        return 1;
    } else {
        return -1;
    }
}

RockResult::ptr RockStream::request(RockRequest::ptr req, uint32_t timeout_ms) {
    if (isConnected()) {
        RockCtx::ptr ctx(new RockCtx);
        ctx->request = req;
        ctx->sn = req->getSn();
        ctx->timeout = timeout_ms;
        ctx->scheduler = symphony::Scheduler::GetThis();
        ctx->fiber = symphony::Fiber::GetThis();
        addCtx(ctx);
        uint64_t ts = symphony::GetCurrentMS();
        ctx->timer = symphony::IOManager::GetThis()->addTimer(
            timeout_ms,
            std::bind(&RockStream::onTimeOut, shared_from_this(), ctx));
        enqueue(ctx);
        symphony::Fiber::YieldToHold();
        return std::make_shared<RockResult>(
            ctx->result, symphony::GetCurrentMS() - ts, ctx->response, req);
    } else {
        return std::make_shared<RockResult>(AsyncSocketStream::NOT_CONNECT, 0,
                                            nullptr, req);
    }
}

bool RockStream::RockSendCtx::doSend(AsyncSocketStream::ptr stream) {
    return std::dynamic_pointer_cast<RockStream>(stream)
               ->m_decoder->serializeTo(stream, msg) > 0;
}

bool RockStream::RockCtx::doSend(AsyncSocketStream::ptr stream) {
    return std::dynamic_pointer_cast<RockStream>(stream)
               ->m_decoder->serializeTo(stream, request) > 0;
}

AsyncSocketStream::Ctx::ptr RockStream::doRecv() {
    auto msg = m_decoder->parseFrom(shared_from_this());
    if (!msg) {
        innerClose();
        return nullptr;
    }

    int type = msg->getType();
    if (type == Message::RESPONSE) {
        auto rsp = std::dynamic_pointer_cast<RockResponse>(msg);
        if (!rsp) {
            SYMPHONY_LOG_WARN(g_logger)
                << "RockStream doRecv response not RockResponse: "
                << msg->toString();
            return nullptr;
        }
        RockCtx::ptr ctx = getAndDelCtxAs<RockCtx>(rsp->getSn());
        if (!ctx) {
            SYMPHONY_LOG_WARN(g_logger)
                << "RockStream request timeout reponse=" << rsp->toString();
            return nullptr;
        }
        ctx->result = rsp->getResult();
        ctx->response = rsp;
        return ctx;
    } else if (type == Message::REQUEST) {
        auto req = std::dynamic_pointer_cast<RockRequest>(msg);
        if (!req) {
            SYMPHONY_LOG_WARN(g_logger)
                << "RockStream doRecv request not RockRequest: "
                << msg->toString();
            return nullptr;
        }
        if (m_requestHandler) {
            m_worker->schedule(std::bind(
                &RockStream::handleRequest,
                std::dynamic_pointer_cast<RockStream>(shared_from_this()),
                req));
        } else {
            SYMPHONY_LOG_WARN(g_logger)
                << "unhandle request " << req->toString();
        }
    } else if (type == Message::NOTIFY) {
        auto nty = std::dynamic_pointer_cast<RockNotify>(msg);
        if (!nty) {
            SYMPHONY_LOG_WARN(g_logger)
                << "RockStream doRecv notify not RockNotify: "
                << msg->toString();
            return nullptr;
        }

        if (m_notifyHandler) {
            m_worker->schedule(std::bind(
                &RockStream::handleNotify,
                std::dynamic_pointer_cast<RockStream>(shared_from_this()),
                nty));
        } else {
            SYMPHONY_LOG_WARN(g_logger)
                << "unhandle notify " << nty->toString();
        }
    } else {
        SYMPHONY_LOG_WARN(g_logger) << "RockStream recv unknow type=" << type
                                    << " msg: " << msg->toString();
    }
    return nullptr;
}

void RockStream::handleRequest(symphony::RockRequest::ptr req) {
    symphony::RockResponse::ptr rsp = req->createResponse();
    if (!m_requestHandler(
            req, rsp,
            std::dynamic_pointer_cast<RockStream>(shared_from_this()))) {
        sendMessage(rsp);
        // innerClose();
        close();
    } else {
        SYMPHONY_LOG_DEBUG(g_logger) << "handleRequest requestHandler";
        sendMessage(rsp);
    }
}

void RockStream::handleNotify(symphony::RockNotify::ptr nty) {
    if (!m_notifyHandler(
            nty, std::dynamic_pointer_cast<RockStream>(shared_from_this()))) {
        // innerClose();
        close();
    }
}

RockSession::RockSession(Socket::ptr sock) : RockStream(sock) {
    m_autoConnect = false;
}

RockConnection::RockConnection() : RockStream(nullptr) {
    m_autoConnect = true;
}

bool RockConnection::connect(symphony::Address::ptr addr) {
    m_socket = symphony::Socket::CreateTCP(addr);
    return m_socket->connect(addr);
}

RockSDLoadBalance::RockSDLoadBalance(IServiceDiscovery::ptr sd)
    : SDLoadBalance(sd) {}

static SocketStream::ptr create_rock_stream(ServiceItemInfo::ptr info) {
    symphony::IPAddress::ptr addr =
        symphony::Address::LookupAnyIPAddress(info->getIp());
    if (!addr) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "invalid service info: " << info->toString();
        return nullptr;
    }
    addr->setPort(info->getPort());

    RockConnection::ptr conn(new RockConnection);

    symphony::WorkerMgr::GetInstance()->schedule("service_io", [conn, addr]() {
        conn->connect(addr);
        conn->start();
    });
    return conn;
}

void RockSDLoadBalance::start() {
    m_cb = create_rock_stream;
    initConf(g_rock_services->getValue());
    SDLoadBalance::start();
}

void RockSDLoadBalance::start(
    const std::unordered_map<std::string,
                             std::unordered_map<std::string, std::string> >&
        confs) {
    m_cb = create_rock_stream;
    initConf(confs);
    SDLoadBalance::start();
}

void RockSDLoadBalance::stop() {
    SDLoadBalance::stop();
}

RockResult::ptr RockSDLoadBalance::request(const std::string& domain,
                                           const std::string& service,
                                           RockRequest::ptr req,
                                           uint32_t timeout_ms,
                                           uint64_t idx) {
    auto lb = get(domain, service);
    if (!lb) {
        return std::make_shared<RockResult>(ILoadBalance::NO_SERVICE, 0,
                                            nullptr, req);
    }
    auto conn = lb->get(idx);
    if (!conn) {
        return std::make_shared<RockResult>(ILoadBalance::NO_CONNECTION, 0,
                                            nullptr, req);
    }
    uint64_t ts = symphony::GetCurrentMS();
    auto& stats = conn->get(ts / 1000);
    stats.incDoing(1);
    stats.incTotal(1);
    auto r = conn->getStreamAs<RockStream>()->request(req, timeout_ms);
    uint64_t ts2 = symphony::GetCurrentMS();
    if (r->result == 0) {
        stats.incOks(1);
        stats.incUsedTime(ts2 - ts);
    } else if (r->result == AsyncSocketStream::TIMEOUT) {
        stats.incTimeouts(1);
    } else if (r->result < 0) {
        stats.incErrs(1);
    }
    stats.decDoing(1);
    return r;
}

}  // namespace symphony