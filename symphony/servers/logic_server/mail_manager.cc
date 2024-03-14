#include "mail_manager.h"
#include "data_pool.h"
#include "global_data_manager.h"
#include "mail_module.h"
#include "player_manager.h"
#include "role_module.h"
#include "symphony/ds/mail_data.h"

CMailManager::CMailManager() {}

CMailManager::~CMailManager() {
    for (auto itor = m_mapOffMailData.begin(); itor != m_mapOffMailData.end();
         itor++) {
        itor->second->Release();
    }

    m_mapOffMailData.clear();

    for (auto itor = m_mapGroupMailData.begin();
         itor != m_mapGroupMailData.end(); itor++) {
        itor->second->Release();
    }

    m_mapGroupMailData.clear();
}

CMailManager* CMailManager::GetInstancePtr() {
    static CMailManager _StaticMgr;

    return &_StaticMgr;
}

BOOL CMailManager::SendGroupMail(std::string strSender,
                                 std::string strTitle,
                                 std::string strContent,
                                 std::vector<StMailItem>& vtItems,
                                 INT32 nRecvGroup) {
    if (nRecvGroup == 2) {
        CPlayerManager::TNodeTypePtr pNode =
            CPlayerManager::GetInstancePtr()->MoveFirst();
        if (pNode == NULL) {
            return false;
        }

        CPlayerObject* pTempObj = NULL;
        for (; pNode != NULL;
             pNode = CPlayerManager::GetInstancePtr()->MoveNext(pNode)) {
            pTempObj = pNode->GetValue();
            if (pTempObj == NULL) {
                continue;
            }

            if (!pTempObj->IsOnline()) {
                continue;
            }

            CMailModule* pMailModule =
                (CMailModule*)pTempObj->GetModuleByType(MT_MAIL);
            if (pMailModule == NULL) {
                continue;
            }

            pMailModule->AddMail(symphony::proto::EMT_CUSTOM, strSender,
                                 strTitle, strContent, vtItems);
        }

        return TRUE;
    }

    GroupMailDataObject* pGroupMailObject =
        DataPool::CreateObject<GroupMailDataObject>(ESD_GROUP_MAIL, TRUE);
    pGroupMailObject->Lock();
    pGroupMailObject->m_uGuid =
        CGlobalDataManager::GetInstancePtr()->MakeNewGuid();
    pGroupMailObject->m_nMailType = symphony::proto::EMT_CUSTOM;  // 邮件类型
    pGroupMailObject->m_uTime = CommonFunc::GetCurrTime();
    CommonConvert::StrCopy(pGroupMailObject->m_szTitle, strTitle.c_str(),
                           MAIL_TITLE_LEN);
    CommonConvert::StrCopy(pGroupMailObject->m_szContent, strContent.c_str(),
                           MAIL_CONTENT_LEN);
    CommonConvert::StrCopy(pGroupMailObject->m_szSender, strSender.c_str(),
                           ROLE_NAME_LEN);

    for (int i = 0; i < vtItems.size() && i < MAIL_ITEM_COUNT; i++) {
        if (vtItems.at(i).m_nItemID == 0) {
            break;
        }

        pGroupMailObject->m_Items[i] = vtItems.at(i);
    }

    pGroupMailObject->Unlock();

    m_mapGroupMailData.insert(
        std::make_pair(pGroupMailObject->m_uGuid, pGroupMailObject));

    CPlayerManager::TNodeTypePtr pNode =
        CPlayerManager::GetInstancePtr()->MoveFirst();
    if (pNode == NULL) {
        return false;
    }

    CPlayerObject* pTempObj = NULL;
    for (; pNode != NULL;
         pNode = CPlayerManager::GetInstancePtr()->MoveNext(pNode)) {
        pTempObj = pNode->GetValue();
        if (pTempObj == NULL) {
            return false;
        }

        if (!pTempObj->IsOnline()) {
            continue;
        }

        CMailModule* pMailModule =
            (CMailModule*)pTempObj->GetModuleByType(MT_MAIL);
        if (pMailModule == NULL) {
            return false;
        }

        pMailModule->ReceiveGroupMail(pGroupMailObject);
    }

    return TRUE;
}

BOOL CMailManager::SendSingleMail(UINT64 uRoleID,
                                  symphony::proto::EMailType eMailType,
                                  std::string strContent,
                                  std::vector<StMailItem>& vtItems,
                                  std::string strSender,
                                  std::string strTitle) {
    if (eMailType <= 0) {
        return false;
    }

    CPlayerObject* pPlayer =
        CPlayerManager::GetInstancePtr()->GetPlayer(uRoleID);
    if (pPlayer != NULL)  // 玩家在线，直接发给玩家数据
    {
        CMailModule* pMailModule =
            (CMailModule*)pPlayer->GetModuleByType(MT_MAIL);
        if (pMailModule == NULL) {
            return FALSE;
        }

        return pMailModule->AddMail(eMailType, strSender, strTitle, strContent,
                                    vtItems);
    }

    // 玩家不在线，放到离线内存数据内

    MailDataObject* pMailObject =
        DataPool::CreateObject<MailDataObject>(ESD_MAIL, TRUE);
    pMailObject->Lock();
    pMailObject->m_uGuid = CGlobalDataManager::GetInstancePtr()->MakeNewGuid();
    pMailObject->m_uRoleID = uRoleID;
    pMailObject->m_nMailType = eMailType;
    pMailObject->m_uTime = CommonFunc::GetCurrTime();
    CommonConvert::StrCopy(pMailObject->m_szTitle, strTitle.c_str(),
                           MAIL_TITLE_LEN);
    CommonConvert::StrCopy(pMailObject->m_szContent, strContent.c_str(),
                           MAIL_CONTENT_LEN);
    CommonConvert::StrCopy(pMailObject->m_szSender, strSender.c_str(),
                           ROLE_NAME_LEN);

    for (int i = 0; i < vtItems.size() && i < MAIL_ITEM_COUNT; i++) {
        if (vtItems.at(i).m_nItemID == 0) {
            break;
        }

        pMailObject->m_Items[i] = vtItems.at(i);
    }

    pMailObject->Unlock();

    m_mapOffMailData.insert(std::make_pair(pMailObject->m_uGuid, pMailObject));

    return TRUE;
}

BOOL CMailManager::SendOffOperation(UINT64 uRoleID) {
    return TRUE;
}

BOOL CMailManager::DeleteGroupMail(UINT64 uGuid) {
    auto itor = m_mapGroupMailData.find(uGuid);
    if (itor == m_mapGroupMailData.end()) {
        return FALSE;
    }

    GroupMailDataObject* pObject = itor->second;

    pObject->Destroy();

    m_mapGroupMailData.erase(itor);

    CPlayerManager::TNodeTypePtr pNode =
        CPlayerManager::GetInstancePtr()->MoveFirst();
    if (pNode == NULL) {
        return false;
    }

    CPlayerObject* pTempObj = NULL;
    for (; pNode != NULL;
         pNode = CPlayerManager::GetInstancePtr()->MoveNext(pNode)) {
        pTempObj = pNode->GetValue();
        if (pTempObj == NULL) {
            continue;
        }

        CMailModule* pMailModule =
            (CMailModule*)pTempObj->GetModuleByType(MT_MAIL);
        if (pMailModule == NULL) {
            continue;
        }

        pMailModule->DeleteMailByGroupID(uGuid);
    }

    return TRUE;
}

BOOL CMailManager::LoadData(symphony::MySQL::ptr pdb) {
    if (LoadGroupMailData(pdb) == FALSE) {
        return FALSE;
    }

    return TRUE;
}

BOOL CMailManager::LoadGroupMailData(symphony::MySQL::ptr pdb) {
    std::string szSql = "SELECT * FROM mail_group";
    auto stmt = pdb->prepare(szSql);
    if (!stmt) {
        return FALSE;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    while (res->next()) {
        GroupMailDataObject* pGroupMail =
            DataPool::CreateObject<GroupMailDataObject>(ESD_GROUP_MAIL, FALSE);
        pGroupMail->m_nMailType = symphony::proto::EMT_CUSTOM;  // 邮件类型
        pGroupMail->m_nChannel = res->getIntField("channel");
        pGroupMail->m_uGuid = res->getInt64Field("id");
        pGroupMail->m_uTime = res->getInt64Field("mail_time");
        CommonConvert::StrCopy(pGroupMail->m_szTitle,
                               res->getStringField("title"), MAIL_TITLE_LEN);
        CommonConvert::StrCopy(pGroupMail->m_szContent,
                               res->getStringField("content"),
                               MAIL_CONTENT_LEN);
        CommonConvert::StrCopy(pGroupMail->m_szSender,
                               res->getStringField("sender"), ROLE_NAME_LEN);

        INT32 nLen = 0;
        const unsigned char* pData = res->getBlobField("itemdata", nLen);
        memcpy((void*)&pGroupMail->m_Items, (void*)pData, nLen);

        m_mapGroupMailData.insert(
            std::make_pair(pGroupMail->m_uGuid, pGroupMail));
    }

    return TRUE;
}

BOOL CMailManager::ProcessRoleLogin(CPlayerObject* pPlayer) {
    CRoleModule* pRoleModule = (CRoleModule*)pPlayer->GetModuleByType(MT_ROLE);
    if (pRoleModule == NULL) {
        return FALSE;
    }

    for (auto itor = m_mapGroupMailData.begin();
         itor != m_mapGroupMailData.end(); ++itor) {
        GroupMailDataObject* pGroupMailObject = itor->second;
        if (pGroupMailObject == NULL) {
            return false;
        }

        if (pGroupMailObject->m_uTime > pRoleModule->GetGroupMailTime()) {
            CMailModule* pMailModule =
                (CMailModule*)pPlayer->GetModuleByType(MT_MAIL);
            if (pMailModule == NULL) {
                return false;
            }

            pMailModule->ReceiveGroupMail(pGroupMailObject);
        }
    }

    return TRUE;
}

MailDataObject* CMailManager::PickUpMailData(UINT64 uGuid) {
    MailDataObject* pObject = NULL;
    auto itor = m_mapOffMailData.find(uGuid);
    if (itor != m_mapOffMailData.end()) {
        pObject = itor->second;
        m_mapOffMailData.erase(itor);
    }

    return pObject;
}