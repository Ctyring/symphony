#pragma once
#include "symphony/db/mysql.h"
#include "symphony/module.h"
#include "symphony/servers/login_server/logic_svr_manager.h"
namespace symphony {
namespace los {
class LoginServerModule : public RockModule {
   public:
    typedef std::shared_ptr<LoginServerModule> ptr;
    LoginServerModule();

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
    bool handleMsgCheckVersionReq(symphony::RockRequest::ptr request,
                                  symphony::RockResponse::ptr response,
                                  symphony::RockStream::ptr stream);
    bool handleMsgAccountRegReq(symphony::RockRequest::ptr request,
                                symphony::RockResponse::ptr response,
                                symphony::RockStream::ptr stream);
    bool handleMsgAccountLoginReq(symphony::RockRequest::ptr request,
                                  symphony::RockResponse::ptr response,
                                  symphony::RockStream::ptr stream);
    bool handleMsgServerListReq(symphony::RockRequest::ptr request,
                                symphony::RockResponse::ptr response,
                                symphony::RockStream::ptr stream);
    bool handleMsgSelectServerReq(symphony::RockRequest::ptr request,
                                  symphony::RockResponse::ptr response,
                                  symphony::RockStream::ptr stream);
    bool handleMsgAccountRegAck(symphony::RockRequest::ptr request,
                                symphony::RockResponse::ptr response,
                                symphony::RockStream::ptr stream);
    bool handleMsgAccountLoginAck(symphony::RockRequest::ptr request,
                                  symphony::RockResponse::ptr response,
                                  symphony::RockStream::ptr stream);
    bool handleMsgLogicSvrRegReq(symphony::RockRequest::ptr request,
                                 symphony::RockResponse::ptr response,
                                 symphony::RockStream::ptr stream);
    bool handleMsgLogicUpdateReq(symphony::RockRequest::ptr request,
                                 symphony::RockResponse::ptr response,
                                 symphony::RockStream::ptr stream);
    bool handleMsgSelectServerAck(symphony::RockRequest::ptr request,
                                  symphony::RockResponse::ptr response,
                                  symphony::RockStream::ptr stream);
    bool handleMsgSealAccountAck(symphony::RockRequest::ptr request,
                                 symphony::RockResponse::ptr response,
                                 symphony::RockStream::ptr stream);
    bool handleMsgGameParamReq(symphony::RockRequest::ptr request,
                               symphony::RockResponse::ptr response,
                               symphony::RockStream::ptr stream);

   private:
    LogicSvrManager m_LogicSvrMgr;
};
}  // namespace los
}  // namespace symphony