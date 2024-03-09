#pragma once
#include "account_manager.h"
#include "symphony/module.h"
namespace symphony {
namespace as {
class AccountServerModule : public RockModule {
   public:
    typedef std::shared_ptr<AccountServerModule> ptr;
    AccountServerModule();

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
    bool handleMsgAccountRegReq(symphony::RockRequest::ptr request,
                                symphony::RockResponse::ptr response,
                                symphony::RockStream::ptr stream);
    bool handleMsgAccountLoginReq(symphony::RockRequest::ptr request,
                                  symphony::RockResponse::ptr response,
                                  symphony::RockStream::ptr stream);
    bool handleMsgSealAccountReq(symphony::RockRequest::ptr request,
                                 symphony::RockResponse::ptr response,
                                 symphony::RockStream::ptr stream);
    bool handleMsgSetLastServerNty(symphony::RockRequest::ptr request,
                                   symphony::RockResponse::ptr response,
                                   symphony::RockStream::ptr stream);

   public:
    CAccountObjectMgr m_AccountManager;
};
}  // namespace as

}  // namespace symphony
