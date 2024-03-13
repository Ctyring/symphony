#ifndef __ROLE_DATA_OBJECT_H__
#define __ROLE_DATA_OBJECT_H__
#include "symphony/common/shared_memory.h"
#include "symphony/symphony.h"
// #include "DBInterface/DBInterface.h"
// #include "DBInterface/DBStoredProc.h"
struct RoleDataObject : public ShareObject {
    RoleDataObject() {
        m_uRoleID = 0;      // 角色ID
        m_uAccountID = 0;   // 账号ID
        m_Level = 0;        // 等级
        m_Exp = 0;          // 经验
        m_nLangID = 0;      // 语言ID
        m_u64Fight = 0;     // 战力
        m_nVipLvl = 0;      // VIP等级
        m_nVipExp = 0;      // VIP经验
        m_CityCopyID = 0;   // 主城副本类型
        m_bDelete = FALSE;  // 是否删除
        m_CarrerID = 0;     // 职业
        m_uCreateTime = 0;  // 角色创建时间
        m_uLogonTime = 0;   // 最近一次登录时间
        m_uLogoffTime = 0;  // 最近一次离线时间
        m_nChannel = 0;     // 角色渠道
        memset(m_szName, 0, ROLE_NAME_LEN);
    }

    UINT64 m_uRoleID;              // 角色ID
    UINT64 m_uAccountID;           // 账号ID
    CHAR m_szName[ROLE_NAME_LEN];  // 角色名
    INT32 m_CarrerID;              // 职业ID
    INT32 m_Level;                 // 等级
    INT64 m_Action[ACTION_NUM];    // 所有的体力
    INT64 m_Actime[ACTION_NUM];    // 体力恢复时间
    INT64 m_Exp;                   // 经验
    INT32 m_nLangID;               // 语言ID
    INT64 m_u64Fight;              // 战力
    INT32 m_nVipLvl;               // VIP等级
    INT32 m_nVipExp;               // VIP经验
    INT32 m_CityCopyID;            // 主城副本类型
    INT32 m_nChannel;              // 角色渠道
    BOOL m_bDelete;                // 是否删除
    INT64 m_uQQ;                   // QQ号
    UINT64 m_uCreateTime;          // 角色创建时间
    UINT64 m_uLogonTime;           // 本次登录时间
    UINT64 m_uLogoffTime;          // 离线时间
    UINT64 m_uGroupMailTime;       // 群邮件接收时间
    UINT64 m_uGuildID;             // 公会ID
    UINT32 m_nOnlineTime;          // 在线时长
    // 签到数据
    INT32 m_nSignNum;     // 签到天数
    UINT32 m_nSignDay;    // 最新的签到时间
    UINT32 m_RecvAction;  // 领取体力标记

    BOOL Create(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO player (id, accountid, name, carrerid,level, citycopyid,exp, langid, viplevel, vipexp, action1, action2, action3,action4, actime1, actime2, actime3,actime4, createtime, logontime, logofftime, grouptime, fightvalue, guildid) \
            VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uRoleID);
        stmt->bindUint64(1, m_uAccountID);
        stmt->bindString(2, m_szName);
        stmt->bindInt32(3, m_CarrerID);
        stmt->bindInt32(4, m_Level);
        stmt->bindInt64(5, m_CityCopyID);
        stmt->bindInt64(6, m_Exp);
        stmt->bindInt32(7, m_nLangID);
        stmt->bindInt32(8, m_nVipLvl);
        stmt->bindInt32(9, m_nVipExp);
        stmt->bindInt64(10, m_Action[0]);
        stmt->bindInt64(11, m_Action[1]);
        stmt->bindInt64(12, m_Action[2]);
        stmt->bindInt64(13, m_Action[3]);
        stmt->bindInt64(14, m_Actime[0]);
        stmt->bindInt64(15, m_Actime[1]);
        stmt->bindInt64(16, m_Actime[2]);
        stmt->bindInt64(17, m_Actime[3]);
        stmt->bindInt64(18, m_uCreateTime);
        stmt->bindInt64(19, m_uLogonTime);
        stmt->bindInt64(20, m_uLogoffTime);
        stmt->bindInt64(21, m_uGroupMailTime);
        stmt->bindInt64(22, m_u64Fight);
        stmt->bindInt64(23, m_uGuildID);
        return stmt->execute() == 0;
    }

    BOOL Update(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO player (id, accountid, name, carrerid,level, citycopyid,exp, langid, viplevel, vipexp, action1, action2, action3,action4, actime1, actime2, actime3,actime4, createtime, logontime, logofftime, grouptime, fightvalue, guildid) \
            VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uRoleID);
        stmt->bindUint64(1, m_uAccountID);
        stmt->bindString(2, m_szName);
        stmt->bindInt32(3, m_CarrerID);
        stmt->bindInt32(4, m_Level);
        stmt->bindInt64(5, m_CityCopyID);
        stmt->bindInt64(6, m_Exp);
        stmt->bindInt32(7, m_nLangID);
        stmt->bindInt32(8, m_nVipLvl);
        stmt->bindInt32(9, m_nVipExp);
        stmt->bindInt64(10, m_Action[0]);
        stmt->bindInt64(11, m_Action[1]);
        stmt->bindInt64(12, m_Action[2]);
        stmt->bindInt64(13, m_Action[3]);
        stmt->bindInt64(14, m_Actime[0]);
        stmt->bindInt64(15, m_Actime[1]);
        stmt->bindInt64(16, m_Actime[2]);
        stmt->bindInt64(17, m_Actime[3]);
        stmt->bindInt64(18, m_uCreateTime);
        stmt->bindInt64(19, m_uLogonTime);
        stmt->bindInt64(20, m_uLogoffTime);
        stmt->bindInt64(21, m_uGroupMailTime);
        stmt->bindInt64(22, m_u64Fight);
        stmt->bindInt64(23, m_uGuildID);
        return stmt->execute() == 0;
    }

    BOOL Delete(symphony::MySQL::ptr pdb) {
        std::string szSql = "delete from player where id = ?";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uRoleID);
        return stmt->execute() == 0;
    }
};

#endif  //__SERVER_STRUCT_H__