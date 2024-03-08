#include "account_create_info.h"
#include "symphony/log.h"

namespace symphony {
namespace log {

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("orm");

AccountCreateInfo::AccountCreateInfo()
    :m_version()
    ,m_channel()
    ,m_accountid()
    ,m_imodel()
    ,m_imei()
    ,m_ip()
    ,m_openid()
    ,m_idfa()
    ,m_uuid()
    ,m_optime() {
}

std::string AccountCreateInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["accountid"] = std::to_string(m_accountid);
    jvalue["version"] = m_version;
    jvalue["channel"] = m_channel;
    jvalue["optime"] = symphony::Time2Str(m_optime);
    jvalue["imodel"] = m_imodel;
    jvalue["imei"] = m_imei;
    jvalue["ip"] = m_ip;
    jvalue["openid"] = m_openid;
    jvalue["idfa"] = m_idfa;
    jvalue["uuid"] = m_uuid;
    return symphony::JsonUtil::ToString(jvalue);
}

void AccountCreateInfo::setAccountid(const int64_t& v) {
    m_accountid = v;
}

void AccountCreateInfo::setVersion(const int32_t& v) {
    m_version = v;
}

void AccountCreateInfo::setChannel(const int32_t& v) {
    m_channel = v;
}

void AccountCreateInfo::setOptime(const int64_t& v) {
    m_optime = v;
}

void AccountCreateInfo::setImodel(const std::string& v) {
    m_imodel = v;
}

void AccountCreateInfo::setImei(const std::string& v) {
    m_imei = v;
}

void AccountCreateInfo::setIp(const std::string& v) {
    m_ip = v;
}

void AccountCreateInfo::setOpenid(const std::string& v) {
    m_openid = v;
}

void AccountCreateInfo::setIdfa(const std::string& v) {
    m_idfa = v;
}

void AccountCreateInfo::setUuid(const std::string& v) {
    m_uuid = v;
}


int AccountCreateInfoDao::Update(AccountCreateInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "update account_create set accountid = ?, version = ?, channel = ?, optime = ?, imodel = ?, imei = ?, ip = ?, openid = ?, idfa = ?, uuid = ? where";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_accountid);
    stmt->bindInt32(2, info->m_version);
    stmt->bindInt32(3, info->m_channel);
    stmt->bindTime(4, info->m_optime);
    stmt->bindString(5, info->m_imodel);
    stmt->bindString(6, info->m_imei);
    stmt->bindString(7, info->m_ip);
    stmt->bindString(8, info->m_openid);
    stmt->bindString(9, info->m_idfa);
    stmt->bindString(10, info->m_uuid);
    return stmt->execute();
}

int AccountCreateInfoDao::Insert(AccountCreateInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "insert into account_create (version, channel, optime, imodel, imei, ip, openid, idfa, uuid) values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt32(1, info->m_version);
    stmt->bindInt32(2, info->m_channel);
    stmt->bindTime(3, info->m_optime);
    stmt->bindString(4, info->m_imodel);
    stmt->bindString(5, info->m_imei);
    stmt->bindString(6, info->m_ip);
    stmt->bindString(7, info->m_openid);
    stmt->bindString(8, info->m_idfa);
    stmt->bindString(9, info->m_uuid);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_accountid = conn->getLastInsertId();
    }
    return rt;
}

int AccountCreateInfoDao::InsertOrUpdate(AccountCreateInfo::ptr info, symphony::IDB::ptr conn) {
    if(info->m_accountid == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into account_create (accountid, version, channel, optime, imodel, imei, ip, openid, idfa, uuid) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_accountid);
    stmt->bindInt32(2, info->m_version);
    stmt->bindInt32(3, info->m_channel);
    stmt->bindTime(4, info->m_optime);
    stmt->bindString(5, info->m_imodel);
    stmt->bindString(6, info->m_imei);
    stmt->bindString(7, info->m_ip);
    stmt->bindString(8, info->m_openid);
    stmt->bindString(9, info->m_idfa);
    stmt->bindString(10, info->m_uuid);
    return stmt->execute();
}

int AccountCreateInfoDao::Delete(AccountCreateInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "delete from account_create where";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    return stmt->execute();
}

int AccountCreateInfoDao::DeleteByOptime( const int64_t& optime, symphony::IDB::ptr conn) {
    std::string sql = "delete from account_create where optime = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindTime(1, optime);
    return stmt->execute();
}

int AccountCreateInfoDao::QueryAll(std::vector<AccountCreateInfo::ptr>& results, symphony::IDB::ptr conn) {
    std::string sql = "select accountid, version, channel, optime, imodel, imei, ip, openid, idfa, uuid from account_create";
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
        AccountCreateInfo::ptr v(new AccountCreateInfo);
        v->m_accountid = rt->getInt64(0);
        v->m_version = rt->getInt32(1);
        v->m_channel = rt->getInt32(2);
        v->m_optime = rt->getTime(3);
        v->m_imodel = rt->getString(4);
        v->m_imei = rt->getString(5);
        v->m_ip = rt->getString(6);
        v->m_openid = rt->getString(7);
        v->m_idfa = rt->getString(8);
        v->m_uuid = rt->getString(9);
        results.push_back(v);
    }
    return 0;
}

AccountCreateInfo::ptr AccountCreateInfoDao::Query(symphony::IDB::ptr conn) {
    std::string sql = "select accountid, version, channel, optime, imodel, imei, ip, openid, idfa, uuid from account_create where";
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
    AccountCreateInfo::ptr v(new AccountCreateInfo);
    v->m_accountid = rt->getInt64(0);
    v->m_version = rt->getInt32(1);
    v->m_channel = rt->getInt32(2);
    v->m_optime = rt->getTime(3);
    v->m_imodel = rt->getString(4);
    v->m_imei = rt->getString(5);
    v->m_ip = rt->getString(6);
    v->m_openid = rt->getString(7);
    v->m_idfa = rt->getString(8);
    v->m_uuid = rt->getString(9);
    return v;
}

int AccountCreateInfoDao::QueryByOptime(std::vector<AccountCreateInfo::ptr>& results,  const int64_t& optime, symphony::IDB::ptr conn) {
    std::string sql = "select accountid, version, channel, optime, imodel, imei, ip, openid, idfa, uuid from account_create where optime = ?";
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
        AccountCreateInfo::ptr v(new AccountCreateInfo);
        v->m_accountid = rt->getInt64(0);
        v->m_version = rt->getInt32(1);
        v->m_channel = rt->getInt32(2);
        v->m_optime = rt->getTime(3);
        v->m_imodel = rt->getString(4);
        v->m_imei = rt->getString(5);
        v->m_ip = rt->getString(6);
        v->m_openid = rt->getString(7);
        v->m_idfa = rt->getString(8);
        v->m_uuid = rt->getString(9);
        results.push_back(v);
    };
    return 0;
}

int AccountCreateInfoDao::CreateTableSQLite3(symphony::IDB::ptr conn) {
    return conn->execute("CREATE TABLE account_create("
            "accountid INTEGER PRIMARY KEY AUTOINCREMENT,"
            "version INTEGER NOT NULL DEFAULT 0,"
            "channel INTEGER NOT NULL DEFAULT 0,"
            "optime TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "imodel TEXT NOT NULL DEFAULT '',"
            "imei TEXT NOT NULL DEFAULT '',"
            "ip TEXT NOT NULL DEFAULT '',"
            "openid TEXT NOT NULL DEFAULT '',"
            "idfa TEXT NOT NULL DEFAULT '',"
            "uuid TEXT NOT NULL DEFAULT '');"
            "CREATE INDEX account_create_optime ON account_create(optime);"
            );
}

int AccountCreateInfoDao::CreateTableMySQL(symphony::IDB::ptr conn) {
    return conn->execute("CREATE TABLE account_create("
            "`accountid` bigint AUTO_INCREMENT COMMENT '帐号',"
            "`version` int NOT NULL DEFAULT 0 COMMENT '版本',"
            "`channel` int NOT NULL DEFAULT 0 COMMENT '平台ID',"
            "`optime` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建帐号时间',"
            "`imodel` varchar(64) NOT NULL DEFAULT '' COMMENT '机型',"
            "`imei` varchar(64) NOT NULL DEFAULT '' COMMENT '手机序列号',"
            "`ip` varchar(64) NOT NULL DEFAULT '' COMMENT 'IP地址',"
            "`openid` varchar(64) NOT NULL DEFAULT '' COMMENT 'openid',"
            "`idfa` varchar(64) NOT NULL DEFAULT '' COMMENT 'idfa',"
            "`uuid` varchar(64) NOT NULL DEFAULT '' COMMENT 'uuid',"
            "PRIMARY KEY(),"
            "KEY `account_create_optime` (`optime`))");
}
} //namespace log
} //namespace symphony
