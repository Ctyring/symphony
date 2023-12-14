#include "rock_server.h"
#include "symphony/log.h"
#include "symphony/module.h"

namespace symphony {

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");

RockServer::RockServer(const std::string& type,
                       symphony::IOManager* worker,
                       symphony::IOManager* io_worker,
                       symphony::IOManager* accept_worker)
    : TcpServer(worker, io_worker, accept_worker) {
    m_type = type;
}

void RockServer::handleClient(Socket::ptr client) {
    SYMPHONY_LOG_DEBUG(g_logger) << "handleClient " << *client;
    symphony::RockSession::ptr session(new symphony::RockSession(client));
    session->setWorker(m_worker);
    ModuleMgr::GetInstance()->foreach (
        Module::ROCK, [session](Module::ptr m) { m->onConnect(session); });
    session->setDisconnectCb([](AsyncSocketStream::ptr stream) {
        ModuleMgr::GetInstance()->foreach (
            Module::ROCK, [stream](Module::ptr m) { m->onDisconnect(stream); });
    });
    session->setRequestHandler([](symphony::RockRequest::ptr req,
                                  symphony::RockResponse::ptr rsp,
                                  symphony::RockStream::ptr conn) -> bool {
        // SYMPHONY_LOG_INFO(g_logger)
        //     << "handleReq " << req->toString() << " body=" << req->getBody();
        bool rt = false;
        ModuleMgr::GetInstance()->foreach (
            Module::ROCK, [&rt, req, rsp, conn](Module::ptr m) {
                if (rt) {
                    return;
                }
                rt = m->handleRequest(req, rsp, conn);
            });
        return rt;
    });
    session->setNotifyHandler([](symphony::RockNotify::ptr nty,
                                 symphony::RockStream::ptr conn) -> bool {
        SYMPHONY_LOG_INFO(g_logger)
            << "handleNty " << nty->toString() << " body=" << nty->getBody();
        bool rt = false;
        ModuleMgr::GetInstance()->foreach (Module::ROCK,
                                           [&rt, nty, conn](Module::ptr m) {
                                               if (rt) {
                                                   return;
                                               }
                                               rt = m->handleNotify(nty, conn);
                                           });
        return rt;
    });
    session->start();
}

}  // namespace symphony