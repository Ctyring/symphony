#pragma once
#include "symphony/tcp_server.h"
#include "ws_servlet.h"
#include "ws_session.h"

namespace symphony {
namespace http {

class WSServer : public TcpServer {
   public:
    typedef std::shared_ptr<WSServer> ptr;

    WSServer(
        symphony::IOManager* worker = symphony::IOManager::GetThis(),
        symphony::IOManager* io_worker = symphony::IOManager::GetThis(),
        symphony::IOManager* accept_worker = symphony::IOManager::GetThis());

    WSServletDispatch::ptr getWSServletDispatch() const { return m_dispatch; }
    void setWSServletDispatch(WSServletDispatch::ptr v) { m_dispatch = v; }

   protected:
    virtual void handleClient(Socket::ptr client) override;

   protected:
    WSServletDispatch::ptr m_dispatch;
};

}  // namespace http
}  // namespace symphony