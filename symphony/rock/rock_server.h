#ifndef __SYMPHONY_ROCK_SERVER_H__
#define __SYMPHONY_ROCK_SERVER_H__

#include "symphony/rock/rock_stream.h"
#include "symphony/tcp_server.h"

namespace symphony {

class RockServer : public TcpServer {
   public:
    typedef std::shared_ptr<RockServer> ptr;
    RockServer(
        const std::string& type = "rock",
        symphony::IOManager* worker = symphony::IOManager::GetThis(),
        symphony::IOManager* io_worker = symphony::IOManager::GetThis(),
        symphony::IOManager* accept_worker = symphony::IOManager::GetThis());

   protected:
    virtual void handleClient(Socket::ptr client) override;
};

}  // namespace symphony

#endif