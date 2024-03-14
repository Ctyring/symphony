
#include "global_data_manager.h"
#include "data_pool.h"
#include "symphony/common/config_file.h"

CGlobalDataManager::CGlobalDataManager() {}

CGlobalDataManager::~CGlobalDataManager() {}

CGlobalDataManager* CGlobalDataManager::GetInstancePtr() {
    static CGlobalDataManager _StaticMgr;

    return &_StaticMgr;
}

BOOL CGlobalDataManager::LoadData(symphony::MySQL::ptr tDBConnection) {
    m_pGlobalDataObject =
        DataPool::CreateObject<GlobalDataObject>(ESD_GLOBAL, FALSE);
    m_pGlobalDataObject->Lock();
    m_pGlobalDataObject->m_dwServerID =
        CConfigFile::GetInstancePtr()->GetIntValue("areaid");

    CHAR szSql[SQL_BUFF_LEN] = {0};
    snprintf(szSql, SQL_BUFF_LEN,
             "select * from globaldata where serverid = %d",
             CConfigFile::GetInstancePtr()->GetIntValue("areaid"));

    auto stmt = tDBConnection->prepare(szSql);
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());

    if (res->next()) {
        m_pGlobalDataObject->m_u64Guid = res->getInt64Field("maxguid");
        m_pGlobalDataObject->m_dwMaxOnline = res->getIntField("maxonline");
        int nLen = 0;
        const unsigned char* pData = res->getBlobField("exdata", nLen);
        memcpy((void*)&m_pGlobalDataObject->m_exData, (void*)pData, nLen);
    }

    if (m_pGlobalDataObject->m_u64Guid <= 0) {
        m_pGlobalDataObject->m_u64Guid =
            CConfigFile::GetInstancePtr()->GetIntValue("areaid");
        m_pGlobalDataObject->m_u64Guid =
            (m_pGlobalDataObject->m_u64Guid << 48) + 1;
    }

    m_pGlobalDataObject->m_u64Guid += 100;

    m_pGlobalDataObject->Unlock();

    return TRUE;
}

UINT64 CGlobalDataManager::MakeNewGuid() {
    m_pGlobalDataObject->Lock();
    m_pGlobalDataObject->m_u64Guid += 1;
    m_pGlobalDataObject->Unlock();
    return m_pGlobalDataObject->m_u64Guid;
}

VOID CGlobalDataManager::SetMaxOnline(INT32 nNum) {
    m_pGlobalDataObject->Lock();
    m_pGlobalDataObject->m_dwMaxOnline = nNum;
    m_pGlobalDataObject->Unlock();
}

INT32 CGlobalDataManager::GetMaxOnline() {
    return m_pGlobalDataObject->m_dwMaxOnline;
}

BOOL CGlobalDataManager::SetExData(INT32 nIndex, INT32 dwData) {
    if (nIndex <= 0 || nIndex >= MAX_EXTRA_INDEX) {
        return FALSE;
    }

    m_pGlobalDataObject->Lock();
    m_pGlobalDataObject->m_exData[nIndex - 1] = dwData;
    m_pGlobalDataObject->Unlock();

    return TRUE;
}

INT32 CGlobalDataManager::GetExData(INT32 nIndex) {
    if (nIndex <= 0 || nIndex >= MAX_EXTRA_INDEX) {
        return 0;
    }

    return m_pGlobalDataObject->m_exData[nIndex - 1];
}