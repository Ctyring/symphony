#pragma once
#include "symphony/db/mysql.h"
#include "symphony/module.h"
namespace symphony {
namespace ps {
class ProxyServerModule : public RockModule {
   public:
    typedef std::shared_ptr<ProxyServerModule> ptr;
    ProxyServerModule();

    bool onServerReady() override;
    virtual bool handleRockRequest(symphony::RockRequest::ptr request,
                                   symphony::RockResponse::ptr response,
                                   symphony::RockStream::ptr stream) override;
    virtual bool handleRockNotify(symphony::RockNotify::ptr notify,
                                  symphony::RockStream::ptr stream) override;
    virtual bool onConnect(symphony::Stream::ptr stream) override;
    virtual bool onDisconnect(symphony::Stream::ptr stream) override;
    virtual std::string statusString() override;

   private:
    void onTimer();
    bool handleMsgGameSvrRegister(symphony::RockRequest::ptr request,
                                  symphony::RockResponse::ptr response,
                                  symphony::RockStream::ptr stream);
    bool handleMsgBroadMessageNty(symphony::RockRequest::ptr request,
                                  symphony::RockResponse::ptr response,
                                  symphony::RockStream::ptr stream);
    bool handleMsgNotifyIntoSceneNtf(symphony::RockRequest::ptr request,
                                     symphony::RockResponse::ptr response,
                                     symphony::RockStream::ptr stream);
    bool handleMsgEnterSceneReq(symphony::RockRequest::ptr request,
                                symphony::RockResponse::ptr response,
                                symphony::RockStream::ptr stream);
    bool handleMsgRoleLoginAck(symphony::RockRequest::ptr request,
                               symphony::RockResponse::ptr response,
                               symphony::RockStream::ptr stream);
    bool handleMsgRoleLogoutReq(symphony::RockRequest::ptr request,
                                symphony::RockResponse::ptr response,
                                symphony::RockStream::ptr stream);
    bool handleMsgKickoutNty(symphony::RockRequest::ptr request,
                             symphony::RockResponse::ptr response,
                             symphony::RockStream::ptr stream);
    bool handleMsgRemoveConnectNty(symphony::RockRequest::ptr request,
                                   symphony::RockResponse::ptr response,
                                   symphony::RockStream::ptr stream);
    bool handleMsgRelayToLogic(symphony::RockRequest::ptr request,
                               symphony::RockResponse::ptr response,
                               symphony::RockStream::ptr stream);
    bool handleMsgReconnectReq(symphony::RockRequest::ptr request,
                               symphony::RockResponse::ptr response,
                               symphony::RockStream::ptr stream);
    bool handleMsgReconnectAck(symphony::RockRequest::ptr request,
                               symphony::RockResponse::ptr response,
                               symphony::RockStream::ptr stream);

   private:
};
}  // namespace ps
}  // namespace symphony