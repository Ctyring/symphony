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
    bool handleTick(symphony::RockRequest::ptr request,
                    symphony::RockResponse::ptr response,
                    symphony::RockStream::ptr stream);

    bool handleAccountCreate(symphony::RockRequest::ptr request,
                             symphony::RockResponse::ptr response,
                             symphony::RockStream::ptr stream);

    bool handleAccountLogin(symphony::RockRequest::ptr request,
                            symphony::RockResponse::ptr response,
                            symphony::RockStream::ptr stream);

    bool handleRoleCreate(symphony::RockRequest::ptr request,
                          symphony::RockResponse::ptr response,
                          symphony::RockStream::ptr stream);

    bool handleRoleLogin(symphony::RockRequest::ptr request,
                         symphony::RockResponse::ptr response,
                         symphony::RockStream::ptr stream);

    bool handleRoleLogout(symphony::RockRequest::ptr request,
                          symphony::RockResponse::ptr response,
                          symphony::RockStream::ptr stream);

    bool handleRoleChat(symphony::RockRequest::ptr request,
                        symphony::RockResponse::ptr response,
                        symphony::RockStream::ptr stream);
    void onTimer();

   private:
    std::uint64_t m_write_cnt = 0;
    std::uint64_t m_last_write_time = 0;
    symphony::RWMutex m_mutex;
    symphony::MySQL::ptr m_log_db;
    symphony::Timer::ptr m_timer;
};
}  // namespace ls
}  // namespace symphony