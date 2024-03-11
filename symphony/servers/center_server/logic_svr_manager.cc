
#include "symphony/servers/center_server/logic_svr_manager.h"

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");

CLogicSvrMgr::CLogicSvrMgr(void) {}

CLogicSvrMgr::~CLogicSvrMgr(void) {}

CLogicSvrMgr* CLogicSvrMgr::GetInstancePtr() {
    static CLogicSvrMgr _StaticMgr;

    return &_StaticMgr;
}

BOOL CLogicSvrMgr::Init() {
    return TRUE;
}

BOOL CLogicSvrMgr::Uninit() {
    for (auto itor = m_mapServer.begin(); itor != m_mapServer.end(); itor++) {
        LogicServerNode* pTempNode = itor->second;

        delete pTempNode;
    }

    m_mapServer.clear();

    return TRUE;
}

BOOL CLogicSvrMgr::RegisterLogicServer(INT32 nConnID,
                                       INT32 nServerID,
                                       std::string strSvrName) {
    LogicServerNode* pNode = GetLogicServerInfo(nServerID);
    if (pNode == NULL) {
        LogicServerNode* pTempNode = new LogicServerNode();
        pTempNode->m_nServerID = nServerID;
        pTempNode->m_nConnID = nConnID;
        pTempNode->m_strSvrName = strSvrName;
        m_mapServer.insert(std::make_pair(nServerID, pTempNode));
        return TRUE;
    }

    pNode->m_nConnID = nConnID;
    pNode->m_nServerID = nServerID;
    pNode->m_strSvrName = strSvrName;

    return TRUE;
}

BOOL CLogicSvrMgr::UnregisterLogicServer(INT32 nServerID) {
    LogicServerNode* pNode = GetLogicServerInfo(nServerID);
    if (pNode == NULL) {
        return TRUE;
    }

    pNode->m_nConnID = 0;

    return TRUE;
}

BOOL CLogicSvrMgr::OnCloseConnect(INT32 nConnID) {
    for (auto itor = m_mapServer.begin(); itor != m_mapServer.end(); ++itor) {
        LogicServerNode* pNode = itor->second;
        if (pNode == nullptr) {
            SYMPHONY_LOG_ERROR(g_logger)
                << "pNode is nullptr from CLogicSvrMgr::OnCloseConnect";
            continue;
        }

        if (pNode->m_nConnID == nConnID) {
            pNode->m_nConnID = 0;

            SYMPHONY_LOG_ERROR(g_logger)
                << "Lost Connect To Server:[" << pNode->m_nServerID << "] !";
        }
    }

    return TRUE;
}

INT32 CLogicSvrMgr::GetLogicConnID(INT32 nServerID) {
    LogicServerNode* pNode = GetLogicServerInfo(nServerID);
    if (pNode == NULL) {
        return 0;
    }

    return pNode->m_nConnID;
}

LogicServerNode* CLogicSvrMgr::GetLogicServerInfo(INT32 nServerID) {
    auto itor = m_mapServer.find(nServerID);
    if (itor != m_mapServer.end()) {
        return itor->second;
    }

    return NULL;
}