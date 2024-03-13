#pragma once
#include "symphony/log.h"
#include "symphony/module.h"
namespace symphony {
namespace lcs {

class LogicServerModule : public RockModule {
   public:
    typedef std::shared_ptr<LogicServerModule> ptr;
    LogicServerModule();

    bool onServerReady() override;
    virtual bool handleRockRequest(symphony::RockRequest::ptr request,
                                   symphony::RockResponse::ptr response,
                                   symphony::RockStream::ptr stream);
    virtual bool handleRockNotify(symphony::RockNotify::ptr notify,
                                  symphony::RockStream::ptr stream) override;
    virtual bool onConnect(symphony::Stream::ptr stream) override;
    virtual bool onDisconnect(symphony::Stream::ptr stream) override;
    virtual std::string statusString() override;

   private:
    bool handleMsgSelectServerReq(symphony::RockRequest::ptr request,
                                  symphony::RockResponse::ptr response,
                                  symphony::RockStream::ptr stream);
    bool handleMsgRoleListReq(symphony::RockRequest::ptr request,
                              symphony::RockResponse::ptr response,
                              symphony::RockStream::ptr stream);
    bool handleMsgRoleListAck(symphony::RockRequest::ptr request,
                              symphony::RockResponse::ptr response,
                              symphony::RockStream::ptr stream);
    bool handleMsgRoleCreateReq(symphony::RockRequest::ptr request,
                                symphony::RockResponse::ptr response,
                                symphony::RockStream::ptr stream);
    bool handleMsgRoleDeleteReq(symphony::RockRequest::ptr request,
                                symphony::RockResponse::ptr response,
                                symphony::RockStream::ptr stream);
    bool handleMsgRoleLoginReq(symphony::RockRequest::ptr request,
                               symphony::RockResponse::ptr response,
                               symphony::RockStream::ptr stream);
    bool handleMsgRoleLoginAck(symphony::RockRequest::ptr request,
                               symphony::RockResponse::ptr response,
                               symphony::RockStream::ptr stream);
    bool handleMsgRoleLogoutReq(symphony::RockRequest::ptr request,
                                symphony::RockResponse::ptr response,
                                symphony::RockStream::ptr stream);
    bool handleMsgRoleDisconnect(symphony::RockRequest::ptr request,
                                 symphony::RockResponse::ptr response,
                                 symphony::RockStream::ptr stream);
    bool handleMsgAbortSceneNtf(symphony::RockRequest::ptr request,
                                symphony::RockResponse::ptr response,
                                symphony::RockStream::ptr stream);
    bool handleMsgMainCopyReq(symphony::RockRequest::ptr request,
                              symphony::RockResponse::ptr response,
                              symphony::RockStream::ptr stream);
    bool handleMsgBackToCityReq(symphony::RockRequest::ptr request,
                                symphony::RockResponse::ptr response,
                                symphony::RockStream::ptr stream);
    bool handleMsgChatMessageReq(symphony::RockRequest::ptr request,
                                 symphony::RockResponse::ptr response,
                                 symphony::RockStream::ptr stream);
    bool handleMsgReconnectReq(symphony::RockRequest::ptr request,
                               symphony::RockResponse::ptr response,
                               symphony::RockStream::ptr stream);
    bool handleMsgSealAccountNtf(symphony::RockRequest::ptr request,
                                 symphony::RockResponse::ptr response,
                                 symphony::RockStream::ptr stream);
};
}  // namespace lcs
}  // namespace symphony