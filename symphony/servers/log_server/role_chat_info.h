#ifndef __SYMPHONY_LOGROLE_CHAT_INFO_H__
#define __SYMPHONY_LOGROLE_CHAT_INFO_H__

#include <json/json.h>
#include <vector>
#include "symphony/db/db.h"
#include "symphony/util.h"


namespace symphony {
namespace log {

class RoleChatInfoDao;
class RoleChatInfo {
friend class RoleChatInfoDao;
public:
    typedef std::shared_ptr<RoleChatInfo> ptr;

    RoleChatInfo();

    const int64_t& getRoleid() { return m_roleid; }
    void setRoleid(const int64_t& v);

    const int32_t& getLevel() { return m_level; }
    void setLevel(const int32_t& v);

    const std::string& getRolename() { return m_rolename; }
    void setRolename(const std::string& v);

    const int32_t& getViplevel() { return m_viplevel; }
    void setViplevel(const int32_t& v);

    const int32_t& getAreaid() { return m_areaid; }
    void setAreaid(const int32_t& v);

    const int32_t& getChannel() { return m_channel; }
    void setChannel(const int32_t& v);

    const std::string& getText() { return m_text; }
    void setText(const std::string& v);

    const int64_t& getOptime() { return m_optime; }
    void setOptime(const int64_t& v);

    const int64_t& getTargetid() { return m_targetid; }
    void setTargetid(const int64_t& v);

    const int32_t& getTargetvip() { return m_targetvip; }
    void setTargetvip(const int32_t& v);

    const std::string& getTargetname() { return m_targetname; }
    void setTargetname(const std::string& v);

    const int32_t& getChatchl() { return m_chatchl; }
    void setChatchl(const int32_t& v);

    std::string toJsonString() const;

private:
    int32_t m_level;
    int32_t m_viplevel;
    int32_t m_areaid;
    int32_t m_channel;
    int32_t m_targetvip;
    int32_t m_chatchl;
    int64_t m_roleid;
    int64_t m_targetid;
    std::string m_rolename;
    std::string m_text;
    std::string m_targetname;
    int64_t m_optime;
};


class RoleChatInfoDao {
public:
    typedef std::shared_ptr<RoleChatInfoDao> ptr;
    static int Update(RoleChatInfo::ptr info, symphony::IDB::ptr conn);
    static int Insert(RoleChatInfo::ptr info, symphony::IDB::ptr conn);
    static int InsertOrUpdate(RoleChatInfo::ptr info, symphony::IDB::ptr conn);
    static int Delete(RoleChatInfo::ptr info, symphony::IDB::ptr conn);
    static int Delete(symphony::IDB::ptr conn);
    static int QueryAll(std::vector<RoleChatInfo::ptr>& results, symphony::IDB::ptr conn);
    static RoleChatInfo::ptr Query(symphony::IDB::ptr conn);
    static int CreateTableSQLite3(symphony::IDB::ptr info);
    static int CreateTableMySQL(symphony::IDB::ptr info);
};

} //namespace log
} //namespace symphony
#endif //__SYMPHONY_LOGROLE_CHAT_INFO_H__
