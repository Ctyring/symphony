#ifndef __SYMPHONY_LOGROLE_LOGOUT_INFO_H__
#define __SYMPHONY_LOGROLE_LOGOUT_INFO_H__

#include <json/json.h>
#include <vector>
#include "symphony/db/db.h"
#include "symphony/util.h"


namespace symphony {
namespace log {

class RoleLogoutInfoDao;
class RoleLogoutInfo {
friend class RoleLogoutInfoDao;
public:
    typedef std::shared_ptr<RoleLogoutInfo> ptr;

    RoleLogoutInfo();

    const int64_t& getRoleid() { return m_roleid; }
    void setRoleid(const int64_t& v);

    const int64_t& getAccountid() { return m_accountid; }
    void setAccountid(const int64_t& v);

    const int32_t& getChannel() { return m_channel; }
    void setChannel(const int32_t& v);

    const int32_t& getLevel() { return m_level; }
    void setLevel(const int32_t& v);

    const int32_t& getViplevel() { return m_viplevel; }
    void setViplevel(const int32_t& v);

    const int64_t& getOptime() { return m_optime; }
    void setOptime(const int64_t& v);

    const int32_t& getAreaid() { return m_areaid; }
    void setAreaid(const int32_t& v);

    const std::string& getRolename() { return m_rolename; }
    void setRolename(const std::string& v);

    const std::string& getIdfa() { return m_idfa; }
    void setIdfa(const std::string& v);

    const std::string& getImei() { return m_imei; }
    void setImei(const std::string& v);

    const std::string& getImodel() { return m_imodel; }
    void setImodel(const std::string& v);

    std::string toJsonString() const;

private:
    int32_t m_channel;
    int32_t m_level;
    int32_t m_viplevel;
    int32_t m_areaid;
    int64_t m_roleid;
    int64_t m_accountid;
    std::string m_rolename;
    std::string m_idfa;
    std::string m_imei;
    std::string m_imodel;
    int64_t m_optime;
};


class RoleLogoutInfoDao {
public:
    typedef std::shared_ptr<RoleLogoutInfoDao> ptr;
    static int Update(RoleLogoutInfo::ptr info, symphony::IDB::ptr conn);
    static int Insert(RoleLogoutInfo::ptr info, symphony::IDB::ptr conn);
    static int InsertOrUpdate(RoleLogoutInfo::ptr info, symphony::IDB::ptr conn);
    static int Delete(RoleLogoutInfo::ptr info, symphony::IDB::ptr conn);
    static int Delete(symphony::IDB::ptr conn);
    static int QueryAll(std::vector<RoleLogoutInfo::ptr>& results, symphony::IDB::ptr conn);
    static RoleLogoutInfo::ptr Query(symphony::IDB::ptr conn);
    static int CreateTableSQLite3(symphony::IDB::ptr info);
    static int CreateTableMySQL(symphony::IDB::ptr info);
};

} //namespace log
} //namespace symphony
#endif //__SYMPHONY_LOGROLE_LOGOUT_INFO_H__
