#ifndef __SYMPHONY_LOGROLE_CREATE_INFO_H__
#define __SYMPHONY_LOGROLE_CREATE_INFO_H__

#include <json/json.h>
#include <vector>
#include "symphony/db/db.h"
#include "symphony/util.h"


namespace symphony {
namespace log {

class RoleCreateInfoDao;
class RoleCreateInfo {
friend class RoleCreateInfoDao;
public:
    typedef std::shared_ptr<RoleCreateInfo> ptr;

    RoleCreateInfo();

    const int64_t& getRoleid() { return m_roleid; }
    void setRoleid(const int64_t& v);

    const int64_t& getAccountid() { return m_accountid; }
    void setAccountid(const int64_t& v);

    const int32_t& getAreaid() { return m_areaid; }
    void setAreaid(const int32_t& v);

    const int32_t& getChannel() { return m_channel; }
    void setChannel(const int32_t& v);

    const int64_t& getOptime() { return m_optime; }
    void setOptime(const int64_t& v);

    const std::string& getRolename() { return m_rolename; }
    void setRolename(const std::string& v);

    const std::string& getImodel() { return m_imodel; }
    void setImodel(const std::string& v);

    const std::string& getImei() { return m_imei; }
    void setImei(const std::string& v);

    const std::string& getIdfa() { return m_idfa; }
    void setIdfa(const std::string& v);

    const std::string& getUuid() { return m_uuid; }
    void setUuid(const std::string& v);

    std::string toJsonString() const;

private:
    int32_t m_areaid;
    int32_t m_channel;
    int64_t m_roleid;
    int64_t m_accountid;
    std::string m_rolename;
    std::string m_imodel;
    std::string m_imei;
    std::string m_idfa;
    std::string m_uuid;
    int64_t m_optime;
};


class RoleCreateInfoDao {
public:
    typedef std::shared_ptr<RoleCreateInfoDao> ptr;
    static int Update(RoleCreateInfo::ptr info, symphony::IDB::ptr conn);
    static int Insert(RoleCreateInfo::ptr info, symphony::IDB::ptr conn);
    static int InsertOrUpdate(RoleCreateInfo::ptr info, symphony::IDB::ptr conn);
    static int Delete(RoleCreateInfo::ptr info, symphony::IDB::ptr conn);
    static int Delete(symphony::IDB::ptr conn);
    static int DeleteByOptime( const int64_t& optime, symphony::IDB::ptr conn);
    static int QueryAll(std::vector<RoleCreateInfo::ptr>& results, symphony::IDB::ptr conn);
    static RoleCreateInfo::ptr Query(symphony::IDB::ptr conn);
    static int QueryByOptime(std::vector<RoleCreateInfo::ptr>& results,  const int64_t& optime, symphony::IDB::ptr conn);
    static int CreateTableSQLite3(symphony::IDB::ptr info);
    static int CreateTableMySQL(symphony::IDB::ptr info);
};

} //namespace log
} //namespace symphony
#endif //__SYMPHONY_LOGROLE_CREATE_INFO_H__
