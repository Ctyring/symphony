#ifndef __SERVER_DEFINE_H__
#define __SERVER_DEFINE_H__

// 货币数量
#define MONEY_NUM 15

// 行动力数量
#define ACTION_NUM 4

// 角色属性个数
#define PROPERTY_NUM 21

// 角色的最大等级
#define MAX_ROLE_LEVEL 150

// 服务器帧率
#define FPS_TIME_TICK 20

// 公会名长度
#define GUILD_NAME_LEN 255
#define GUILD_NOTICE_LEN 1024
#define GUILD_MAX_APPLY_NUM 50

// 订单
#define PAY_ORDERID_LEN 128

// 语言数
#define MAX_LANGUAGE_NUM 15

#define MAX_VIP_LEVEL 20

#define SQL_BUFF_LEN 1024

// 邮件
#define MAIL_CONTENT_LEN 2048
#define MAIL_TITLE_LEN 255
#define MAIL_ITEM_COUNT 10

#define ROLE_NAME_LEN 255

#define EQUIP_MAX_NUM 8

#define PARTNER_MAX_NUM 2

// 定义四种状态的基本移动速度
#define SPEED_IDLE (0.0f)
#define SPEED_WALK (2.5f)
#define SPEED_RUN (4.0f)
#define SPEED_FLY (6.5f)

enum EMouduleType {
    MT_ROLE,
    MT_COPY,
    MT_BAG,
    MT_EQUIP,
    MT_GEM,
    MT_PET,
    MT_PARTNER,
    MT_TASK,
    MT_MOUNT,
    MT_ACTIVITY,
    MT_COUNTER,
    MT_STORE,
    MT_SKILL,
    MT_MAIL,  // 邮件
    MT_FRIEND,
    MT_END
};

enum EShareData {
    ESD_BEGIN,
    ESD_ROLE,
    ESD_GLOBAL,
    ESD_BAG,
    ESD_COPY,
    ESD_EQUIP,
    ESD_GEM,
    ESD_PET,
    ESD_PARTNER,
    ESD_GUILD,
    ESD_GUILD_MEMBER,
    ESD_TASK,
    ESD_MOUNT,
    ESD_MAIL,
    ESD_OFFDATA,  // 离线操作
    ESD_GROUP_MAIL,
    ESD_ACTIVITY,
    ESD_COUNTER,
    ESD_FRIEND,
    ESD_CHAPTER,
    ESD_SKILL,
    ESD_SEAL_ROLE,
    ESD_PAYMENT,
    ESD_END
};

enum EAddWay {
    ADD_GMCOMMAND = 1,  // gm命令
    Add_ = 1,
    Cost_
};

enum EActivtyType {
    ACT_NONE = 0,
    ACT_LOGINAWARD = 1,
    ACT_SINCHRAGE = 2,
    ACT_SUMCHARGE = 3,
    ACT_OPEN_FUND = 4,
    ACT_DISCOUNT_SALE = 5,
};

enum ERoleProperty {
    ERP_ID = 1,
    ERP_LEVEL,
    ERP_VIPLEVEL,
    ERP_EXP,
    ERP_CHANNEL,
};

#ifndef __SERVER_STRUCT_H__
#define __SERVER_STRUCT_H__

struct BattleRecord {
    uint32_t m_dwResult;  // 0:未结算，1:胜利，2: 失败 3: 平局
    uint32_t m_dwKill;    // 击杀数
    uint32_t m_dwDeath;   // 被杀次数
    uint32_t m_dwHeal;    // 治疗值
    uint32_t m_dwDamage;  // 总伤害值
};

enum EChangeType {
    ECT_EQUIP = 1,    // 装备改变
    ECT_MOUNT = 2,    // 坐骑改变
    ECT_LEVEL = 3,    // 等级
    ECT_PARTNER = 4,  // 伙伴
    ECT_PET = 5,      // 宠物
};

enum EWinCondition {
    EWC_NONE,
    EWC_KILL_ALL,      // 击杀全部怪物
    EWC_KILL_NUM,      // 击杀指定数量怪物
    EWC_DESTINATION,   // 达到目的地
    EWC_PLAYER_ALIVE,  // 存活下来
    EWC_NPC_ALIVE,     // 护送npc
    EWC_END
};

enum EBattleCamp {
    EBC_NONE,     // 中立阵营
    EBC_PLAYER,   // 玩家阵营
    EBC_MONSTER,  // 怪物阵营
};

enum ETriggerType {
    ETT_NORMAL,  // 直接触发
    ETT_TRIBOX,  // 触发盒触发
    ETT_TIME,    // 时间触发
};

#endif  //__SERVER_STRUCT_H__

#endif  //__SERVER_STRUCT_H__