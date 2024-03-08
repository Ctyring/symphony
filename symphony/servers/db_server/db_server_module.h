#pragma once
#include "symphony/db/mysql.h"
#include "symphony/module.h"
namespace symphony {
namespace db {
class DBServerModule : public RockModule {
   public:
    typedef std::shared_ptr<DBServerModule> ptr;
    DBServerModule();
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
    bool handleMsgRoleListReq(symphony::RockRequest::ptr request,
                              symphony::RockResponse::ptr response,
                              symphony::RockStream::ptr stream);
    bool handleMsgRoleLoginReq(symphony::RockRequest::ptr request,
                               symphony::RockResponse::ptr response,
                               symphony::RockStream::ptr stream);
    bool handleMsgRoleDeleteReq(symphony::RockRequest::ptr request,
                                symphony::RockResponse::ptr response,
                                symphony::RockStream::ptr stream);
    bool handleMsgExeSqlReq(symphony::RockRequest::ptr request,
                            symphony::RockResponse::ptr response,
                            symphony::RockStream::ptr stream);
    bool handleMsgLogicSvrRegReq(symphony::RockRequest::ptr request,
                                 symphony::RockResponse::ptr response,
                                 symphony::RockStream::ptr stream);
};
}  // namespace db
}  // namespace symphony