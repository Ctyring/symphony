#ifndef __SYMPHONY_NS_NAME_SERVER_MODULE_H__
#define __SYMPHONY_NS_NAME_SERVER_MODULE_H__

#include "ns_protocol.h"
#include "symphony/module.h"

namespace symphony {
namespace ns {

class NameServerModule;
class NSClientInfo {
    friend class NameServerModule;

   public:
    typedef std::shared_ptr<NSClientInfo> ptr;

   private:
    NSNode::ptr m_node;
    std::map<std::string, std::set<uint32_t> > m_domain2cmds;
};

class NameServerModule : public RockModule {
   public:
    typedef std::shared_ptr<NameServerModule> ptr;
    NameServerModule();

    virtual bool handleRockRequest(symphony::RockRequest::ptr request,
                                   symphony::RockResponse::ptr response,
                                   symphony::RockStream::ptr stream) override;
    virtual bool handleRockNotify(symphony::RockNotify::ptr notify,
                                  symphony::RockStream::ptr stream) override;
    virtual bool onConnect(symphony::Stream::ptr stream) override;
    virtual bool onDisconnect(symphony::Stream::ptr stream) override;
    virtual std::string statusString() override;

   private:
    bool handleRegister(symphony::RockRequest::ptr request,
                        symphony::RockResponse::ptr response,
                        symphony::RockStream::ptr stream);
    bool handleQuery(symphony::RockRequest::ptr request,
                     symphony::RockResponse::ptr response,
                     symphony::RockStream::ptr stream);
    bool handleTick(symphony::RockRequest::ptr request,
                    symphony::RockResponse::ptr response,
                    symphony::RockStream::ptr stream);

   private:
    NSClientInfo::ptr get(symphony::RockStream::ptr rs);
    void set(symphony::RockStream::ptr rs, NSClientInfo::ptr info);

    void setQueryDomain(symphony::RockStream::ptr rs,
                        const std::set<std::string>& ds);

    void doNotify(std::set<std::string>& domains,
                  std::shared_ptr<NotifyMessage> nty);

    std::set<symphony::RockStream::ptr> getStreams(const std::string& domain);

   private:
    NSDomainSet::ptr m_domains;

    symphony::RWMutex m_mutex;
    std::map<symphony::RockStream::ptr, NSClientInfo::ptr> m_sessions;

    /// sessoin 关注的域名
    std::map<symphony::RockStream::ptr, std::set<std::string> > m_queryDomains;
    /// 域名对应关注的session
    std::map<std::string, std::set<symphony::RockStream::ptr> >
        m_domainToSessions;
};

}  // namespace ns
}  // namespace symphony

#endif