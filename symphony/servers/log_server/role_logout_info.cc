#include "role_logout_info.h"
#include "symphony/log.h"

namespace symphony {
namespace log {

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("orm");

RoleLogoutInfo::RoleLogoutInfo()
    :m_channel()
    ,m_level()
    ,m_viplevel()
    ,m_areaid()
    ,m_roleid()
    ,m_accountid()
    ,m_rolename()
    ,m_idfa()
    ,m_imei()
    ,m_imodel()
    ,m_optime() {
}

std::string RoleLogoutInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["roleid"] = std::to_string(m_roleid);
    jvalue["accountid"] = std::to_string(m_accountid);
    jvalue["channel"] = m_channel;
    jvalue["level"] = m_level;
    jvalue["viplevel"] = m_viplevel;
    jvalue["optime"] = symphony::Time2Str(m_optime);
    jvalue["areaid"] = m_areaid;
    jvalue["rolename"] = m_rolename;
    jvalue["idfa"] = m_idfa;
    jvalue["imei"] = m_imei;
    jvalue["imodel"] = m_imodel;
    return symphony::JsonUtil::ToString(jvalue);
}

void RoleLogoutInfo::setRoleid(const int64_t& v) {
    m_roleid = v;
}

void RoleLogoutInfo::setAccountid(const int64_t& v) {
    m_accountid = v;
}

void RoleLogoutInfo::setChannel(const int32_t& v) {
    m_channel = v;
}

void RoleLogoutInfo::setLevel(const int32_t& v) {
    m_level = v;
}

void RoleLogoutInfo::setViplevel(const int32_t& v) {
    m_viplevel = v;
}

void RoleLogoutInfo::setOptime(const int64_t& v) {
    m_optime = v;
}

void RoleLogoutInfo::setAreaid(const int32_t& v) {
    m_areaid = v;
}

void RoleLogoutInfo::setRolename(const std::string& v) {
    m_rolename = v;
}

void RoleLogoutInfo::setIdfa(const std::string& v) {
    m_idfa = v;
}

void RoleLogoutInfo::setImei(const std::string& v) {
    m_imei = v;
}

void RoleLogoutInfo::setImodel(const std::string& v) {
    m_imodel = v;
}


int RoleLogoutInfoDao::Update(RoleLogoutInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "update role_logout set roleid = ?, accountid = ?, channel = ?, level = ?, viplevel = ?, optime = ?, areaid = ?, rolename = ?, idfa = ?, imei = ?, imodel = ? where";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_roleid);
    stmt->bindInt64(2, info->m_accountid);
    stmt->bindInt32(3, info->m_channel);
    stmt->bindInt32(4, info->m_level);
    stmt->bindInt32(5, info->m_viplevel);
    stmt->bindTime(6, info->m_optime);
    stmt->bindInt32(7, info->m_areaid);
    stmt->bindString(8, info->m_rolename);
    stmt->bindString(9, info->m_idfa);
    stmt->bindString(10, info->m_imei);
    stmt->bindString(11, info->m_imodel);
    return stmt->execute();
}

int RoleLogoutInfoDao::Insert(RoleLogoutInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "insert into role_logout (roleid, accountid, channel, level, viplevel, optime, areaid, rolename, idfa, imei, imodel) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_roleid);
    stmt->bindInt64(2, info->m_accountid);
    stmt->bindInt32(3, info->m_channel);
    stmt->bindInt32(4, info->m_level);
    stmt->bindInt32(5, info->m_viplevel);
    stmt->bindTime(6, info->m_optime);
    stmt->bindInt32(7, info->m_areaid);
    stmt->bindString(8, info->m_rolename);
    stmt->bindString(9, info->m_idfa);
    stmt->bindString(10, info->m_imei);
    stmt->bindString(11, info->m_imodel);
    int rt = stmt->execute();
    return rt;
}

int RoleLogoutInfoDao::InsertOrUpdate(RoleLogoutInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "replace into role_logout (roleid, accountid, channel, level, viplevel, optime, areaid, rolename, idfa, imei, imodel) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_roleid);
    stmt->bindInt64(2, info->m_accountid);
    stmt->bindInt32(3, info->m_channel);
    stmt->bindInt32(4, info->m_level);
    stmt->bindInt32(5, info->m_viplevel);
    stmt->bindTime(6, info->m_optime);
    stmt->bindInt32(7, info->m_areaid);
    stmt->bindString(8, info->m_rolename);
    stmt->bindString(9, info->m_idfa);
    stmt->bindString(10, info->m_imei);
    stmt->bindString(11, info->m_imodel);
    return stmt->execute();
}

int RoleLogoutInfoDao::Delete(RoleLogoutInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "delete from role_logout where";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    return stmt->execute();
}

int RoleLogoutInfoDao::QueryAll(std::vector<RoleLogoutInfo::ptr>& results, symphony::IDB::ptr conn) {
    std::string sql = "select roleid, accountid, channel, level, viplevel, optime, areaid, rolename, idfa, imei, imodel from role_logout";
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
        RoleLogoutInfo::ptr v(new RoleLogoutInfo);
        v->m_roleid = rt->getInt64(0);
        v->m_accountid = rt->getInt64(1);
        v->m_channel = rt->getInt32(2);
        v->m_level = rt->getInt32(3);
        v->m_viplevel = rt->getInt32(4);
        v->m_optime = rt->getTime(5);
        v->m_areaid = rt->getInt32(6);
        v->m_rolename = rt->getString(7);
        v->m_idfa = rt->getString(8);
        v->m_imei = rt->getString(9);
        v->m_imodel = rt->getString(10);
        results.push_back(v);
    }
    return 0;
}

RoleLogoutInfo::ptr RoleLogoutInfoDao::Query(symphony::IDB::ptr conn) {
    std::string sql = "select roleid, accountid, channel, level, viplevel, optime, areaid, rolename, idfa, imei, imodel from role_logout where";
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
    RoleLogoutInfo::ptr v(new RoleLogoutInfo);
    v->m_roleid = rt->getInt64(0);
    v->m_accountid = rt->getInt64(1);
    v->m_channel = rt->getInt32(2);
    v->m_level = rt->getInt32(3);
    v->m_viplevel = rt->getInt32(4);
    v->m_optime = rt->getTime(5);
    v->m_areaid = rt->getInt32(6);
    v->m_rolename = rt->getString(7);
    v->m_idfa = rt->getString(8);
    v->m_imei = rt->getString(9);
    v->m_imodel = rt->getString(10);
    return v;
}

int RoleLogoutInfoDao::CreateTableSQLite3(symphony::IDB::ptr conn) {
    return conn->execute("CREATE TABLE role_logout("
            "roleid INTEGER NOT NULL DEFAULT 0,"
            "accountid INTEGER NOT NULL DEFAULT 0,"
            "channel INTEGER NOT NULL DEFAULT 0,"
            "level INTEGER NOT NULL DEFAULT 0,"
            "viplevel INTEGER NOT NULL DEFAULT 0,"
            "optime TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "areaid INTEGER NOT NULL DEFAULT 0,"
            "rolename TEXT NOT NULL DEFAULT '',"
            "idfa TEXT NOT NULL DEFAULT '',"
            "imei TEXT NOT NULL DEFAULT '',"
            "imodel TEXT NOT NULL DEFAULT '', PRIMARY KEY());"
            );
}

int RoleLogoutInfoDao::CreateTableMySQL(symphony::IDB::ptr conn) {
    return conn->execute("CREATE TABLE role_logout("
            "`roleid` bigint NOT NULL DEFAULT 0 COMMENT '角色ID',"
            "`accountid` bigint NOT NULL DEFAULT 0 COMMENT '帐号ID',"
            "`channel` int NOT NULL DEFAULT 0 COMMENT '平台ID',"
            "`level` int NOT NULL DEFAULT 0 COMMENT '等级',"
            "`viplevel` int NOT NULL DEFAULT 0 COMMENT 'vip等级',"
            "`optime` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '登出时间',"
            "`areaid` int NOT NULL DEFAULT 0 COMMENT '区服ID',"
            "`rolename` varchar(64) NOT NULL DEFAULT '' COMMENT '角色名',"
            "`idfa` varchar(64) NOT NULL DEFAULT '' COMMENT 'idfa',"
            "`imei` varchar(64) NOT NULL DEFAULT '' COMMENT '手机序列号',"
            "`imodel` varchar(64) NOT NULL DEFAULT '' COMMENT '机型',"
            "PRIMARY KEY())");
}
} //namespace log
} //namespace symphony
