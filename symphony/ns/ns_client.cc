#include "ns_client.h"
#include "symphony/log.h"
#include "symphony/util.h"

namespace symphony {
namespace ns {

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");

NSClient::NSClient() {
    m_domains.reset(new symphony::ns::NSDomainSet);
}

NSClient::~NSClient() {
    SYMPHONY_LOG_DEBUG(g_logger) << "NSClient::~NSClient";
}

const std::set<std::string>& NSClient::getQueryDomains() {
    symphony::RWMutex::ReadLock lock(m_mutex);
    return m_queryDomains;
}

void NSClient::setQueryDomains(const std::set<std::string>& v) {
    symphony::RWMutex::WriteLock lock(m_mutex);
    m_queryDomains = v;
    lock.unlock();
    onQueryDomainChange();
}

void NSClient::addQueryDomain(const std::string& domain) {
    symphony::RWMutex::WriteLock lock(m_mutex);
    m_queryDomains.insert(domain);
    lock.unlock();
    onQueryDomainChange();
}

bool NSClient::hasQueryDomain(const std::string& domain) {
    symphony::RWMutex::ReadLock lock(m_mutex);
    return m_queryDomains.count(domain) > 0;
}

void NSClient::delQueryDomain(const std::string& domain) {
    symphony::RWMutex::WriteLock lock(m_mutex);
    m_queryDomains.erase(domain);
    lock.unlock();
    onQueryDomainChange();
}

RockResult::ptr NSClient::query() {
    symphony::RockRequest::ptr req = std::make_shared<symphony::RockRequest>();
    req->setSn(symphony::Atomic::addFetch(m_sn, 1));
    req->setCmd((int)NSCommand::QUERY);
    auto data = std::make_shared<symphony::ns::QueryRequest>();

    symphony::RWMutex::ReadLock lock(m_mutex);
    for (auto& i : m_queryDomains) {
        data->add_domains(i);
    }
    if (m_queryDomains.empty()) {
        return std::make_shared<RockResult>(0, 0, nullptr, nullptr);
    }
    lock.unlock();

    req->setAsPB(*data);
    auto rt = request(req, 1000);
    do {
        if (!rt->response) {
            SYMPHONY_LOG_ERROR(g_logger) << "query error result=" << rt->result;
            break;
        }
        auto rsp = rt->response->getAsPB<symphony::ns::QueryResponse>();
        if (!rsp) {
            SYMPHONY_LOG_ERROR(g_logger) << "invalid data not QueryResponse";
            break;
        }

        NSDomainSet::ptr domains(new NSDomainSet);
        for (auto& i : rsp->infos()) {
            if (!hasQueryDomain(i.domain())) {
                continue;
            }
            auto domain = domains->get(i.domain(), true);
            uint32_t cmd = i.cmd();

            for (auto& n : i.nodes()) {
                NSNode::ptr node(new NSNode(n.ip(), n.port(), n.weight()));
                if (!(node->getId() >> 32)) {
                    SYMPHONY_LOG_ERROR(g_logger)
                        << "invalid node: " << node->toString();
                    continue;
                }
                domain->add(cmd, node);
            }
        }
        m_domains->swap(*domains);
    } while (false);
    return rt;
}

void NSClient::onQueryDomainChange() {
    if (isConnected()) {
        query();
    }
}

void NSClient::init() {
    auto self = std::dynamic_pointer_cast<NSClient>(shared_from_this());
    setConnectCb(std::bind(&NSClient::onConnect, self, std::placeholders::_1));
    setDisconnectCb(
        std::bind(&NSClient::onDisconnect, self, std::placeholders::_1));
    setNotifyHandler(std::bind(&NSClient::onNotify, self, std::placeholders::_1,
                               std::placeholders::_2));
}

void NSClient::uninit() {
    setConnectCb(nullptr);
    setDisconnectCb(nullptr);
    setNotifyHandler(nullptr);

    if (m_timer) {
        m_timer->cancel();
    }
}

bool NSClient::onConnect(symphony::AsyncSocketStream::ptr stream) {
    if (m_timer) {
        m_timer->cancel();
    }
    auto self = std::dynamic_pointer_cast<NSClient>(shared_from_this());
    m_timer = m_iomanager->addTimer(30 * 1000,
                                    std::bind(&NSClient::onTimer, self), true);
    m_iomanager->schedule(std::bind(&NSClient::query, self));
    return true;
}

void NSClient::onTimer() {
    symphony::RockRequest::ptr req = std::make_shared<symphony::RockRequest>();
    req->setSn(symphony::Atomic::addFetch(m_sn, 1));
    req->setCmd((uint32_t)NSCommand::TICK);
    auto rt = request(req, 1000);
    if (!rt->response) {
        SYMPHONY_LOG_ERROR(g_logger) << "tick error result=" << rt->result;
    } else {
        SYMPHONY_LOG_DEBUG(g_logger) << "tick ok";
    }
    sleep(1000);
    query();
}

void NSClient::onDisconnect(symphony::AsyncSocketStream::ptr stream) {}

bool NSClient::onNotify(symphony::RockNotify::ptr nty,
                        symphony::RockStream::ptr stream) {
    do {
        if (nty->getNotify() == (uint32_t)NSNotify::NODE_CHANGE) {
            auto nm = nty->getAsPB<symphony::ns::NotifyMessage>();
            if (!nm) {
                SYMPHONY_LOG_ERROR(g_logger) << "invalid node_change data";
                break;
            }

            for (auto& i : nm->dels()) {
                if (!hasQueryDomain(i.domain())) {
                    continue;
                }
                auto domain = m_domains->get(i.domain());
                if (!domain) {
                    continue;
                }
                int cmd = i.cmd();
                for (auto& n : i.nodes()) {
                    NSNode::ptr node(new NSNode(n.ip(), n.port(), n.weight()));
                    domain->del(cmd, node->getId());
                }
            }

            for (auto& i : nm->updates()) {
                if (!hasQueryDomain(i.domain())) {
                    continue;
                }
                auto domain = m_domains->get(i.domain(), true);
                int cmd = i.cmd();
                for (auto& n : i.nodes()) {
                    NSNode::ptr node(new NSNode(n.ip(), n.port(), n.weight()));
                    if (node->getId() >> 32) {
                        domain->add(cmd, node);
                    } else {
                        SYMPHONY_LOG_ERROR(g_logger)
                            << "invalid node: " << node->toString();
                    }
                }
            }
        }
    } while (false);
    return true;
}

}  // namespace ns
}  // namespace symphony