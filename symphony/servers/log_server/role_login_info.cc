#include "role_login_info.h"
#include "symphony/log.h"

namespace symphony {
namespace log {

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("orm");

RoleLoginInfo::RoleLoginInfo()
    :m_channel()
    ,m_level()
    ,m_viplevel()
    ,m_areaid()
    ,m_roleid()
    ,m_accountid()
    ,m_rolename()
    ,m_uuid()
    ,m_idfa()
    ,m_imei()
    ,m_imodel()
    ,m_optime() {
}

std::string RoleLoginInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["roleid"] = std::to_string(m_roleid);
    jvalue["accountid"] = std::to_string(m_accountid);
    jvalue["channel"] = m_channel;
    jvalue["level"] = m_level;
    jvalue["viplevel"] = m_viplevel;
    jvalue["optime"] = symphony::Time2Str(m_optime);
    jvalue["areaid"] = m_areaid;
    jvalue["rolename"] = m_rolename;
    jvalue["uuid"] = m_uuid;
    jvalue["idfa"] = m_idfa;
    jvalue["imei"] = m_imei;
    jvalue["imodel"] = m_imodel;
    return symphony::JsonUtil::ToString(jvalue);
}

void RoleLoginInfo::setRoleid(const int64_t& v) {
    m_roleid = v;
}

void RoleLoginInfo::setAccountid(const int64_t& v) {
    m_accountid = v;
}

void RoleLoginInfo::setChannel(const int32_t& v) {
    m_channel = v;
}

void RoleLoginInfo::setLevel(const int32_t& v) {
    m_level = v;
}

void RoleLoginInfo::setViplevel(const int32_t& v) {
    m_viplevel = v;
}

void RoleLoginInfo::setOptime(const int64_t& v) {
    m_optime = v;
}

void RoleLoginInfo::setAreaid(const int32_t& v) {
    m_areaid = v;
}

void RoleLoginInfo::setRolename(const std::string& v) {
    m_rolename = v;
}

void RoleLoginInfo::setUuid(const std::string& v) {
    m_uuid = v;
}

void RoleLoginInfo::setIdfa(const std::string& v) {
    m_idfa = v;
}

void RoleLoginInfo::setImei(const std::string& v) {
    m_imei = v;
}

void RoleLoginInfo::setImodel(const std::string& v) {
    m_imodel = v;
}


int RoleLoginInfoDao::Update(RoleLoginInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "update role_login set roleid = ?, accountid = ?, channel = ?, level = ?, viplevel = ?, optime = ?, areaid = ?, rolename = ?, uuid = ?, idfa = ?, imei = ?, imodel = ? where";
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
    stmt->bindString(9, info->m_uuid);
    stmt->bindString(10, info->m_idfa);
    stmt->bindString(11, info->m_imei);
    stmt->bindString(12, info->m_imodel);
    return stmt->execute();
}

int RoleLoginInfoDao::Insert(RoleLoginInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "insert into role_login (roleid, accountid, channel, level, viplevel, optime, areaid, rolename, uuid, idfa, imei, imodel) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
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
    stmt->bindString(9, info->m_uuid);
    stmt->bindString(10, info->m_idfa);
    stmt->bindString(11, info->m_imei);
    stmt->bindString(12, info->m_imodel);
    int rt = stmt->execute();
    return rt;
}

int RoleLoginInfoDao::InsertOrUpdate(RoleLoginInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "replace into role_login (roleid, accountid, channel, level, viplevel, optime, areaid, rolename, uuid, idfa, imei, imodel) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
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
    stmt->bindString(9, info->m_uuid);
    stmt->bindString(10, info->m_idfa);
    stmt->bindString(11, info->m_imei);
    stmt->bindString(12, info->m_imodel);
    return stmt->execute();
}

int RoleLoginInfoDao::Delete(RoleLoginInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "delete from role_login where";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    return stmt->execute();
}

int RoleLoginInfoDao::QueryAll(std::vector<RoleLoginInfo::ptr>& results, symphony::IDB::ptr conn) {
    std::string sql = "select roleid, accountid, channel, level, viplevel, optime, areaid, rolename, uuid, idfa, imei, imodel from role_login";
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
        RoleLoginInfo::ptr v(new RoleLoginInfo);
        v->m_roleid = rt->getInt64(0);
        v->m_accountid = rt->getInt64(1);
        v->m_channel = rt->getInt32(2);
        v->m_level = rt->getInt32(3);
        v->m_viplevel = rt->getInt32(4);
        v->m_optime = rt->getTime(5);
        v->m_areaid = rt->getInt32(6);
        v->m_rolename = rt->getString(7);
        v->m_uuid = rt->getString(8);
        v->m_idfa = rt->getString(9);
        v->m_imei = rt->getString(10);
        v->m_imodel = rt->getString(11);
        results.push_back(v);
    }
    return 0;
}

RoleLoginInfo::ptr RoleLoginInfoDao::Query(symphony::IDB::ptr conn) {
    std::string sql = "select roleid, accountid, channel, level, viplevel, optime, areaid, rolename, uuid, idfa, imei, imodel from role_login where";
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
    RoleLoginInfo::ptr v(new RoleLoginInfo);
    v->m_roleid = rt->getInt64(0);
    v->m_accountid = rt->getInt64(1);
    v->m_channel = rt->getInt32(2);
    v->m_level = rt->getInt32(3);
    v->m_viplevel = rt->getInt32(4);
    v->m_optime = rt->getTime(5);
    v->m_areaid = rt->getInt32(6);
    v->m_rolename = rt->getString(7);
    v->m_uuid = rt->getString(8);
    v->m_idfa = rt->getString(9);
    v->m_imei = rt->getString(10);
    v->m_imodel = rt->getString(11);
    return v;
}

int RoleLoginInfoDao::CreateTableSQLite3(symphony::IDB::ptr conn) {
    return conn->execute("CREATE TABLE role_login("
            "roleid INTEGER NOT NULL DEFAULT 0,"
            "accountid INTEGER NOT NULL DEFAULT 0,"
            "channel INTEGER NOT NULL DEFAULT 0,"
            "level INTEGER NOT NULL DEFAULT 0,"
            "viplevel INTEGER NOT NULL DEFAULT 0,"
            "optime TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "areaid INTEGER NOT NULL DEFAULT 0,"
            "rolename TEXT NOT NULL DEFAULT '',"
            "uuid TEXT NOT NULL DEFAULT '',"
            "idfa TEXT NOT NULL DEFAULT '',"
            "imei TEXT NOT NULL DEFAULT '',"
            "imodel TEXT NOT NULL DEFAULT '', PRIMARY KEY());"
            );
}

int RoleLoginInfoDao::CreateTableMySQL(symphony::IDB::ptr conn) {
    return conn->execute("CREATE TABLE role_login("
            "`roleid` bigint NOT NULL DEFAULT 0 COMMENT '角色ID',"
            "`accountid` bigint NOT NULL DEFAULT 0 COMMENT '帐号ID',"
            "`channel` int NOT NULL DEFAULT 0 COMMENT '平台ID',"
            "`level` int NOT NULL DEFAULT 0 COMMENT '等级',"
            "`viplevel` int NOT NULL DEFAULT 0 COMMENT 'vip等级',"
            "`optime` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '登出时间',"
            "`areaid` int NOT NULL DEFAULT 0 COMMENT '区服ID',"
            "`rolename` varchar(64) NOT NULL DEFAULT '' COMMENT '角色名',"
            "`uuid` varchar(64) NOT NULL DEFAULT '' COMMENT '登入设备UUID',"
            "`idfa` varchar(64) NOT NULL DEFAULT '' COMMENT 'idfa',"
            "`imei` varchar(64) NOT NULL DEFAULT '' COMMENT '手机序列号',"
            "`imodel` varchar(64) NOT NULL DEFAULT '' COMMENT '机型',"
            "PRIMARY KEY())");
}
} //namespace log
} //namespace symphony
