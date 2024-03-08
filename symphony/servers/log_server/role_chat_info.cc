#include "role_chat_info.h"
#include "symphony/log.h"

namespace symphony {
namespace log {

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("orm");

RoleChatInfo::RoleChatInfo()
    :m_level()
    ,m_viplevel()
    ,m_areaid()
    ,m_channel()
    ,m_targetvip()
    ,m_chatchl()
    ,m_roleid()
    ,m_targetid()
    ,m_rolename()
    ,m_text()
    ,m_targetname()
    ,m_optime() {
}

std::string RoleChatInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["roleid"] = std::to_string(m_roleid);
    jvalue["level"] = m_level;
    jvalue["rolename"] = m_rolename;
    jvalue["viplevel"] = m_viplevel;
    jvalue["areaid"] = m_areaid;
    jvalue["channel"] = m_channel;
    jvalue["text"] = m_text;
    jvalue["optime"] = symphony::Time2Str(m_optime);
    jvalue["targetid"] = std::to_string(m_targetid);
    jvalue["targetvip"] = m_targetvip;
    jvalue["targetname"] = m_targetname;
    jvalue["chatchl"] = m_chatchl;
    return symphony::JsonUtil::ToString(jvalue);
}

void RoleChatInfo::setRoleid(const int64_t& v) {
    m_roleid = v;
}

void RoleChatInfo::setLevel(const int32_t& v) {
    m_level = v;
}

void RoleChatInfo::setRolename(const std::string& v) {
    m_rolename = v;
}

void RoleChatInfo::setViplevel(const int32_t& v) {
    m_viplevel = v;
}

void RoleChatInfo::setAreaid(const int32_t& v) {
    m_areaid = v;
}

void RoleChatInfo::setChannel(const int32_t& v) {
    m_channel = v;
}

void RoleChatInfo::setText(const std::string& v) {
    m_text = v;
}

void RoleChatInfo::setOptime(const int64_t& v) {
    m_optime = v;
}

void RoleChatInfo::setTargetid(const int64_t& v) {
    m_targetid = v;
}

void RoleChatInfo::setTargetvip(const int32_t& v) {
    m_targetvip = v;
}

void RoleChatInfo::setTargetname(const std::string& v) {
    m_targetname = v;
}

void RoleChatInfo::setChatchl(const int32_t& v) {
    m_chatchl = v;
}


int RoleChatInfoDao::Update(RoleChatInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "update role_chat set roleid = ?, level = ?, rolename = ?, viplevel = ?, areaid = ?, channel = ?, text = ?, optime = ?, targetid = ?, targetvip = ?, targetname = ?, chatchl = ? where";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_roleid);
    stmt->bindInt32(2, info->m_level);
    stmt->bindString(3, info->m_rolename);
    stmt->bindInt32(4, info->m_viplevel);
    stmt->bindInt32(5, info->m_areaid);
    stmt->bindInt32(6, info->m_channel);
    stmt->bindString(7, info->m_text);
    stmt->bindTime(8, info->m_optime);
    stmt->bindInt64(9, info->m_targetid);
    stmt->bindInt32(10, info->m_targetvip);
    stmt->bindString(11, info->m_targetname);
    stmt->bindInt32(12, info->m_chatchl);
    return stmt->execute();
}

int RoleChatInfoDao::Insert(RoleChatInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "insert into role_chat (roleid, level, rolename, viplevel, areaid, channel, text, optime, targetid, targetvip, targetname, chatchl) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_roleid);
    stmt->bindInt32(2, info->m_level);
    stmt->bindString(3, info->m_rolename);
    stmt->bindInt32(4, info->m_viplevel);
    stmt->bindInt32(5, info->m_areaid);
    stmt->bindInt32(6, info->m_channel);
    stmt->bindString(7, info->m_text);
    stmt->bindTime(8, info->m_optime);
    stmt->bindInt64(9, info->m_targetid);
    stmt->bindInt32(10, info->m_targetvip);
    stmt->bindString(11, info->m_targetname);
    stmt->bindInt32(12, info->m_chatchl);
    int rt = stmt->execute();
    return rt;
}

int RoleChatInfoDao::InsertOrUpdate(RoleChatInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "replace into role_chat (roleid, level, rolename, viplevel, areaid, channel, text, optime, targetid, targetvip, targetname, chatchl) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_roleid);
    stmt->bindInt32(2, info->m_level);
    stmt->bindString(3, info->m_rolename);
    stmt->bindInt32(4, info->m_viplevel);
    stmt->bindInt32(5, info->m_areaid);
    stmt->bindInt32(6, info->m_channel);
    stmt->bindString(7, info->m_text);
    stmt->bindTime(8, info->m_optime);
    stmt->bindInt64(9, info->m_targetid);
    stmt->bindInt32(10, info->m_targetvip);
    stmt->bindString(11, info->m_targetname);
    stmt->bindInt32(12, info->m_chatchl);
    return stmt->execute();
}

int RoleChatInfoDao::Delete(RoleChatInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "delete from role_chat where";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    return stmt->execute();
}

int RoleChatInfoDao::QueryAll(std::vector<RoleChatInfo::ptr>& results, symphony::IDB::ptr conn) {
    std::string sql = "select roleid, level, rolename, viplevel, areaid, channel, text, optime, targetid, targetvip, targetname, chatchl from role_chat";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    auto rt = stmt->query();
    if(!rt) {
        return stmt->getErrno();
    }
    while (rt->next()) {
        RoleChatInfo::ptr v(new RoleChatInfo);
        v->m_roleid = rt->getInt64(0);
        v->m_level = rt->getInt32(1);
        v->m_rolename = rt->getString(2);
        v->m_viplevel = rt->getInt32(3);
        v->m_areaid = rt->getInt32(4);
        v->m_channel = rt->getInt32(5);
        v->m_text = rt->getString(6);
        v->m_optime = rt->getTime(7);
        v->m_targetid = rt->getInt64(8);
        v->m_targetvip = rt->getInt32(9);
        v->m_targetname = rt->getString(10);
        v->m_chatchl = rt->getInt32(11);
        results.push_back(v);
    }
    return 0;
}

RoleChatInfo::ptr RoleChatInfoDao::Query(symphony::IDB::ptr conn) {
    std::string sql = "select roleid, level, rolename, viplevel, areaid, channel, text, optime, targetid, targetvip, targetname, chatchl from role_chat where";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    RoleChatInfo::ptr v(new RoleChatInfo);
    v->m_roleid = rt->getInt64(0);
    v->m_level = rt->getInt32(1);
    v->m_rolename = rt->getString(2);
    v->m_viplevel = rt->getInt32(3);
    v->m_areaid = rt->getInt32(4);
    v->m_channel = rt->getInt32(5);
    v->m_text = rt->getString(6);
    v->m_optime = rt->getTime(7);
    v->m_targetid = rt->getInt64(8);
    v->m_targetvip = rt->getInt32(9);
    v->m_targetname = rt->getString(10);
    v->m_chatchl = rt->getInt32(11);
    return v;
}

int RoleChatInfoDao::CreateTableSQLite3(symphony::IDB::ptr conn) {
    return conn->execute("CREATE TABLE role_chat("
            "roleid INTEGER NOT NULL DEFAULT 0,"
            "level INTEGER NOT NULL DEFAULT 0,"
            "rolename TEXT NOT NULL DEFAULT '',"
            "viplevel INTEGER NOT NULL DEFAULT 0,"
            "areaid INTEGER NOT NULL DEFAULT 0,"
            "channel INTEGER NOT NULL DEFAULT 0,"
            "text TEXT NOT NULL DEFAULT '',"
            "optime TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "targetid INTEGER NOT NULL DEFAULT 0,"
            "targetvip INTEGER NOT NULL DEFAULT 0,"
            "targetname TEXT NOT NULL DEFAULT '',"
            "chatchl INTEGER NOT NULL DEFAULT 0, PRIMARY KEY());"
            );
}

int RoleChatInfoDao::CreateTableMySQL(symphony::IDB::ptr conn) {
    return conn->execute("CREATE TABLE role_chat("
            "`roleid` bigint NOT NULL DEFAULT 0 COMMENT '角色ID',"
            "`level` int NOT NULL DEFAULT 0 COMMENT '等级',"
            "`rolename` varchar(64) NOT NULL DEFAULT '' COMMENT '角色名',"
            "`viplevel` int NOT NULL DEFAULT 0 COMMENT 'vip等级',"
            "`areaid` int NOT NULL DEFAULT 0 COMMENT '区服ID',"
            "`channel` int NOT NULL DEFAULT 0 COMMENT '平台ID',"
            "`text` varchar(256) NOT NULL DEFAULT '' COMMENT '聊天内容',"
            "`optime` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '聊天时间',"
            "`targetid` bigint NOT NULL DEFAULT 0 COMMENT '目标角色ID',"
            "`targetvip` int NOT NULL DEFAULT 0 COMMENT '目标角色vip等级',"
            "`targetname` varchar(64) NOT NULL DEFAULT '' COMMENT '目标角色名',"
            "`chatchl` int NOT NULL DEFAULT 0 COMMENT '聊天频道',"
            "PRIMARY KEY())");
}
} //namespace log
} //namespace symphony
