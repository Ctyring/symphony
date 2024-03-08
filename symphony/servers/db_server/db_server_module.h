#pragma once
#include "symphony/db/mysql.h"
#include "symphony/module.h"
namespace symphony {
namespace db {
class DBServerModule : public RockModule {
   public:
    typedef std::shared_ptr<DBServerModule> ptr;
    DBServerModule();

    virtual bool handleRockRequest(symphony::RockRequest::ptr request,
                                   symphony::RockResponse::ptr response,
                                   symphony::RockStream::ptr stream) override;
    virtual bool handleRockNotify(symphony::RockNotify::ptr notify,
                                  symphony::RockStream::ptr stream) override;
    virtual bool onConnect(symphony::Stream::ptr stream) override;
    virtual bool onDisconnect(symphony::Stream::ptr stream) override;
    virtual std::string statusString() override;
};
}  // namespace db
}  // namespace symphony