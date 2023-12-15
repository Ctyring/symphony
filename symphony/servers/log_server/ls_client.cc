#include "ls_client.h"
#include "log_server_protocol.h"

namespace symphony {
namespace ls {
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");

LSClient::LSClient() {}

LSClient::~LSClient() {
    SYMPHONY_LOG_DEBUG(g_logger) << "NSClient::~NSClient";
}

void LSClient::init() {
    auto self = std::dynamic_pointer_cast<LSClient>(shared_from_this());
    setConnectCb(std::bind(&LSClient::onConnect, self, std::placeholders::_1));
    setDisconnectCb(
        std::bind(&LSClient::onDisconnect, self, std::placeholders::_1));
    setNotifyHandler(std::bind(&LSClient::onNotify, self, std::placeholders::_1,
                               std::placeholders::_2));
}

bool LSClient::onConnect(symphony::AsyncSocketStream::ptr stream) {
    if (m_timer) {
        m_timer->cancel();
    }
    auto self = std::dynamic_pointer_cast<LSClient>(shared_from_this());
    m_timer = m_iomanager->addTimer(30 * 1000,
                                    std::bind(&LSClient::onTimer, self), true);
    // m_iomanager->schedule(std::bind(&LSClient::query, self));
    return true;
}

void LSClient::onTimer() {
    symphony::RockRequest::ptr req = std::make_shared<symphony::RockRequest>();
    req->setSn(symphony::Atomic::addFetch(m_sn, 1));
    req->setCmd((uint32_t)LSCommand::TICK);
    auto rt = request(req, 1000);
    if (!rt->response) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "tick error result=" << rt->result
            << " ip: " + m_socket->getRemoteAddress()->toString();
    } else {
        SYMPHONY_LOG_DEBUG(g_logger) << "tick ok";
    }
    sleep(1000);
}

void LSClient::onDisconnect(symphony::AsyncSocketStream::ptr stream) {}

bool LSClient::onNotify(symphony::RockNotify::ptr nty,
                        symphony::RockStream::ptr stream) {
    return false;
}
}  // namespace ls
}  // namespace symphony