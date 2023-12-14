#ifndef __SYMPHONY_NS_NS_CLIENT_H__
#define __SYMPHONY_NS_NS_CLIENT_H__

#include "ns_protocol.h"
#include "symphony/rock/rock_stream.h"

namespace symphony {
namespace ns {

class NSClient : public RockConnection {
   public:
    typedef std::shared_ptr<NSClient> ptr;
    NSClient();
    ~NSClient();

    const std::set<std::string>& getQueryDomains();
    void setQueryDomains(const std::set<std::string>& v);

    void addQueryDomain(const std::string& domain);
    void delQueryDomain(const std::string& domain);

    bool hasQueryDomain(const std::string& domain);

    RockResult::ptr query();

    void init();
    void uninit();
    NSDomainSet::ptr getDomains() const { return m_domains; }

   private:
    void onQueryDomainChange();
    bool onConnect(symphony::AsyncSocketStream::ptr stream);
    void onDisconnect(symphony::AsyncSocketStream::ptr stream);
    bool onNotify(symphony::RockNotify::ptr, symphony::RockStream::ptr);

    void onTimer();

   private:
    symphony::RWMutex m_mutex;
    std::set<std::string> m_queryDomains;
    NSDomainSet::ptr m_domains;
    uint32_t m_sn = 0;
    symphony::Timer::ptr m_timer;
};

}  // namespace ns
}  // namespace symphony

#endif