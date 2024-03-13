#ifndef __TYPE_DATA_PARSER_H__
#define __TYPE_DATA_PARSER_H__

#include "skill_struct.h"
#include "static_struct.h"
#include "symphony/db/mysql.h"
class CStaticData;

typedef BOOL (CStaticData::*DataFunc)(symphony::MySQLRes::ptr QueryData);

struct DataFuncNode {
    std::string m_strTbName;
    DataFunc m_pDataFunc;

    DataFuncNode(std::string sValue, DataFunc func) {
        m_strTbName = sValue;
        m_pDataFunc = func;
    }
};

class CStaticData {
    CStaticData();
    ~CStaticData();

   public:
    static CStaticData* GetInstancePtr();
    BOOL InitDataReader();
    BOOL LoadConfigData(std::string strDbFile);
    BOOL ReloadConfigData(std::string strTbName);

   public:
    // 基本配制变量
    ///////////////////////////////////////////////
    std::map<std::string, INT32> m_mapConstantValue;
    BOOL ReadConstantData(symphony::MySQLRes::ptr QueryData);
    INT32 GetConstantValue(std::string& strName);
    INT32 GetConstantValue(char* pszName);

    // 体力
    ///////////////////////////////////////////////
    std::vector<StActionInfo> m_vtActionList;
    BOOL ReadActionCfg(symphony::MySQLRes::ptr QueryData);
    INT64 GetActoinMaxValue(UINT32 dwActionID);
    UINT32 GetActoinUnitTime(UINT32 dwActionID);

    // 职业
    ///////////////////////////////////////////////
    std::map<UINT32, StCarrerInfo> m_mapCarrer;
    BOOL ReadCarrer(symphony::MySQLRes::ptr QueryData);
    StCarrerInfo* GetCarrerInfo(UINT32 dwCarrerID);

    // 职业等级信息
    ///////////////////////////////////////////////
    StLevelInfo m_CarrerLevel[4][MAX_ROLE_LEVEL];
    BOOL ReadCarrerLevel(symphony::MySQLRes::ptr QueryData);
    StLevelInfo* GetCarrerLevelInfo(UINT32 dwCarrerID, UINT32 dwLevel);

    // 角色
    ///////////////////////////////////////////////
    std::map<UINT32, StActorInfo> m_mapActor;
    BOOL ReadActor(symphony::MySQLRes::ptr QueryData);
    StActorInfo* GetActorInfo(UINT32 dwActorID);

    // 角色技能关系表
    std::map<UINT32, StActorSkillInfo> m_mapActorSkill;
    BOOL ReadActorSkillInfo(symphony::MySQLRes::ptr QueryData);
    StActorSkillInfo* GetActorSkillInfo(UINT32 dwActorID);

    // 副本
    ///////////////////////////////////////////////
    std::map<UINT32, StCopyInfo> m_mapCopyInfo;
    BOOL ReadCopyInfo(symphony::MySQLRes::ptr QueryData);
    StCopyInfo* GetCopyInfo(UINT32 dwCopyID);
    UINT32 GetCopyType(UINT32 dwCopyID);
    // 语言配制表
    ///////////////////////////////////////////////
    std::map<UINT32, StLocalString> m_mapLanguage;
    BOOL ReadLanguage(symphony::MySQLRes::ptr QueryData);
    std::string& GetLanguageText(UINT32 dwID, UINT32 dwLang);
    std::string& GetLanguageText(std::string strID, UINT32 dwLang);

    // 掉落表
    ///////////////////////////////////////////////
    std::map<UINT32, std::vector<StAwardItem>> m_mapAwardItem;
    BOOL ReadAwardData(symphony::MySQLRes::ptr QueryData);
    BOOL ParseToDropItem(std::string strDrop, StDropItem& Item);
    BOOL GetAwardItem(INT32 nAwardID, INT32 nCarrer, StAwardItem& AwardItem);
    BOOL GetAwardItemByIndex(INT32 nAwardID,
                             INT32 nCarrer,
                             INT32 nIndex,
                             StItemData& ItemData);
    BOOL GetItemsFromAwardID(INT32 nAwardID,
                             INT32 nCarrer,
                             std::vector<StItemData>& vtItemList);
    BOOL GetItemsAwardIDTimes(INT32 nAwardID,
                              INT32 nCarrer,
                              INT32 nTimes,
                              std::vector<StItemData>& vtItemList);

    // 物品表
    ///////////////////////////////////////////////
    std::map<UINT32, StItemInfo> m_mapItem;
    BOOL ReadItemData(symphony::MySQLRes::ptr QueryData);
    StItemInfo* GetItemInfo(UINT32 dwItemID);

    // 功能表
    std::map<UINT32, StFuncInfo> m_mapFuncInfo;
    BOOL ReadFuncInfo(symphony::MySQLRes::ptr QueryData);
    StFuncInfo* GetFuncInfo(UINT32 dwFuncID);
    BOOL IsFuncOpen(UINT32 dwFuncID, INT32 level, INT32 viplevel);

    // 功能表VIP
    std::map<UINT32, StFuncVipInfo> m_mapFuncVipInfo;
    BOOL ReadFuncVipInfo(symphony::MySQLRes::ptr QueryData);
    StFuncVipInfo* GetFuncVipInfo(UINT32 dwFuncID);

    // 功能表VIP花费
    std::map<UINT32, std::vector<INT32>> m_mapFuncCostInfo;
    BOOL ReadFuncCostInfo(symphony::MySQLRes::ptr QueryData);
    INT32 GetFuncCostInfo(UINT32 dwFuncID, INT32 Times);

    // 装备
    std::map<UINT32, StEquipInfo> m_mapEquipInfo;
    BOOL ReadEquipInfo(symphony::MySQLRes::ptr QueryData);
    StEquipInfo* GetEquipInfo(UINT32 dwEquipID);

    // 宝石
    std::map<UINT32, StGemInfo> m_mapGemInfo;
    BOOL ReadGemInfo(symphony::MySQLRes::ptr QueryData);
    StGemInfo* GetGemInfo(UINT32 dwGemID);

    // 宠物
    std::map<UINT32, StPetInfo> m_mapPetInfo;
    BOOL ReadPetInfo(symphony::MySQLRes::ptr QueryData);
    StPetInfo* GetPetInfo(UINT32 dwPetID);

    // 伙伴
    std::map<UINT32, StPartnerInfo> m_mapPartnerInfo;
    BOOL ReadPartnerInfo(symphony::MySQLRes::ptr QueryData);
    StPartnerInfo* GetPartnerInfo(UINT32 dwPartnerID);

    // 坐骑
    std::map<UINT32, StMountInfo> m_mapMountInfo;
    BOOL ReadMountInfo(symphony::MySQLRes::ptr QueryData);
    StMountInfo* GetMountInfo(UINT32 dwMountID);

    // 任务
    std::map<UINT32, StTaskInfo> m_mapTaskInfo;
    BOOL ReadTaskInfo(symphony::MySQLRes::ptr QueryData);
    StTaskInfo* GetTaskInfo(UINT32 dwTaskID);

    // 商店表
    std::map<UINT32, StStoreItemInfo> m_mapStoreInfo;
    BOOL ReadStoreInfo(symphony::MySQLRes::ptr QueryData);
    StStoreItemInfo* GetStoreItemInfo(UINT32 dwStoreID);

    // 活动表
    std::map<UINT32, StActivityInfo> m_mapActivityInfo;
    BOOL ReadActivityInfo(symphony::MySQLRes::ptr QueryData);
    StActivityInfo* GetActivityInfo(UINT32 dwActivityType);

    //=================================================================
    // 技能
    std::map<UINT32, StSkillInfo> m_mapSkillInfo;
    BOOL ReadSkillInfo(symphony::MySQLRes::ptr QueryData);
    StSkillInfo* GetSkillInfo(UINT32 dwSkillID, UINT32 dwLevel);

    // 技能事件
    std::map<UINT32, StSkillEventInfo> m_mapSkillEvent;
    BOOL ReadSkillEvent();
    StSkillEventInfo* GetSkillEventInfo(UINT32 dwSkillID);

    // 连击技能
    std::map<UINT32, StComboSkillInfo> m_mapComboSkill;
    BOOL ReadComboSkillInfo(symphony::MySQLRes::ptr QueryData);
    StComboSkillInfo* GetComboSkillInfo(UINT32 dwSkillID);

    // Buff
    std::map<UINT32, StBuffInfo> m_mapBuffInfo;
    BOOL ReadBuffInfo(symphony::MySQLRes::ptr QueryData);
    StBuffInfo* GetBuffInfo(UINT32 dwBuffID);

    // 子弹信息
    std::map<UINT32, StBulletInfo> m_mapBulletInfo;
    BOOL ReadBulletInfo(symphony::MySQLRes::ptr QueryData);
    StBulletInfo* GetBulletInfo(UINT32 dwBulletID);

    // 充值产品表
    std::map<UINT32, StChargeInfo> m_mapChargeInfo;
    BOOL ReadChargeInfo(symphony::MySQLRes::ptr QueryData);
    StChargeInfo* GetChargeInfo(UINT32 dwBulletID);
    //=================================================================
   public:
    std::vector<DataFuncNode> m_vtDataFuncList;
};

#endif  //__TYPE_DATA_PARSER_H__