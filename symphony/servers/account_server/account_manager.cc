#include "account_manager.h"
#include <regex>
#include "symphony/common/convert.h"
#include "symphony/common/func.h"
#include "symphony/common/time.h"
#include "symphony/db/mysql.h"
#include "symphony/ds/util.h"
#include "symphony/log.h"
#include "symphony/util/str_util.h"
namespace symphony {
namespace as {
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");
CAccountObjectMgr::CAccountObjectMgr() {
    m_IsRun = false;
    m_pThread = NULL;
    m_bCrossChannel = false;
    m_u64MaxID = 0;
}

CAccountObjectMgr::~CAccountObjectMgr() {
    m_IsRun = false;
    m_pThread = NULL;
    m_bCrossChannel = false;
}

bool CAccountObjectMgr::LoadCacheAccount() {
    std::map<std::string, std::string> params;
    params["host"] = "127.0.0.1";
    params["user"] = "root";
    params["passwd"] = "123456";
    params["dbname"] = "db_game";
    symphony::MySQL::ptr m(new symphony::MySQL(params));
    if (!m->connect()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "LoadCacheAccount Error: Can not open mysql database! Reason:"
            << m->getErrStr();
        SYMPHONY_LOG_ERROR(g_logger)
            << "LoadCacheAccount Error: "
               "Host:[%s]-User:[%s]-Pwd:[%s]-DBName:[%s]"
            << params["host"] << params["user"] << params["passwd"]
            << params["dbname"];
        return false;
    }

    std::string sql = "select * from account";
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(m->query(sql));
    CAccountObject* pTempObject = NULL;
    while (res->next()) {
        pTempObject = AddAccountObject(res->getInt64Field("id"),
                                       res->getStringField("name"),
                                       res->getIntField("channel"));

        // ERROR_RETURN_FALSE(pTempObject != NULL);
        if (pTempObject == nullptr) {
            return false;
        }

        pTempObject->m_strPassword = res->getStringField("password");
        pTempObject->m_uCreateTime =
            CommonFunc::DateStringToTime(res->getStringField("create_time"));
        pTempObject->m_uSealTime =
            CommonFunc::DateStringToTime(res->getStringField("seal_end_time"));
        pTempObject->m_nLastSvrID[0] = res->getIntField("lastsvrid1");
        pTempObject->m_nLastSvrID[1] = res->getIntField("lastsvrid2");
        if (m_u64MaxID < (uint64_t)res->getInt64Field("id")) {
            m_u64MaxID = (uint64_t)res->getInt64Field("id");
        }
    }

    return true;
}

CAccountObject* CAccountObjectMgr::GetAccountObjectByID(uint64_t AccountID) {
    return GetByKey(AccountID);
}

CAccountObject* CAccountObjectMgr::CreateAccountObject(
    const std::string& strName,
    const std::string& strPwd,
    int32_t nChannel) {
    m_u64MaxID += 1;

    CAccountObject* pObj = InsertAlloc(m_u64MaxID);
    if (pObj == nullptr) {
        return nullptr;
    }

    pObj->m_strName = strName;
    pObj->m_strPassword = strPwd;
    pObj->m_ID = m_u64MaxID;
    pObj->m_nChannel = nChannel;
    pObj->m_nLoginCount = 1;
    pObj->m_uCreateTime = symphony::GetCurrentMS();

    if (m_bCrossChannel) {
        m_mapNameObj.insert(std::make_pair(strName, pObj));
    } else {
        m_mapNameObj.insert(std::make_pair(
            strName + CommonConvert::IntToString(nChannel), pObj));
    }

    m_ArrChangedAccount.push(pObj);

    return pObj;
}

bool CAccountObjectMgr::ReleaseAccountObject(uint64_t AccountID) {
    return Delete(AccountID);
}

bool CAccountObjectMgr::SealAccount(uint64_t& uAccountID,
                                    const std::string& strName,
                                    int32_t nChannel,
                                    bool bSeal,
                                    int32_t nSealTime,
                                    int32_t& nLastSvrID) {
    CAccountObject* pAccObj = NULL;
    if (uAccountID == 0) {
        pAccObj = GetAccountObject(strName, nChannel);
    } else {
        pAccObj = GetAccountObjectByID(uAccountID);
    }

    if (pAccObj == NULL) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "CAccountObjectMgr::SealAccount Error Cannot find account "
               "uAccountID:"
            << uAccountID << ", strName:" << strName;
        return false;
    }

    if (bSeal) {
        pAccObj->m_uSealTime = symphony::GetCurrentMS() + nSealTime;
        uAccountID = pAccObj->m_ID;
        nLastSvrID = pAccObj->m_nLastSvrID[0];
    } else {
        pAccObj->m_uSealTime = 0;
    }

    m_ArrChangedAccount.push(pAccObj);

    return true;
}

bool CAccountObjectMgr::SetLastServer(uint64_t uAccountID, int32_t ServerID) {
    if (uAccountID == 0) {
        return false;
    }

    CAccountObject* pAccObj = GetAccountObjectByID(uAccountID);
    if (pAccObj == nullptr) {
        return false;
    }

    if (pAccObj->m_nLastSvrID[0] == ServerID) {
        pAccObj->m_nLoginCount += 1;
        m_ArrChangedAccount.push(pAccObj);
        return true;
    }

    pAccObj->m_nLastSvrID[1] = pAccObj->m_nLastSvrID[0];
    pAccObj->m_nLastSvrID[0] = ServerID;
    m_ArrChangedAccount.push(pAccObj);

    return true;
}

CAccountObject* CAccountObjectMgr::AddAccountObject(uint64_t uAccountID,
                                                    const char* pStrName,
                                                    int32_t nChannel) {
    CAccountObject* pObj = InsertAlloc(uAccountID);
    if (pObj == nullptr) {
        return nullptr;
    }

    pObj->m_strName = pStrName;
    pObj->m_ID = uAccountID;
    pObj->m_nChannel = nChannel;

    if (m_bCrossChannel) {
        m_mapNameObj.insert(std::make_pair(pObj->m_strName, pObj));
    } else {
        m_mapNameObj.insert(std::make_pair(
            pObj->m_strName + CommonConvert::IntToString(nChannel), pObj));
    }

    return pObj;
}

bool CAccountObjectMgr::SaveAccountThread() {
    std::map<std::string, std::string> params;
    params["host"] = "127.0.0.1";
    params["user"] = "root";
    params["passwd"] = "123456";
    params["dbname"] = "db_game";

    symphony::MySQL::ptr m(new symphony::MySQL(params));
    if (!m->connect()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "SaveAccountChange Error: Can not open mysql database! Reason:"
            << m->getErrStr();
        SYMPHONY_LOG_ERROR(g_logger)
            << "SaveAccountChange Error: "
               "Host:[%s]-User:[%s]-Pwd:[%s]-DBName:[%s]"
            << params["host"] << params["user"] << params["passwd"]
            << params["dbname"];
        return false;
    }

    while (true) {
        CAccountObject* pAccount = NULL;

        if (m_ArrChangedAccount.size() <= 0) {
            if (!IsRun()) {
                return true;
            }

            CommonFunc::Sleep(100);
            continue;
        }

        if (!m->ping()) {
            if (!m->connect()) {
                CommonFunc::Sleep(1000);
                continue;
            }
        }

        while (m_ArrChangedAccount.front() != nullptr) {
            pAccount = m_ArrChangedAccount.front();
            std::string szSql =
                "replace into account(id, name, password, lastsvrid1, "
                "lastsvrid2, channel, create_time, seal_end_time, logincount) "
                "values(?,?,?,?,?,?,?,?,?)";
            symphony::MySQLStmt::ptr m_stmt =
                symphony::MySQLStmt::Create(m, szSql);
            m_stmt->bindInt64(1, pAccount->m_ID);
            m_stmt->bindString(2, pAccount->m_strName);
            m_stmt->bindString(3, pAccount->m_strPassword);
            m_stmt->bindInt32(4, pAccount->m_nLastSvrID[0]);
            m_stmt->bindInt32(5, pAccount->m_nLastSvrID[1]);
            m_stmt->bindInt32(6, pAccount->m_nChannel);
            m_stmt->bindString(
                7, CommonFunc::TimeToString(pAccount->m_uCreateTime));
            m_stmt->bindString(8,
                               CommonFunc::TimeToString(pAccount->m_uSealTime));
            m_stmt->bindInt32(9, pAccount->m_nLoginCount);

            if (m->execute(szSql) > 0) {
                continue;
            }

            SYMPHONY_LOG_ERROR(g_logger)
                << "CAccountMsgHandler::SaveAccountChange Failed! Reason: "
                << m->getErrStr();
            break;
        }
    }

    return true;
}

bool CAccountObjectMgr::Init() {
    if (!LoadCacheAccount()) {
        return false;
    }

    m_IsRun = true;

    m_pThread = new std::thread(&CAccountObjectMgr::SaveAccountThread, this);

    if (m_pThread == NULL) {
        return false;
    }

    return true;
}

bool CAccountObjectMgr::Uninit() {
    m_IsRun = false;

    if (m_pThread != NULL) {
        m_pThread->join();

        delete m_pThread;

        m_pThread = NULL;
    }

    m_mapNameObj.clear();

    Clear();

    return true;
}

bool CAccountObjectMgr::IsRun() {
    return m_IsRun;
}

bool CAccountObjectMgr::CheckAccountName(const std::string& strName,
                                         bool bFromChannel) {
    if (strName.size() < 1) {
        return false;
    }

    if (symphony::str_util::HasSymbol(strName.c_str(),
                                      (const char*)"\'\" \\\r\n%%")) {
        return false;
    }

    if (bFromChannel) {
        return true;
    }

    if (!std::regex_match(strName.c_str(), std::regex("([a-zA-Z0-9]+)"))) {
        return false;
    }

    return true;
}

CAccountObject* CAccountObjectMgr::GetAccountObject(const std::string& name,
                                                    int32_t nChannel) {
    if (m_bCrossChannel) {
        auto itor = m_mapNameObj.find(name);
        if (itor != m_mapNameObj.end()) {
            return itor->second;
        }
    } else {
        auto itor =
            m_mapNameObj.find(name + CommonConvert::IntToString(nChannel));
        if (itor != m_mapNameObj.end()) {
            return itor->second;
        }
    }

    return NULL;
}
}  // namespace as
}  // namespace symphony
