#include "account_login_info.h"
#include "symphony/log.h"

namespace symphony {
namespace log {

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("orm");

AccountLoginInfo::AccountLoginInfo()
    :m_channel()
    ,m_version()
    ,m_accountid()
    ,m_ip()
    ,m_openid()
    ,m_uuid()
    ,m_idfa()
    ,m_imei()
    ,m_imodel()
    ,m_optime() {
}

std::string AccountLoginInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["accountid"] = std::to_string(m_accountid);
    jvalue["channel"] = m_channel;
    jvalue["version"] = m_version;
    jvalue["optime"] = symphony::Time2Str(m_optime);
    jvalue["ip"] = m_ip;
    jvalue["openid"] = m_openid;
    jvalue["uuid"] = m_uuid;
    jvalue["idfa"] = m_idfa;
    jvalue["imei"] = m_imei;
    jvalue["imodel"] = m_imodel;
    return symphony::JsonUtil::ToString(jvalue);
}

void AccountLoginInfo::setAccountid(const int64_t& v) {
    m_accountid = v;
}

void AccountLoginInfo::setChannel(const int32_t& v) {
    m_channel = v;
}

void AccountLoginInfo::setVersion(const int32_t& v) {
    m_version = v;
}

void AccountLoginInfo::setOptime(const int64_t& v) {
    m_optime = v;
}

void AccountLoginInfo::setIp(const std::string& v) {
    m_ip = v;
}

void AccountLoginInfo::setOpenid(const std::string& v) {
    m_openid = v;
}

void AccountLoginInfo::setUuid(const std::string& v) {
    m_uuid = v;
}

void AccountLoginInfo::setIdfa(const std::string& v) {
    m_idfa = v;
}

void AccountLoginInfo::setImei(const std::string& v) {
    m_imei = v;
}

void AccountLoginInfo::setImodel(const std::string& v) {
    m_imodel = v;
}


int AccountLoginInfoDao::Update(AccountLoginInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "update account_login set accountid = ?, channel = ?, version = ?, optime = ?, ip = ?, openid = ?, uuid = ?, idfa = ?, imei = ?, imodel = ? where";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_accountid);
    stmt->bindInt32(2, info->m_channel);
    stmt->bindInt32(3, info->m_version);
    stmt->bindTime(4, info->m_optime);
    stmt->bindString(5, info->m_ip);
    stmt->bindString(6, info->m_openid);
    stmt->bindString(7, info->m_uuid);
    stmt->bindString(8, info->m_idfa);
    stmt->bindString(9, info->m_imei);
    stmt->bindString(10, info->m_imodel);
    return stmt->execute();
}

int AccountLoginInfoDao::Insert(AccountLoginInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "insert into account_login (accountid, channel, version, optime, ip, openid, uuid, idfa, imei, imodel) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_accountid);
    stmt->bindInt32(2, info->m_channel);
    stmt->bindInt32(3, info->m_version);
    stmt->bindTime(4, info->m_optime);
    stmt->bindString(5, info->m_ip);
    stmt->bindString(6, info->m_openid);
    stmt->bindString(7, info->m_uuid);
    stmt->bindString(8, info->m_idfa);
    stmt->bindString(9, info->m_imei);
    stmt->bindString(10, info->m_imodel);
    int rt = stmt->execute();
    return rt;
}

int AccountLoginInfoDao::InsertOrUpdate(AccountLoginInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "replace into account_login (accountid, channel, version, optime, ip, openid, uuid, idfa, imei, imodel) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_accountid);
    stmt->bindInt32(2, info->m_channel);
    stmt->bindInt32(3, info->m_version);
    stmt->bindTime(4, info->m_optime);
    stmt->bindString(5, info->m_ip);
    stmt->bindString(6, info->m_openid);
    stmt->bindString(7, info->m_uuid);
    stmt->bindString(8, info->m_idfa);
    stmt->bindString(9, info->m_imei);
    stmt->bindString(10, info->m_imodel);
    return stmt->execute();
}

int AccountLoginInfoDao::Delete(AccountLoginInfo::ptr info, symphony::IDB::ptr conn) {
    std::string sql = "delete from account_login where";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        SYMPHONY_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    return stmt->execute();
}

int AccountLoginInfoDao::QueryAll(std::vector<AccountLoginInfo::ptr>& results, symphony::IDB::ptr conn) {
    std::string sql = "select accountid, channel, version, optime, ip, openid, uuid, idfa, imei, imodel from account_login";
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
        AccountLoginInfo::ptr v(new AccountLoginInfo);
        v->m_accountid = rt->getInt64(0);
        v->m_channel = rt->getInt32(1);
        v->m_version = rt->getInt32(2);
        v->m_optime = rt->getTime(3);
        v->m_ip = rt->getString(4);
        v->m_openid = rt->getString(5);
        v->m_uuid = rt->getString(6);
        v->m_idfa = rt->getString(7);
        v->m_imei = rt->getString(8);
        v->m_imodel = rt->getString(9);
        results.push_back(v);
    }
    return 0;
}

AccountLoginInfo::ptr AccountLoginInfoDao::Query(symphony::IDB::ptr conn) {
    std::string sql = "select accountid, channel, version, optime, ip, openid, uuid, idfa, imei, imodel from account_login where";
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
    AccountLoginInfo::ptr v(new AccountLoginInfo);
    v->m_accountid = rt->getInt64(0);
    v->m_channel = rt->getInt32(1);
    v->m_version = rt->getInt32(2);
    v->m_optime = rt->getTime(3);
    v->m_ip = rt->getString(4);
    v->m_openid = rt->getString(5);
    v->m_uuid = rt->getString(6);
    v->m_idfa = rt->getString(7);
    v->m_imei = rt->getString(8);
    v->m_imodel = rt->getString(9);
    return v;
}

int AccountLoginInfoDao::CreateTableSQLite3(symphony::IDB::ptr conn) {
    return conn->execute("CREATE TABLE account_login("
            "accountid INTEGER NOT NULL DEFAULT 0,"
            "channel INTEGER NOT NULL DEFAULT 0,"
            "version INTEGER NOT NULL DEFAULT 0,"
            "optime TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "ip TEXT NOT NULL DEFAULT '',"
            "openid TEXT NOT NULL DEFAULT '',"
            "uuid TEXT NOT NULL DEFAULT '',"
            "idfa TEXT NOT NULL DEFAULT '',"
            "imei TEXT NOT NULL DEFAULT '',"
            "imodel TEXT NOT NULL DEFAULT '', PRIMARY KEY());"
            );
}

int AccountLoginInfoDao::CreateTableMySQL(symphony::IDB::ptr conn) {
    return conn->execute("CREATE TABLE account_login("
            "`accountid` bigint NOT NULL DEFAULT 0 COMMENT '帐号ID',"
            "`channel` int NOT NULL DEFAULT 0 COMMENT '平台ID',"
            "`version` int NOT NULL DEFAULT 0 COMMENT '版本ID',"
            "`optime` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '登出时间',"
            "`ip` varchar(64) NOT NULL DEFAULT '' COMMENT '登入IP',"
            "`openid` varchar(64) NOT NULL DEFAULT '' COMMENT 'openid',"
            "`uuid` varchar(64) NOT NULL DEFAULT '' COMMENT '登入设备UUID',"
            "`idfa` varchar(64) NOT NULL DEFAULT '' COMMENT 'idfa',"
            "`imei` varchar(64) NOT NULL DEFAULT '' COMMENT '手机序列号',"
            "`imodel` varchar(64) NOT NULL DEFAULT '' COMMENT '机型',"
            "PRIMARY KEY())");
}
} //namespace log
} //namespace symphony
