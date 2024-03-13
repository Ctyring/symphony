// #include "ConfigFile.h"
#include "static_data.h"
#include <tinyxml2.h>
#include "symphony/log.h"
// #include "RapidXml.h"
// #include "stdafx.h"
// #include "DBInterface/CppMysql.h"
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");
CStaticData::CStaticData() {
    InitDataReader();
}

CStaticData::~CStaticData() {}

CStaticData* CStaticData::GetInstancePtr() {
    static CStaticData _StaticMgr;

    return &_StaticMgr;
}

BOOL CStaticData::InitDataReader() {
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Constant", &CStaticData::ReadConstantData));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Role", &CStaticData::ReadCarrer));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_RoleLevel", &CStaticData::ReadCarrerLevel));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Actor", &CStaticData::ReadActor));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Copy", &CStaticData::ReadCopyInfo));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Item", &CStaticData::ReadItemData));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Action", &CStaticData::ReadActionCfg));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Actor_Skill", &CStaticData::ReadActorSkillInfo));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Equip", &CStaticData::ReadEquipInfo));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Gem", &CStaticData::ReadGemInfo));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Partner", &CStaticData::ReadPartnerInfo));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Mount", &CStaticData::ReadMountInfo));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Store", &CStaticData::ReadStoreInfo));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Combo_Skill", &CStaticData::ReadComboSkillInfo));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Skill", &CStaticData::ReadSkillInfo));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_FlyObject", &CStaticData::ReadBulletInfo));
    m_vtDataFuncList.push_back(
        DataFuncNode("Data_Pet", &CStaticData::ReadPetInfo));

    //  m_vtDataFuncList.push_back(DataFuncNode("Data_Language",
    //  &CStaticData::ReadLanguage));
    //  m_vtDataFuncList.push_back(DataFuncNode("Data_Award",
    //  &CStaticData::ReadAwardData));
    //  m_vtDataFuncList.push_back(DataFuncNode("Data_Func",
    //  &CStaticData::ReadFuncInfo));
    //  m_vtDataFuncList.push_back(DataFuncNode("Data_Func_Vip",
    //  &CStaticData::ReadFuncVipInfo));
    //  m_vtDataFuncList.push_back(DataFuncNode("Data_Func_Cost",
    //  &CStaticData::ReadFuncCostInfo));
    //  m_vtDataFuncList.push_back(DataFuncNode("Data_Task",
    //  &CStaticData::ReadTaskInfo));
    //  m_vtDataFuncList.push_back(DataFuncNode("Data_Buff",
    //  &CStaticData::ReadBuffInfo));

    return TRUE;
}

BOOL CStaticData::LoadConfigData(std::string strDbFile) {
#define SQLITE_TYPE 1
#ifdef SQLITE_TYPE
    try {
        std::map<std::string, std::string> params;
        params["host"] = "127.0.0.1";
        params["user"] = "root";
        params["passwd"] = "123456";
        params["dbname"] = strDbFile;
        symphony::MySQL::ptr tDBConnection(new symphony::MySQL(params));
        char szSql[SQL_BUFF_LEN] = {0};
        for (std::vector<DataFuncNode>::iterator itor =
                 m_vtDataFuncList.begin();
             itor != m_vtDataFuncList.end(); itor++) {
            DataFuncNode dataNode = (*itor);
            snprintf(szSql, SQL_BUFF_LEN, "select * from %s;",
                     dataNode.m_strTbName.c_str());
            auto stmt = symphony::MySQLStmt::Create(tDBConnection, szSql);
            auto res =
                std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
            (this->*dataNode.m_pDataFunc)(res);
        }
        tDBConnection->close();
    } catch (...) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "CConfigData::LoadConfigData Failed!!!,";
        return FALSE;
    }
#else
    std::string strHost =
        CConfigFile::GetInstancePtr()->GetStringValue("mysql_type_svr_ip");
    INT32 nPort =
        CConfigFile::GetInstancePtr()->GetIntValue("mysql_type_svr_port");
    std::string strUser =
        CConfigFile::GetInstancePtr()->GetStringValue("mysql_type_svr_user");
    std::string strPwd =
        CConfigFile::GetInstancePtr()->GetStringValue("mysql_type_svr_pwd");
    std::string strDb =
        CConfigFile::GetInstancePtr()->GetStringValue("mysql_type_svr_db_name");

    CppMySQL3DB tDBConnection;
    if (!tDBConnection.open(strHost.c_str(), strUser.c_str(), strPwd.c_str(),
                            strDb.c_str(), nPort)) {
        CLog::GetInstancePtr()->LogError(
            "Error: Can not open mysql database! Reason:%s",
            tDBConnection.GetErrorMsg());
        return FALSE;
    }
    char szSql[SQL_BUFF_LEN] = {0};
    for (std::vector<DataFuncNode>::iterator itor = m_vtDataFuncList.begin();
         itor != m_vtDataFuncList.end(); itor++) {
        DataFuncNode dataNode = (*itor);
        snprintf(szSql, SQL_BUFF_LEN, "select * from %s;",
                 dataNode.m_strTbName.c_str());
        CppMySQLQuery Tabledatas = tDBConnection.querySQL(szSql);
        (this->*dataNode.m_pDataFunc)(Tabledatas);
    }
    tDBConnection.close();
#endif
    ReadSkillEvent();

    return TRUE;
}

BOOL CStaticData::ReloadConfigData(std::string strTbName) {
    try {
        std::map<std::string, std::string> params;
        params["host"] = "127.0.0.1";
        params["user"] = "root";
        params["passwd"] = "123456";
        params["dbname"] = "Config.db";
        symphony::MySQL::ptr tDBConnection(new symphony::MySQL(params));
        char szSql[SQL_BUFF_LEN] = {0};
        for (std::vector<DataFuncNode>::iterator itor =
                 m_vtDataFuncList.begin();
             itor != m_vtDataFuncList.end(); itor++) {
            DataFuncNode dataNode = (*itor);
            if (dataNode.m_strTbName != strTbName) {
                continue;
            }

            snprintf(szSql, SQL_BUFF_LEN, "select * from %s;",
                     dataNode.m_strTbName.c_str());

            auto stmt = symphony::MySQLStmt::Create(tDBConnection, szSql);
            auto res =
                std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
            (this->*dataNode.m_pDataFunc)(res);
        }

        tDBConnection->close();
    } catch (...) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "CConfigData::ReloadConfigData Failed!!!,";
        return FALSE;
    }

    return TRUE;
}

BOOL CStaticData::ReadConstantData(symphony::MySQLRes::ptr QueryData) {
    m_mapConstantValue.clear();
    while (QueryData->next()) {
        std::string strName = QueryData->getStringField("name");
        std::string strValue = QueryData->getStringField("value");

        m_mapConstantValue.insert(std::make_pair(
            strName, CommonConvert::StringToInt(strValue.c_str())));
    }

    return TRUE;
}

INT32 CStaticData::GetConstantValue(std::string& strName) {
    std::map<std::string, INT32>::iterator itor =
        m_mapConstantValue.find(strName);
    if (itor != m_mapConstantValue.end()) {
        return itor->second;
    }

    return 0;
}

INT32 CStaticData::GetConstantValue(char* pszName) {
    std::map<std::string, INT32>::iterator itor =
        m_mapConstantValue.find(pszName);
    if (itor != m_mapConstantValue.end()) {
        return itor->second;
    }

    return 0;
}

INT64 CStaticData::GetActoinMaxValue(UINT32 dwActionID) {
    if ((dwActionID <= 0) || (dwActionID >= m_vtActionList.size())) {
        return 1;
    }

    return m_vtActionList.at(dwActionID - 1).dwMax;
}

UINT32 CStaticData::GetActoinUnitTime(UINT32 dwActionID) {
    if ((dwActionID <= 0) || (dwActionID >= m_vtActionList.size())) {
        return 1;
    }

    return m_vtActionList.at(dwActionID - 1).UnitTime;
}

BOOL CStaticData::ReadCarrer(symphony::MySQLRes::ptr QueryData) {
    m_mapCarrer.clear();

    while (QueryData->next()) {
        StCarrerInfo stValue;
        stValue.dwID = QueryData->getIntField("Carrer");
        stValue.dwActorID = QueryData->getIntField("ActorID");
        stValue.dwBornCity = QueryData->getIntField("BornCity");
        m_mapCarrer.insert(std::make_pair(stValue.dwID, stValue));
    }

    return TRUE;
}

StCarrerInfo* CStaticData::GetCarrerInfo(UINT32 dwCarrerID) {
    std::map<UINT32, StCarrerInfo>::iterator itor =
        m_mapCarrer.find(dwCarrerID);

    if (itor == m_mapCarrer.end()) {
        return NULL;
    }

    return &itor->second;
}

BOOL CStaticData::ReadActionCfg(symphony::MySQLRes::ptr QueryData) {
    m_vtActionList.clear();
    while (QueryData->next()) {
        StActionInfo stValue;
        stValue.dwActionID = QueryData->getIntField("Id");
        stValue.dwMax = QueryData->getIntField("Max");
        stValue.UnitTime = QueryData->getIntField("UnitTime");
        m_vtActionList.push_back(stValue);
    }

    return TRUE;
}

BOOL CStaticData::ReadCarrerLevel(symphony::MySQLRes::ptr QueryData) {
    while (QueryData->next()) {
        UINT32 dwCarrerID = QueryData->getIntField("Carrer");
        UINT32 dwLevel = QueryData->getIntField("Level");
        m_CarrerLevel[dwCarrerID - 1][dwLevel - 1].dwLevel = dwLevel;
        m_CarrerLevel[dwCarrerID - 1][dwLevel - 1].dwFightValue =
            QueryData->getIntField("FightValue");
        m_CarrerLevel[dwCarrerID - 1][dwLevel - 1].dwNeedExp =
            QueryData->getIntField("RequireExp");

        int nIndex = QueryData->fieldIndex("P1");
        for (int i = 0; i < 20; i++) {
            m_CarrerLevel[dwCarrerID - 1][dwLevel - 1].Propertys[i] =
                QueryData->getIntField(i + nIndex, 0);
        }
    }

    return TRUE;
}

StLevelInfo* CStaticData::GetCarrerLevelInfo(UINT32 dwCarrerID,
                                             UINT32 dwLevel) {
    return &m_CarrerLevel[dwCarrerID - 1][dwLevel - 1];
}

BOOL CStaticData::ReadActor(symphony::MySQLRes::ptr QueryData) {
    m_mapActor.clear();

    while (QueryData->next()) {
        StActorInfo stValue;
        stValue.dwID = QueryData->getIntField("Id");
        stValue.InitLevel = QueryData->getIntField("Level");
        stValue.fDefSpeed = QueryData->getFloatField("DefSpeed");
        stValue.fRadius = QueryData->getFloatField("Radius");
        stValue.dwType = QueryData->getIntField("Type");
        stValue.AiID = QueryData->getIntField("AiId");
        int nIndex = QueryData->fieldIndex("P1");
        for (int i = 0; i < PROPERTY_NUM; i++) {
            stValue.Propertys[i] = QueryData->getIntField(i + nIndex, 0);
        }

        m_mapActor.insert(std::make_pair(stValue.dwID, stValue));
    }

    return TRUE;
}

StActorInfo* CStaticData::GetActorInfo(UINT32 dwActorID) {
    if (dwActorID == 0) {
        return NULL;
    }

    std::map<UINT32, StActorInfo>::iterator itor = m_mapActor.find(dwActorID);
    if (itor != m_mapActor.end()) {
        return &itor->second;
    }
    return NULL;
}

BOOL CStaticData::ReadActorSkillInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapActorSkill.clear();

    while (QueryData->next()) {
        StActorSkillInfo stValue;
        stValue.dwActorID = QueryData->getIntField("Id");
        stValue.NormalID = QueryData->getIntField("Normal1");
        stValue.Specials[0] = QueryData->getIntField("Special1");
        stValue.Specials[1] = QueryData->getIntField("Special2");
        stValue.Specials[2] = QueryData->getIntField("Special3");
        stValue.Specials[3] = QueryData->getIntField("Special4");
        stValue.Specials[4] = QueryData->getIntField("Special5");
        m_mapActorSkill.insert(std::make_pair(stValue.dwActorID, stValue));
    }

    return TRUE;
}

StActorSkillInfo* CStaticData::GetActorSkillInfo(UINT32 dwActorID) {
    if (dwActorID == 0) {
        return NULL;
    }
    std::map<UINT32, StActorSkillInfo>::iterator itor =
        m_mapActorSkill.find(dwActorID);
    if (itor != m_mapActorSkill.end()) {
        return &itor->second;
    }
    return NULL;
}

BOOL CStaticData::ReadCopyInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapCopyInfo.clear();

    while (QueryData->next()) {
        StCopyInfo stValue;
        stValue.dwCopyID = QueryData->getIntField("Id");
        stValue.dwCopyType = QueryData->getIntField("CopyType");
        stValue.dwCostActID = QueryData->getIntField("CostActionId");
        stValue.dwCostActNum = QueryData->getIntField("CostActionNum");
        stValue.dwGetMoneyID = QueryData->getIntField("GetMoneyId");
        stValue.dwGetMoneyRatio = QueryData->getIntField("GetMoneyRatio");
        m_mapCopyInfo.insert(std::make_pair(stValue.dwCopyID, stValue));
    }

    return TRUE;
}

StCopyInfo* CStaticData::GetCopyInfo(UINT32 dwCopyID) {
    if (dwCopyID == 0) {
        return NULL;
    }
    std::map<UINT32, StCopyInfo>::iterator itor = m_mapCopyInfo.find(dwCopyID);
    if (itor != m_mapCopyInfo.end()) {
        return &itor->second;
    }
    return NULL;
}

UINT32 CStaticData::GetCopyType(UINT32 dwCopyID) {
    StCopyInfo* pCopyInfo = GetCopyInfo(dwCopyID);
    if (pCopyInfo == NULL) {
        return 0;
    }

    return pCopyInfo->dwCopyType;
}

BOOL CStaticData::ReadLanguage(symphony::MySQLRes::ptr QueryData) {
    m_mapLanguage.clear();

    while (QueryData->next()) {
        StLocalString stValue;
        stValue.dwID = QueryData->getIntField("id");
        stValue.Language[0] = QueryData->getIntField("lang0");
        stValue.Language[1] = QueryData->getIntField("lang1");
        stValue.Language[2] = QueryData->getIntField("lang2");
        stValue.Language[3] = QueryData->getIntField("lang3");
        stValue.Language[4] = QueryData->getIntField("lang4");
        stValue.Language[5] = QueryData->getIntField("lang5");
        stValue.Language[6] = QueryData->getIntField("lang6");
        stValue.Language[7] = QueryData->getIntField("lang7");
        stValue.Language[8] = QueryData->getIntField("lang8");
        stValue.Language[9] = QueryData->getIntField("lang9");
        stValue.Language[10] = QueryData->getIntField("lang10");
        stValue.Language[11] = QueryData->getIntField("lang11");
        stValue.Language[12] = QueryData->getIntField("lang12");
        stValue.Language[13] = QueryData->getIntField("lang13");
        stValue.Language[14] = QueryData->getIntField("lang14");
        m_mapLanguage.insert(std::make_pair(stValue.dwID, stValue));
    }

    return TRUE;
}

std::string& CStaticData::GetLanguageText(UINT32 dwID, UINT32 dwLang) {
    static std::string strNull = "null";

    if ((dwLang < 0) || (dwLang > 14)) {
        return strNull;
    }

    std::map<UINT32, StLocalString>::iterator itor = m_mapLanguage.find(dwID);
    if (itor != m_mapLanguage.end()) {
        return itor->second.Language[dwLang];
    }

    return strNull;
}

std::string& CStaticData::GetLanguageText(std::string strID, UINT32 dwLang) {
    static std::string strNull = "null";
    return strNull;
}

BOOL CStaticData::ReadAwardData(symphony::MySQLRes::ptr QueryData) {
    m_mapAwardItem.clear();

    while (QueryData->next()) {
        StAwardItem stValue;
        stValue.dwAwardID = QueryData->getIntField("awardid");
        std::string strFixDrop = QueryData->getStringField(2);
        std::string strRatioDrop = QueryData->getStringField(4);
        stValue.bDistinct = QueryData->getIntField(4);
        stValue.dwRatioCount = QueryData->getIntField(4);
        // 解析固定掉落
        if (strFixDrop != "NULL") {
            std::vector<std::string> vtRet;
            CommonConvert::SpliteString(strFixDrop, ")(", vtRet);
            for (std::vector<std::string>::size_type i = 0; i < vtRet.size();
                 i++) {
                StDropItem item;
                ParseToDropItem(vtRet.at(i), item);
                stValue.FixItems.push_back(item);
            }
        }

        if (strRatioDrop != "NULL") {
            std::vector<std::string> vtRet;
            CommonConvert::SpliteString(strFixDrop, ")(", vtRet);

            INT32 nCheckRatio = 0;

            StDropItem item;
            for (std::vector<std::string>::size_type i = 0; i < vtRet.size();
                 i++) {
                ParseToDropItem(vtRet.at(i), item);
                stValue.RatioItems.push_back(item);
                nCheckRatio += item.dwRatio;
            }

            if (nCheckRatio != 10000) {
                SYMPHONY_LOG_ERROR(g_logger)
                    << "ReadAwardData Error: Invalid awardid :"
                    << stValue.dwAwardID;
            }
        }

        if ((stValue.FixItems.size() <= 0) &&
            (stValue.RatioItems.size() <= 0)) {
        }

        auto itor = m_mapAwardItem.find(stValue.dwAwardID);
        if (itor != m_mapAwardItem.end()) {
            std::vector<StAwardItem>& vtList = itor->second;

            vtList.push_back(stValue);
        } else {
            std::vector<StAwardItem> vtList;
            vtList.push_back(stValue);
            m_mapAwardItem.insert(std::make_pair(stValue.dwAwardID, vtList));
        }
    }

    return TRUE;
}

BOOL CStaticData::ParseToDropItem(std::string strDrop, StDropItem& item) {
    std::vector<std::string> vtRet;
    CommonConvert::SpliteString(strDrop, "|", vtRet);
    if (vtRet.size() < 3) {
        return FALSE;
    }

    item.dwItemID = CommonConvert::StringToInt(vtRet[0].c_str());
    item.dwRatio = CommonConvert::StringToInt(vtRet[2].c_str());
    CommonConvert::SpliteString(vtRet[1], "|", vtRet);
    item.dwItemNum[0] = CommonConvert::StringToInt(vtRet[0].c_str());
    item.dwItemNum[1] = CommonConvert::StringToInt(vtRet[1].c_str());

    return TRUE;
}

BOOL CStaticData::GetAwardItem(INT32 nAwardID,
                               INT32 nCarrer,
                               StAwardItem& AwardItem) {
    std::map<UINT32, std::vector<StAwardItem>>::iterator itor =
        m_mapAwardItem.find(nAwardID);
    if (itor == m_mapAwardItem.end()) {
        return FALSE;
    }

    std::vector<StAwardItem>& AwardItemList = itor->second;

    for (std::vector<StAwardItem>::size_type i = 0; i < AwardItemList.size();
         i++) {
        AwardItem = AwardItemList.at(i);
        if (AwardItem.nCarrer == nCarrer) {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL CStaticData::GetAwardItemByIndex(INT32 nAwardID,
                                      INT32 nCarrer,
                                      INT32 nIndex,
                                      StItemData& ItemData) {
    StAwardItem AwardItem;

    if (!GetAwardItem(nAwardID, nCarrer, AwardItem)) {
        return FALSE;
    }

    if (nIndex >= (INT32)AwardItem.FixItems.size()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "GetItemByIndex Error: Invalid index :" << nIndex;
        return FALSE;
    }

    ItemData.dwItemID = AwardItem.FixItems[nIndex].dwItemID;
    ItemData.dwItemNum = AwardItem.FixItems[nIndex].dwItemNum[0];
    return TRUE;
}

BOOL CStaticData::GetItemsFromAwardID(INT32 nAwardID,
                                      INT32 nCarrer,
                                      std::vector<StItemData>& vtItemList) {
    StAwardItem AwardItem;

    if (!GetAwardItem(nAwardID, nCarrer, AwardItem)) {
        return FALSE;
    }

    StItemData tempItem;

    for (std::vector<StDropItem>::size_type i = 0;
         i < AwardItem.FixItems.size(); i++) {
        tempItem.dwItemID = AwardItem.FixItems[i].dwItemID;
        if (AwardItem.FixItems[i].dwItemNum[0] ==
            AwardItem.FixItems[i].dwItemNum[1]) {
            tempItem.dwItemNum = AwardItem.FixItems[i].dwItemNum[0];
        } else {
            tempItem.dwItemNum = AwardItem.FixItems[i].dwItemNum[0] +
                                 CommonFunc::GetRandNum(0) %
                                     (AwardItem.FixItems[i].dwItemNum[1] -
                                      AwardItem.FixItems[i].dwItemNum[0] + 1);
        }

        if (tempItem.dwItemNum > 0) {
            vtItemList.push_back(tempItem);
        }
    }

    // 多次可取到同样的物品
    for (int cycle = 0; cycle < AwardItem.dwRatioCount; cycle++) {
        UINT32 dwRandValue = CommonFunc::GetRandNum(0);
        for (std::vector<StDropItem>::size_type i = 0;
             i < AwardItem.RatioItems.size() - 1; i++) {
            if (dwRandValue <= AwardItem.RatioItems[i].dwRatio) {
                tempItem.dwItemID = AwardItem.RatioItems[i].dwItemID;
                if (AwardItem.RatioItems[i].dwItemNum[1] ==
                    AwardItem.RatioItems[i].dwItemNum[0]) {
                    tempItem.dwItemNum = AwardItem.RatioItems[i].dwItemNum[0];
                } else {
                    tempItem.dwItemNum =
                        AwardItem.RatioItems[i].dwItemNum[0] +
                        CommonFunc::GetRandNum(0) %
                            (AwardItem.RatioItems[i].dwItemNum[1] -
                             AwardItem.RatioItems[i].dwItemNum[0] + 1);
                }

                if (tempItem.dwItemNum > 0) {
                    vtItemList.push_back(tempItem);
                }
            } else {
                dwRandValue -= AwardItem.RatioItems[i].dwRatio;
            }
        }
    }

    // 确保多次都取到不同样的物品
    /*
    bool UsedFlag[100] = { 0 };
    UINT32 UsedValue = 0;
    for (int cycle = 0; cycle < AwardItem.dwRatioCount; cycle++)
    {
        UINT32 dwRandValue = CommonFunc::GetRandNum(0) - UsedValue;
        for (std::vector<StDropItem>::size_type i = 0; i <
    AwardItem.RatioItems.size() - 1; i++)
        {
            if (UsedFlag[i])
            {
                continue;
            }

            if (dwRandValue <= AwardItem.RatioItems[i].dwRatio)
            {
                tempItem.dwItemID = AwardItem.RatioItems[i].dwItemID;
                if (AwardItem.RatioItems[i].dwItemNum[1] ==
    AwardItem.RatioItems[i].dwItemNum[0])
                {
                    tempItem.dwItemNum = AwardItem.RatioItems[i].dwItemNum[0];
                }
                else
                {
                    tempItem.dwItemNum = AwardItem.RatioItems[i].dwItemNum[0] +
    CommonFunc::GetRandNum(0) % (AwardItem.RatioItems[i].dwItemNum[1] -
    AwardItem.RatioItems[i].dwItemNum[0] + 1);
                }

                if (tempItem.dwItemNum > 0)
                {
                    vtItemList.push_back(tempItem);
                    UsedFlag[i] = true;
                    UsedValue += AwardItem.RatioItems[i].dwRatio;
                }
            }
            else
            {
                dwRandValue -= AwardItem.RatioItems[i].dwRatio;
            }
        }
    }
    */

    return TRUE;
}

BOOL CStaticData::GetItemsAwardIDTimes(INT32 nAwardID,
                                       INT32 nCarrer,
                                       INT32 nTimes,
                                       std::vector<StItemData>& vtItemList) {
    StAwardItem AwardItem;

    if (!GetAwardItem(nAwardID, nCarrer, AwardItem)) {
        return FALSE;
    }

    StItemData tempItem;

    for (std::vector<StDropItem>::size_type i = 0;
         i < AwardItem.FixItems.size(); i++) {
        tempItem.dwItemID = AwardItem.FixItems[i].dwItemID;
        if (AwardItem.FixItems[i].dwItemNum[0] ==
            AwardItem.FixItems[i].dwItemNum[1]) {
            tempItem.dwItemNum = AwardItem.FixItems[i].dwItemNum[0];
        } else {
            tempItem.dwItemNum = AwardItem.FixItems[i].dwItemNum[0] +
                                 CommonFunc::GetRandNum(0) %
                                     (AwardItem.FixItems[i].dwItemNum[1] -
                                      AwardItem.FixItems[i].dwItemNum[0] + 1);
        }

        if (tempItem.dwItemNum > 0) {
            vtItemList.push_back(tempItem);
        }
    }

    for (int cycle = 0; cycle < AwardItem.dwRatioCount * nTimes; cycle++) {
        UINT32 dwRandValue = CommonFunc::GetRandNum(0);
        for (std::vector<StDropItem>::size_type i = 0;
             i < AwardItem.RatioItems.size() - 1; i++) {
            if ((dwRandValue >= AwardItem.RatioItems[i].dwRatio) &&
                (dwRandValue < AwardItem.RatioItems[i + 1].dwRatio)) {
                tempItem.dwItemID = AwardItem.RatioItems[i].dwItemID;
                if (AwardItem.RatioItems[i].dwItemNum[1] ==
                    AwardItem.RatioItems[i].dwItemNum[0]) {
                    tempItem.dwItemNum = AwardItem.RatioItems[i].dwItemNum[0];
                } else {
                    tempItem.dwItemNum =
                        AwardItem.RatioItems[i].dwItemNum[0] +
                        CommonFunc::GetRandNum(0) %
                            (AwardItem.RatioItems[i].dwItemNum[1] -
                             AwardItem.RatioItems[i].dwItemNum[0] + 1);
                }

                if (tempItem.dwItemNum > 0) {
                    vtItemList.push_back(tempItem);
                }
            }
        }
    }
    return TRUE;
}

BOOL CStaticData::ReadItemData(symphony::MySQLRes::ptr QueryData) {
    m_mapItem.clear();

    while (QueryData->next()) {
        StItemInfo stValue;
        stValue.dwItemID = QueryData->getIntField("Id");
        stValue.eItemType =
            (symphony::proto::EItemType)QueryData->getIntField("ItemType");
        stValue.dwBagType = QueryData->getIntField("BagType");
        stValue.SellID = QueryData->getIntField("SellMoneyId");
        stValue.SellPrice = QueryData->getIntField("SellMoneyNum");
        stValue.Quality = QueryData->getIntField("Quality");
        stValue.StackMax = QueryData->getIntField("StackMax");
        stValue.CarrerID = QueryData->getIntField("Carrer");
        stValue.Data1 = QueryData->getIntField("Data1");
        stValue.Data2 = QueryData->getIntField("Data2");
        m_mapItem.insert(std::make_pair(stValue.dwItemID, stValue));
    }

    return TRUE;
}

BOOL CStaticData::ReadFuncInfo(symphony::MySQLRes::ptr QueryData) {
    while (QueryData->next()) {
        StFuncInfo stValue;
        m_mapFuncInfo.insert(std::make_pair(stValue.dwFuncID, stValue));
    }

    return TRUE;
}

StFuncInfo* CStaticData::GetFuncInfo(UINT32 dwFuncID) {
    if (dwFuncID == 0) {
        return NULL;
    }
    auto itor = m_mapFuncInfo.find(dwFuncID);
    if (itor != m_mapFuncInfo.end()) {
        return &itor->second;
    }

    return NULL;
}

BOOL CStaticData::IsFuncOpen(UINT32 dwFuncID, INT32 level, INT32 viplevel) {
    StFuncInfo* pFuncInfo = GetFuncInfo(dwFuncID);
    if (pFuncInfo == NULL) {
        return false;
    }
    if (pFuncInfo->Logic <= 0 || pFuncInfo->Logic >= 5) {
        return false;
    }
    if (pFuncInfo->Logic == 1) {
        if (level >= pFuncInfo->OpenLevel || viplevel >= pFuncInfo->VipLevel) {
            return TRUE;
        }
    } else if (pFuncInfo->Logic == 2) {
        if (level >= pFuncInfo->OpenLevel && viplevel >= pFuncInfo->VipLevel) {
            return TRUE;
        }
    } else if (pFuncInfo->Logic == 3) {
        if (viplevel >= pFuncInfo->VipLevel) {
            return TRUE;
        }
    } else if (pFuncInfo->Logic == 4) {
        if (level >= pFuncInfo->OpenLevel) {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL CStaticData::ReadFuncVipInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapFuncVipInfo.clear();

    while (QueryData->next()) {
        StFuncVipInfo stValue;
        m_mapFuncVipInfo.insert(std::make_pair(stValue.dwFuncID, stValue));
    }

    return TRUE;
}

StFuncVipInfo* CStaticData::GetFuncVipInfo(UINT32 dwFuncID) {
    if (dwFuncID == 0) {
        return NULL;
    }
    auto itor = m_mapFuncVipInfo.find(dwFuncID);
    if (itor != m_mapFuncVipInfo.end()) {
        return &itor->second;
    }

    return NULL;
}

BOOL CStaticData::ReadFuncCostInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapFuncCostInfo.clear();

    while (QueryData->next()) {
        UINT32 dwFuncID = 0;
        std::vector<INT32> vtValue;
        m_mapFuncCostInfo.insert(std::make_pair(dwFuncID, vtValue));
    }

    return TRUE;
}

INT32 CStaticData::GetFuncCostInfo(UINT32 dwFuncID, INT32 Times) {
    if (dwFuncID <= 0) {
        return 0;
    }

    auto itor = m_mapFuncCostInfo.find(dwFuncID);
    if (itor != m_mapFuncCostInfo.end()) {
        std::vector<INT32>& vtCost = itor->second;

        return vtCost[Times];
    }

    return 0;
}

BOOL CStaticData::ReadEquipInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapEquipInfo.clear();

    while (QueryData->next()) {
        StEquipInfo stValue;
        stValue.dwEquipID = QueryData->getIntField("Id");
        stValue.dwSuitID = QueryData->getIntField("Suit");
        stValue.dwPos = QueryData->getIntField("Pos");
        m_mapEquipInfo.insert(std::make_pair(stValue.dwEquipID, stValue));
    }

    return TRUE;
}

StEquipInfo* CStaticData::GetEquipInfo(UINT32 dwEquipID) {
    if (dwEquipID == 0) {
        return NULL;
    }
    auto itor = m_mapEquipInfo.find(dwEquipID);
    if (itor != m_mapEquipInfo.end()) {
        return &itor->second;
    }
    return NULL;
}

BOOL CStaticData::ReadGemInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapGemInfo.clear();

    while (QueryData->next()) {
        StGemInfo stValue;
        stValue.dwGemID = QueryData->getIntField("Id");
        stValue.dwPos = QueryData->getIntField("Pos");
        m_mapGemInfo.insert(std::make_pair(stValue.dwGemID, stValue));
    }

    return TRUE;
}

StGemInfo* CStaticData::GetGemInfo(UINT32 dwGemID) {
    if (dwGemID == 0) {
        return NULL;
    }
    auto itor = m_mapGemInfo.find(dwGemID);
    if (itor != m_mapGemInfo.end()) {
        return &itor->second;
    }
    return NULL;
}

BOOL CStaticData::ReadPetInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapPetInfo.clear();

    while (QueryData->next()) {
        StPetInfo stValue;
        stValue.dwPetID = QueryData->getIntField("Id");
        stValue.dwActorID = QueryData->getIntField("ActorId");
        m_mapPetInfo.insert(std::make_pair(stValue.dwPetID, stValue));
    }

    return TRUE;
}

StPetInfo* CStaticData::GetPetInfo(UINT32 dwPetID) {
    if (dwPetID == 0) {
        return NULL;
    }
    auto itor = m_mapPetInfo.find(dwPetID);
    if (itor != m_mapPetInfo.end()) {
        return &itor->second;
    }
    return NULL;
}

BOOL CStaticData::ReadPartnerInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapPartnerInfo.clear();

    while (QueryData->next()) {
        StPartnerInfo stValue;
        stValue.dwPartnerID = QueryData->getIntField("Id");
        stValue.dwActorID = QueryData->getIntField("ActorId");
        m_mapPartnerInfo.insert(std::make_pair(stValue.dwPartnerID, stValue));
    }

    return TRUE;
}

StPartnerInfo* CStaticData::GetPartnerInfo(UINT32 dwPartnerID) {
    if (dwPartnerID == 0) {
        return NULL;
    }
    auto itor = m_mapPartnerInfo.find(dwPartnerID);
    if (itor != m_mapPartnerInfo.end()) {
        return &itor->second;
    }
    return NULL;
}

BOOL CStaticData::ReadMountInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapMountInfo.clear();

    while (QueryData->next()) {
        StMountInfo stValue;
        stValue.dwMountID = QueryData->getIntField("Id");
        stValue.dwMountID = QueryData->getIntField("ActorId");
        m_mapMountInfo.insert(std::make_pair(stValue.dwMountID, stValue));
    }

    return TRUE;
}

StMountInfo* CStaticData::GetMountInfo(UINT32 dwMountID) {
    if (dwMountID == 0) {
        return NULL;
    }
    auto itor = m_mapMountInfo.find(dwMountID);
    if (itor != m_mapMountInfo.end()) {
        return &itor->second;
    }
    return NULL;
}

BOOL CStaticData::ReadTaskInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapTaskInfo.clear();

    while (QueryData->next()) {
        StTaskInfo stValue;
        m_mapTaskInfo.insert(std::make_pair(stValue.TaskID, stValue));
    }

    return TRUE;
}

StTaskInfo* CStaticData::GetTaskInfo(UINT32 dwTaskID) {
    if (dwTaskID == 0) {
        return NULL;
    }
    auto itor = m_mapTaskInfo.find(dwTaskID);
    if (itor != m_mapTaskInfo.end()) {
        return &itor->second;
    }
    return NULL;
}

BOOL CStaticData::ReadSkillInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapSkillInfo.clear();

    while (QueryData->next()) {
        StSkillInfo stValue;
        stValue.SkillID = QueryData->getIntField("Id");
        stValue.Level = QueryData->getIntField("Level");
        stValue.CD = QueryData->getIntField("CountDown");
        stValue.HurtFix = QueryData->getIntField("HurtFix");
        stValue.HurtMuti = QueryData->getIntField("HurtMuti");
        stValue.SkillType = QueryData->getIntField("SkillType");
        stValue.HitShipType =
            (symphony::proto::EHitShipType)QueryData->getIntField(
                "HitShipType");
        stValue.HitMyself = QueryData->getIntField("HitMyself");
        UINT32 dwNewID = stValue.Level << 20 | stValue.SkillID;
        m_mapSkillInfo.insert(std::make_pair(dwNewID, stValue));
    }

    return TRUE;
}

StSkillInfo* CStaticData::GetSkillInfo(UINT32 dwSkillID, UINT32 dwLevel) {
    if (dwSkillID == 0 || dwLevel == 0) {
        return NULL;
    }

    UINT32 dwNewID = dwLevel << 20 | dwSkillID;
    auto itor = m_mapSkillInfo.find(dwNewID);
    if (itor != m_mapSkillInfo.end()) {
        return &itor->second;
    }
    return NULL;
}

BOOL CStaticData::ReadSkillEvent() {
    std::string strPath = "Skill/Battle_Skill.xml";

    tinyxml2::XMLDocument* pXMLDoc = nullptr;
    FILE* pFile = fopen(strPath.c_str(), "rb");
    if (pFile == NULL) {
        return FALSE;
    }
    fseek(pFile, 0, SEEK_END);
    INT32 nSize = ftell(pFile);
    rewind(pFile);
    char* pBuff = (char*)malloc(nSize + 1);
    memset(pBuff, 0, nSize + 1);
    fread(pBuff, nSize, 1, pFile);
    fclose(pFile);
    pXMLDoc = new tinyxml2::XMLDocument();
    pXMLDoc->Parse(pBuff);

    tinyxml2::XMLElement* pXmlRoot = pXMLDoc->FirstChildElement("Root");
    if (pXmlRoot == NULL) {
        return FALSE;
    }

    for (tinyxml2::XMLElement* pSkillNode =
             pXmlRoot->FirstChildElement("Skill");
         pSkillNode != NULL;
         pSkillNode = pSkillNode->NextSiblingElement("Skill")) {
        StSkillEventInfo tSkillEventInfo;

        // 取技能ID
        const char* pAttr = pSkillNode->Attribute("ID");
        tSkillEventInfo.nSkillID = CommonConvert::StringToInt(pAttr);

        pAttr = pSkillNode->Attribute("Duration");
        tSkillEventInfo.uDuration =
            (UINT64)(CommonConvert::StringToFloat(pAttr) * 1000);

        pAttr = pSkillNode->Attribute("CastType");
        tSkillEventInfo.dwCastType = CommonConvert::StringToInt(pAttr);

        for (tinyxml2::XMLElement* pEventNode =
                 pSkillNode->FirstChildElement("ActScope");
             pEventNode != NULL;
             pEventNode = pEventNode->NextSiblingElement("ActScope")) {
            StSkillEvent tEvent;
            pAttr = pEventNode->Attribute("RangeType");
            if (pAttr == NULL) {
                continue;
            }

            tEvent.RangeType = (ERangeType)CommonConvert::StringToInt(pAttr);
            ;
            pAttr = pEventNode->Attribute("RangeParams");
            if (pAttr == NULL) {
                continue;
            }
            CommonConvert::StringToVector(pAttr, tEvent.RangeParams, 5, '~');
            ;

            pAttr = pEventNode->Attribute("StTime");
            if (pAttr == NULL) {
                continue;
            }

            tEvent.TrigerTime =
                (UINT64)(CommonConvert::StringToFloat(pAttr) * 1000);

            pAttr = pEventNode->Attribute("HitActionID");
            if (pAttr == NULL) {
                continue;
            }

            tEvent.HitActionID = (UINT32)CommonConvert::StringToInt(pAttr);

            pAttr = pEventNode->Attribute("HitEffectID");
            if (pAttr == NULL) {
                continue;
            }

            tEvent.HitEffect = (UINT32)CommonConvert::StringToInt(pAttr);

            pAttr = pEventNode->Attribute("HitDistance");
            if (pAttr == NULL) {
                continue;
            }

            tEvent.HitDistance = CommonConvert::StringToFloat(pAttr);
            // 解析子弹
            for (tinyxml2::XMLElement* pBulletNode =
                     pEventNode->FirstChildElement("ActFlyObject");
                 pBulletNode != NULL;
                 pBulletNode =
                     pBulletNode->NextSiblingElement("ActFlyObject")) {
                StBulletObject bulletObject;

                pAttr = pBulletNode->Attribute("ID");
                if (pAttr == NULL) {
                    continue;
                }
                bulletObject.BulletID = CommonConvert::StringToInt(pAttr);

                pAttr = pBulletNode->Attribute("Angle");
                if (pAttr == NULL) {
                    continue;
                }
                bulletObject.fAngle = CommonConvert::StringToFloat(pAttr);

                tEvent.vtBullets.push_back(bulletObject);
            }

            tSkillEventInfo.vtEvents.push_back(tEvent);
        }

        m_mapSkillEvent.insert(
            std::make_pair(tSkillEventInfo.nSkillID, tSkillEventInfo));
    }

    return TRUE;
}

StSkillEventInfo* CStaticData::GetSkillEventInfo(UINT32 dwSkillID) {
    if (dwSkillID == 0) {
        return NULL;
    }

    auto itor = m_mapSkillEvent.find(dwSkillID);
    if (itor != m_mapSkillEvent.end()) {
        return &itor->second;
    }

    return NULL;
}

BOOL CStaticData::ReadComboSkillInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapComboSkill.clear();

    while (QueryData->next()) {
        StComboSkillInfo stValue;
        stValue.SkillID = QueryData->getIntField("SkillId");

        INT32 nValue = QueryData->getIntField("Combo1");
        if (nValue != 0) {
            stValue.vtComboSkill.push_back(nValue);
        }

        nValue = QueryData->getIntField("Combo2");
        if (nValue != 0) {
            stValue.vtComboSkill.push_back(nValue);
        }

        nValue = QueryData->getIntField("Combo3");
        if (nValue != 0) {
            stValue.vtComboSkill.push_back(nValue);
        }

        nValue = QueryData->getIntField("Combo4");
        if (nValue != 0) {
            stValue.vtComboSkill.push_back(nValue);
        }

        m_mapComboSkill.insert(std::make_pair(stValue.SkillID, stValue));
    }

    return TRUE;
}

StComboSkillInfo* CStaticData::GetComboSkillInfo(UINT32 dwSkillID) {
    if (dwSkillID == 0) {
        return NULL;
    }

    auto itor = m_mapComboSkill.find(dwSkillID);
    if (itor != m_mapComboSkill.end()) {
        return &itor->second;
    }

    return NULL;
}

BOOL CStaticData::ReadBuffInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapBuffInfo.clear();

    while (QueryData->next()) {
        StBuffInfo stValue;
        stValue.BuffID = QueryData->getIntField("id");

        m_mapBuffInfo.insert(std::make_pair(stValue.BuffID, stValue));
    }

    return TRUE;
}

StBuffInfo* CStaticData::GetBuffInfo(UINT32 dwBuffID) {
    if (dwBuffID == 0) {
        return NULL;
    }

    auto itor = m_mapBuffInfo.find(dwBuffID);
    if (itor != m_mapBuffInfo.end()) {
        return &itor->second;
    }

    return NULL;
}

BOOL CStaticData::ReadBulletInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapBulletInfo.clear();

    while (QueryData->next()) {
        StBulletInfo stValue;
        stValue.BulletID = QueryData->getIntField("Id");
        stValue.BulletType = (EBulletType)QueryData->getIntField("Type");
        stValue.InitSpeed = QueryData->getFloatField("InitSpeed");
        stValue.AccSpeed = QueryData->getFloatField("AcceSpeed");
        stValue.LifeTime = QueryData->getIntField("LifeTime");
        stValue.RangeType = (ERangeType)QueryData->getIntField("RangeType");
        CommonConvert::StringToVector(QueryData->getStringField("RangeParams"),
                                      stValue.RangeParams, 5, '~');
        m_mapBulletInfo.insert(std::make_pair(stValue.BulletID, stValue));
    }

    return TRUE;
}

StBulletInfo* CStaticData::GetBulletInfo(UINT32 dwBulletID) {
    if (dwBulletID == 0) {
        return NULL;
    }

    auto itor = m_mapBulletInfo.find(dwBulletID);
    if (itor != m_mapBulletInfo.end()) {
        return &itor->second;
    }

    return NULL;
}

BOOL CStaticData::ReadChargeInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapChargeInfo.clear();

    while (QueryData->next()) {
        StChargeInfo stValue;
        stValue.dwProductID = QueryData->getIntField("Id");
        m_mapChargeInfo.insert(std::make_pair(stValue.dwProductID, stValue));
    }

    return TRUE;
}

StChargeInfo* CStaticData::GetChargeInfo(UINT32 dwProductID) {
    if (dwProductID == 0) {
        return NULL;
    }

    auto itor = m_mapChargeInfo.find(dwProductID);
    if (itor != m_mapChargeInfo.end()) {
        return &itor->second;
    }

    return NULL;
}

BOOL CStaticData::ReadStoreInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapStoreInfo.clear();

    while (QueryData->next()) {
        StStoreItemInfo stValue;
        stValue.StoreID = QueryData->getIntField("Id");
        stValue.ItemID = QueryData->getIntField("ItemID");
        stValue.ItemNum = QueryData->getIntField("ItemNum");
        stValue.CostMoneyID = QueryData->getIntField("CostMoneyID");
        stValue.CostMoneyNum = QueryData->getIntField("CostMoneyNum");
        stValue.StoreType = QueryData->getIntField("StoreType");
        m_mapStoreInfo.insert(std::make_pair(stValue.StoreID, stValue));
    }

    return TRUE;
}

StStoreItemInfo* CStaticData::GetStoreItemInfo(UINT32 dwStoreID) {
    if (dwStoreID == 0) {
        return NULL;
    }

    auto itor = m_mapStoreInfo.find(dwStoreID);
    if (itor != m_mapStoreInfo.end()) {
        return &itor->second;
    }

    return NULL;
}

BOOL CStaticData::ReadActivityInfo(symphony::MySQLRes::ptr QueryData) {
    m_mapActivityInfo.clear();

    while (QueryData->next()) {
        StActivityInfo stValue;
        stValue.ActivityID = QueryData->getIntField("id");

        m_mapActivityInfo.insert(std::make_pair(stValue.ActivityID, stValue));
    }

    return TRUE;
}

StActivityInfo* CStaticData::GetActivityInfo(UINT32 dwActivityID) {
    if (dwActivityID == 0) {
        return NULL;
    }

    auto itor = m_mapActivityInfo.find(dwActivityID);
    if (itor != m_mapActivityInfo.end()) {
        return &itor->second;
    }

    return NULL;
}

StItemInfo* CStaticData::GetItemInfo(UINT32 dwItemID) {
    if (dwItemID == 0) {
        return NULL;
    }

    auto itor = m_mapItem.find(dwItemID);
    if (itor != m_mapItem.end()) {
        return &itor->second;
    }

    return NULL;
}