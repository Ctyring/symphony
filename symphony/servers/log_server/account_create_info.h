#ifndef __SYMPHONY_LOGACCOUNT_CREATE_INFO_H__
#define __SYMPHONY_LOGACCOUNT_CREATE_INFO_H__

#include <json/json.h>
#include <vector>
#include "symphony/db/db.h"
#include "symphony/util.h"


namespace symphony {
namespace log {

class AccountCreateInfoDao;
class AccountCreateInfo {
friend class AccountCreateInfoDao;
public:
    typedef std::shared_ptr<AccountCreateInfo> ptr;

    AccountCreateInfo();

    const int64_t& getAccountid() { return m_accountid; }
    void setAccountid(const int64_t& v);

    const int32_t& getVersion() { return m_version; }
    void setVersion(const int32_t& v);

    const int32_t& getChannel() { return m_channel; }
    void setChannel(const int32_t& v);

    const int64_t& getOptime() { return m_optime; }
    void setOptime(const int64_t& v);

    const std::string& getImodel() { return m_imodel; }
    void setImodel(const std::string& v);

    const std::string& getImei() { return m_imei; }
    void setImei(const std::string& v);

    const std::string& getIp() { return m_ip; }
    void setIp(const std::string& v);

    const std::string& getOpenid() { return m_openid; }
    void setOpenid(const std::string& v);

    const std::string& getIdfa() { return m_idfa; }
    void setIdfa(const std::string& v);

    const std::string& getUuid() { return m_uuid; }
    void setUuid(const std::string& v);

    std::string toJsonString() const;

private:
    int32_t m_version;
    int32_t m_channel;
    int64_t m_accountid;
    std::string m_imodel;
    std::string m_imei;
    std::string m_ip;
    std::string m_openid;
    std::string m_idfa;
    std::string m_uuid;
    int64_t m_optime;
};


class AccountCreateInfoDao {
public:
    typedef std::shared_ptr<AccountCreateInfoDao> ptr;
    static int Update(AccountCreateInfo::ptr info, symphony::IDB::ptr conn);
    static int Insert(AccountCreateInfo::ptr info, symphony::IDB::ptr conn);
    static int InsertOrUpdate(AccountCreateInfo::ptr info, symphony::IDB::ptr conn);
    static int Delete(AccountCreateInfo::ptr info, symphony::IDB::ptr conn);
    static int Delete(symphony::IDB::ptr conn);
    static int DeleteByOptime( const int64_t& optime, symphony::IDB::ptr conn);
    static int QueryAll(std::vector<AccountCreateInfo::ptr>& results, symphony::IDB::ptr conn);
    static AccountCreateInfo::ptr Query(symphony::IDB::ptr conn);
    static int QueryByOptime(std::vector<AccountCreateInfo::ptr>& results,  const int64_t& optime, symphony::IDB::ptr conn);
    static int CreateTableSQLite3(symphony::IDB::ptr info);
    static int CreateTableMySQL(symphony::IDB::ptr info);
};

} //namespace log
} //namespace symphony
#endif //__SYMPHONY_LOGACCOUNT_CREATE_INFO_H__
