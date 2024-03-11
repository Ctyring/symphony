#pragma once
#include "symphony/module.h"
namespace symphony {
namespace cs {
class CenterServerModule : public RockModule {
   public:
    typedef std::shared_ptr<CenterServerModule> ptr;

    CenterServerModule();

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
    bool handleMsgLogicSvrRegReq(symphony::RockRequest::ptr request,
                                 symphony::RockResponse::ptr response,
                                 symphony::RockStream::ptr stream);
};
}  // namespace cs
}  // namespace symphony
