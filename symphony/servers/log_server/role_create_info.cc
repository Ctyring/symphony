#include "role_create_info.h"
#include "symphony/log.h"

namespace symphony {
namespace log {

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("orm");

RoleCreateInfo::RoleCreateInfo()
    :m_areaid()
    ,m_channel()
    ,m_roleid()
    ,m_accountid()
    ,m_rolename()
    ,m_imodel()
    ,m_imei()
    ,m_idfa()
    ,m_uuid()
    ,m_optime() {
}

std::string RoleCreateInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["roleid"] = std::to_string(m_roleid);
    jvalue["accountid"] = std::to_string(m_accountid);
    jvalue["areaid"] = m_areaid;
    jvalue["channel"] = m_channel;
    jvalue["optime"] = symphony::Time2Str(m_optime);
    jvalue["rolename"] = m_rolename;
    jvalue["imodel"] = m_imodel;
    jvalue["imei"] = m_imei;
    jvalue["idfa"] = m_idfa;
    jvalue["uuid"] = m_uuid;
    return symphony::JsonUtil::ToString(jvalue);
}

void RoleCreateInfo::setRoleid(const int64_t& v) {
    m_roleid = v;
}

void RoleCreateInfo::setAccountid(const int64_t& v) {
    m_accountid = v;
}

void RoleCreateInfo::setAreaid(const int32_t& v) {
    m_areaid = v;
}

void RoleCreateInfo::setChannel(const int32_t& v) {
    m_channel = v;
}

void RoleCreateInfo::setOptime(const int64_t& v) {
    m_optime = v;
}

void RoleCreateInfo::setRolename(const std::string& v) {
    m_rolename = v;
}

void RoleCreateInfo::setImodel(const std::string& v) {
    m_imodel = v;
}

void RoleCreateInfo::setImei(const std::string& v) {
    m_imei = v;
}

void RoleCreateInfo::setIdfa(const std::string& v) {
    m_idfa = v;
}

void RoleCreateInfo::setUuid(const std::string& v) {
    m_uuid = v;
}


int RoleCreateInfoDao::Update(RoleCreateInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "update role_create set roleid = ?, accountid = ?, areaid = ?, channel = ?, optime = ?, rolename = ?, imodel = ?, imei = ?, idfa = ?, uuid = ? where";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_roleid);
    stmt->bindInt64(2, info->m_accountid);
    stmt->bindInt32(3, info->m_areaid);
    stmt->bindInt32(4, info->m_channel);
    stmt->bindTime(5, info->m_optime);
    stmt->bindString(6, info->m_rolename);
    stmt->bindString(7, info->m_imodel);
    stmt->bindString(8, info->m_imei);
    stmt->bindString(9, info->m_idfa);
    stmt->bindString(10, info->m_uuid);
    return stmt->execute();
}

int RoleCreateInfoDao::Insert(RoleCreateInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "insert into role_create (accountid, areaid, channel, optime, rolename, imodel, imei, idfa, uuid) values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_accountid);
    stmt->bindInt32(2, info->m_areaid);
    stmt->bindInt32(3, info->m_channel);
    stmt->bindTime(4, info->m_optime);
    stmt->bindString(5, info->m_rolename);
    stmt->bindString(6, info->m_imodel);
    stmt->bindString(7, info->m_imei);
    stmt->bindString(8, info->m_idfa);
    stmt->bindString(9, info->m_uuid);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_roleid = conn->getLastInsertId();
    }
    return rt;
}

int RoleCreateInfoDao::InsertOrUpdate(RoleCreateInfo::ptr info, symphony::IDB::ptr conn) {
    if(info->m_roleid == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into role_create (roleid, accountid, areaid, channel, optime, rolename, imodel, imei, idfa, uuid) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_roleid);
    stmt->bindInt64(2, info->m_accountid);
    stmt->bindInt32(3, info->m_areaid);
    stmt->bindInt32(4, info->m_channel);
    stmt->bindTime(5, info->m_optime);
    stmt->bindString(6, info->m_rolename);
    stmt->bindString(7, info->m_imodel);
    stmt->bindString(8, info->m_imei);
    stmt->bindString(9, info->m_idfa);
    stmt->bindString(10, info->m_uuid);
    return stmt->execute();
}

int RoleCreateInfoDao::Delete(RoleCreateInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "delete from role_create where";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    return stmt->execute();
}

int RoleCreateInfoDao::DeleteByOptime( const int64_t& optime, symphony::IDB::ptr conn) {
    std::string sql = "delete from role_create where optime = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindTime(1, optime);
    return stmt->execute();
}

int RoleCreateInfoDao::QueryAll(std::vector<RoleCreateInfo::ptr>& results, symphony::IDB::ptr conn) {
    std::string sql = "select roleid, accountid, areaid, channel, optime, rolename, imodel, imei, idfa, uuid from role_create";
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
        RoleCreateInfo::ptr v(new RoleCreateInfo);
        v->m_roleid = rt->getInt64(0);
        v->m_accountid = rt->getInt64(1);
        v->m_areaid = rt->getInt32(2);
        v->m_channel = rt->getInt32(3);
        v->m_optime = rt->getTime(4);
        v->m_rolename = rt->getString(5);
        v->m_imodel = rt->getString(6);
        v->m_imei = rt->getString(7);
        v->m_idfa = rt->getString(8);
        v->m_uuid = rt->getString(9);
        results.push_back(v);
    }
    return 0;
}

RoleCreateInfo::ptr RoleCreateInfoDao::Query(symphony::IDB::ptr conn) {
    std::string sql = "select roleid, accountid, areaid, channel, optime, rolename, imodel, imei, idfa, uuid from role_create where";
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
    RoleCreateInfo::ptr v(new RoleCreateInfo);
    v->m_roleid = rt->getInt64(0);
    v->m_accountid = rt->getInt64(1);
    v->m_areaid = rt->getInt32(2);
    v->m_channel = rt->getInt32(3);
    v->m_optime = rt->getTime(4);
    v->m_rolename = rt->getString(5);
    v->m_imodel = rt->getString(6);
    v->m_imei = rt->getString(7);
    v->m_idfa = rt->getString(8);
    v->m_uuid = rt->getString(9);
    return v;
}

int RoleCreateInfoDao::QueryByOptime(std::vector<RoleCreateInfo::ptr>& results,  const int64_t& optime, symphony::IDB::ptr conn) {
    std::string sql = "select roleid, accountid, areaid, channel, optime, rolename, imodel, imei, idfa, uuid from role_create where optime = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindTime(1, optime);
    auto rt = stmt->query();
    if(!rt) {
        return 0;
    }
    while (rt->next()) {
        RoleCreateInfo::ptr v(new RoleCreateInfo);
        v->m_roleid = rt->getInt64(0);
        v->m_accountid = rt->getInt64(1);
        v->m_areaid = rt->getInt32(2);
        v->m_channel = rt->getInt32(3);
        v->m_optime = rt->getTime(4);
        v->m_rolename = rt->getString(5);
        v->m_imodel = rt->getString(6);
        v->m_imei = rt->getString(7);
        v->m_idfa = rt->getString(8);
        v->m_uuid = rt->getString(9);
        results.push_back(v);
    };
    return 0;
}

int RoleCreateInfoDao::CreateTableSQLite3(symphony::IDB::ptr conn) {
    return conn->execute("CREATE TABLE role_create("
            "roleid INTEGER PRIMARY KEY AUTOINCREMENT,"
            "accountid INTEGER NOT NULL DEFAULT 0,"
            "areaid INTEGER NOT NULL DEFAULT 0,"
            "channel INTEGER NOT NULL DEFAULT 0,"
            "optime TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "rolename TEXT NOT NULL DEFAULT '',"
            "imodel TEXT NOT NULL DEFAULT '',"
            "imei TEXT NOT NULL DEFAULT '',"
            "idfa TEXT NOT NULL DEFAULT '',"
            "uuid TEXT NOT NULL DEFAULT '');"
            "CREATE INDEX role_create_optime ON role_create(optime);"
            );
}

int RoleCreateInfoDao::CreateTableMySQL(symphony::IDB::ptr conn) {
    return conn->execute("CREATE TABLE role_create("
            "`roleid` bigint AUTO_INCREMENT COMMENT '角色ID',"
            "`accountid` bigint NOT NULL DEFAULT 0 COMMENT '帐号',"
            "`areaid` int NOT NULL DEFAULT 0 COMMENT '区ID',"
            "`channel` int NOT NULL DEFAULT 0 COMMENT '平台ID',"
            "`optime` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建角色时间',"
            "`rolename` varchar(64) NOT NULL DEFAULT '' COMMENT '角色名',"
            "`imodel` varchar(64) NOT NULL DEFAULT '' COMMENT '机型',"
            "`imei` varchar(64) NOT NULL DEFAULT '' COMMENT '手机序列号',"
            "`idfa` varchar(64) NOT NULL DEFAULT '' COMMENT 'idfa',"
            "`uuid` varchar(64) NOT NULL DEFAULT '' COMMENT 'uuid',"
            "PRIMARY KEY(),"
            "KEY `role_create_optime` (`optime`))");
}
} //namespace log
} //namespace symphony
