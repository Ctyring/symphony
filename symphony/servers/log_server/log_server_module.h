#pragma once
#include "log_protobuf.pb.h"
#include "symphony/db/mysql.h"
#include "symphony/module.h"
namespace symphony {
namespace ls {
class LogServerModule : public RockModule {
   public:
    typedef std::shared_ptr<LogServerModule> ptr;
    LogServerModule();

    virtual bool handleRockRequest(symphony::RockRequest::ptr request,
                                   symphony::RockResponse::ptr response,
                                   symphony::RockStream::ptr stream) override;
    virtual bool handleRockNotify(symphony::RockNotify::ptr notify,
                                  symphony::RockStream::ptr stream) override;
    virtual bool onConnect(symphony::Stream::ptr stream) override;
    virtual bool onDisconnect(symphony::Stream::ptr stream) override;
    virtual std::string statusString() override;

   private:
    bool handleTick(symphony::RockRequest::ptr request,
                    symphony::RockResponse::ptr response,
                    symphony::RockStream::ptr stream);

    bool handleAccountCreate(symphony::RockRequest::ptr request,
                             symphony::RockResponse::ptr response,
                             symphony::RockStream::ptr stream);

    bool handleAccountLogin(symphony::RockRequest::ptr request,
                            symphony::RockResponse::ptr response,
                            symphony::RockStream::ptr stream);

   private:
    symphony::RWMutex m_mutex;
    symphony::IDB::ptr m_log_db;
};
}  // namespace ls
}  // namespace symphony