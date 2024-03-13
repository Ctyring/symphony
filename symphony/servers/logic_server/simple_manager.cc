#include "simple_manager.h"
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");
CSimpleManager::CSimpleManager() {}

CSimpleManager::~CSimpleManager() {}

CSimpleManager* CSimpleManager::GetInstancePtr() {
    static CSimpleManager _StaticMgr;

    return &_StaticMgr;
}

BOOL CSimpleManager::LoadData(symphony::MySQL::ptr pDB) {
    std::string sql = "SELECT * FROM player";
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(pDB->query(sql));
    while (!res->next()) {
        CSimpleInfo* pInfo = new CSimpleInfo();
        pInfo->m_uRoleID = res->getInt64Field("id");
        pInfo->m_uAccountID = res->getInt64Field("accountid");
        pInfo->m_strName = res->getStringField("name");
        pInfo->m_dwCarrerID = res->getIntField("carrerid");
        pInfo->m_uCreateTime = res->getInt64Field("createtime");
        pInfo->m_uLogonTime = res->getInt64Field("logontime");
        pInfo->m_uLogoffTime = res->getInt64Field("logofftime");
        pInfo->m_uGuildID = res->getInt64Field("guildid");
        pInfo->m_dwLevel = res->getIntField("level");
        pInfo->m_dwVipLevel = res->getIntField("viplevel");

        AddSimpleInfo(pInfo);
    }

    return TRUE;
}

UINT64 CSimpleManager::GetRoleIDByName(std::string Name) {
    std::map<std::string, UINT64>::iterator itor = m_mapName2ID.find(Name);
    if (itor != m_mapName2ID.end()) {
        return itor->second;
    }

    return 0;
}

CSimpleInfo* CSimpleManager::GetSimpleInfoByID(UINT64 u64ID) {
    std::map<UINT64, CSimpleInfo*>::iterator itor = m_mapID2Simple.find(u64ID);
    if (itor != m_mapID2Simple.end()) {
        return itor->second;
    }

    return NULL;
}

UINT64 CSimpleManager::GetCreateTime(UINT64 u64ID) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return 0;
    }

    return pInfo->m_uCreateTime;
}

UINT64 CSimpleManager::GetLogonTime(UINT64 u64ID) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return 0;
    }

    return pInfo->m_uLogonTime;
}

UINT64 CSimpleManager::GetLogoffTime(UINT64 u64ID) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return 0;
    }

    return pInfo->m_uLogoffTime;
}

UINT64 CSimpleManager::GetFightValue(UINT64 u64ID) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return 0;
    }

    return pInfo->m_uFightValue;
}

BOOL CSimpleManager::SetFightValue(UINT64 u64ID,
                                   UINT64 uFight,
                                   UINT32 dwLevel) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return false;
    }

    pInfo->m_uFightValue = uFight;
    pInfo->m_dwLevel = dwLevel;

    return TRUE;
}

BOOL CSimpleManager::SetName(UINT64 u64ID, std::string strName) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return false;
    }

    auto itor = m_mapName2ID.find(pInfo->m_strName);
    if (itor != m_mapName2ID.end()) {
        m_mapName2ID.erase(itor);
    }

    pInfo->m_strName = strName;
    auto ret = m_mapName2ID.insert(std::make_pair(strName, pInfo->m_uRoleID));
    if (!ret.second) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "CSimpleManager::SetName Error Role Name :"
            << pInfo->m_strName.c_str() << " already exist!";
        return FALSE;
    }

    return TRUE;
}

BOOL CSimpleManager::SetLogoffTime(UINT64 u64ID, UINT64 uTime) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return false;
    }

    pInfo->m_uLogoffTime = uTime;

    return TRUE;
}

BOOL CSimpleManager::SetCreateTime(UINT64 u64ID, UINT64 uTime) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return false;
    }

    pInfo->m_uCreateTime = uTime;

    return TRUE;
}

BOOL CSimpleManager::SetLogonTime(UINT64 u64ID, UINT64 uTime) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return false;
    }

    pInfo->m_uLogonTime = uTime;

    return TRUE;
}

BOOL CSimpleManager::SetVipLevel(UINT64 u64ID, UINT32 dwVipLvl) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return false;
    }

    pInfo->m_dwVipLevel = dwVipLvl;

    return TRUE;
}

BOOL CSimpleManager::SetGuildID(UINT64 u64ID, UINT64 guildid) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return false;
    }

    pInfo->m_uGuildID = guildid;

    return TRUE;
}

BOOL CSimpleManager::SetRoleDelete(UINT64 u64ID, BOOL bDelete) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return false;
    }

    pInfo->m_IsDelete = bDelete;

    return TRUE;
}

BOOL CSimpleManager::CheckNameExist(std::string strName) {
    auto itor = m_mapName2ID.find(strName);
    if (itor != m_mapName2ID.end()) {
        return TRUE;
    }

    return FALSE;
}

BOOL CSimpleManager::CheckNameFormat(std::string strName) {
    if (strName.size() > (ROLE_NAME_LEN - 30)) {
        return FALSE;
    }

    if (strName.size() < 4) {
        return FALSE;
    }

    if (CommonConvert::HasSymbol(strName.c_str(),
                                 (const char*)",;\'\" \\%%\r\n")) {
        return FALSE;
    }

    return TRUE;
}

UINT64 CSimpleManager::GetGuildID(UINT64 u64ID) {
    CSimpleInfo* pInfo = GetSimpleInfoByID(u64ID);
    if (pInfo == NULL) {
        return false;
    }
    return pInfo->m_uGuildID;
}

UINT32 CSimpleManager::GetTotalCount() {
    return (INT32)m_mapID2Simple.size();
}

BOOL CSimpleManager::GetRoleIDsByAccountID(UINT64 uAccountID,
                                           std::vector<UINT64>& vtRoleIDs) {
    for (auto itor = m_mapID2Simple.begin(); itor != m_mapID2Simple.end();
         ++itor) {
        CSimpleInfo* pInfo = itor->second;
        if (pInfo == NULL) {
            return false;
        }

        if (pInfo->m_uAccountID == uAccountID) {
            vtRoleIDs.push_back(pInfo->m_uRoleID);
        }
    }

    return TRUE;
}

CSimpleInfo* CSimpleManager::CreateSimpleInfo(UINT64 u64ID,
                                              UINT64 u64AccID,
                                              std::string strName,
                                              UINT32 dwCarrerID) {
    CSimpleInfo* pInfo = new CSimpleInfo();
    pInfo->m_uRoleID = u64ID;
    pInfo->m_uAccountID = u64AccID;
    pInfo->m_strName = strName;
    pInfo->m_dwCarrerID = dwCarrerID;
    pInfo->m_uCreateTime = CommonFunc::GetCurrTime();
    pInfo->m_dwVipLevel = 0;
    pInfo->m_dwLevel = 0;
    pInfo->m_uFightValue = 0;

    m_mapID2Simple.insert(std::make_pair(u64ID, pInfo));

    m_mapName2ID.insert(std::make_pair(strName, u64ID));

    return pInfo;
}

BOOL CSimpleManager::AddSimpleInfo(CSimpleInfo* pInfo) {
    if (pInfo == NULL) {
        return false;
    }

    m_mapID2Simple.insert(std::make_pair(pInfo->m_uRoleID, pInfo));

    auto ret =
        m_mapName2ID.insert(std::make_pair(pInfo->m_strName, pInfo->m_uRoleID));

    if (!ret.second) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "CSimpleManager::AddSimpleInfo Error Role Name :"
            << pInfo->m_strName.c_str() << " already exist!";
    }

    return TRUE;
}