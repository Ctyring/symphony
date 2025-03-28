#ifndef __ACTIVITY_DATA_OBJECT_H__
#define __ACTIVITY_DATA_OBJECT_H__
#include "symphony/common/shared_memory.h"
// 登录奖励
struct LoginAward {};

struct FirstCharge {};

struct OpenFund {};

struct LevelGift {
    UINT32 GiftID[20];
    UINT32 BuyTimes[20];
    UINT32 DeadLine[20];
};

struct VipGift {
    UINT32 GiftID[20];
    UINT32 BuyTimes[20];
    UINT32 DeadLine[20];
};

// 累充
struct SumRecharge {
    UINT32 m_SumMoney;  // 累计充值钱数
    BOOL m_AwardMark;   // 领奖标计
};

// 单充
struct SinRecharge {};

struct ActivityDataObject : public ShareObject {
    ActivityDataObject() {
        m_dwActivityID = 0;
        m_uRoleID = 0;
        m_dwActivityType = 0;
        m_uJoinTime = 0;
        m_dwDataLen = 0;
        memset(m_Data.m_Bytes, 0, sizeof(m_Data.m_Bytes));
    }

    UINT32 m_dwActivityID;    // 活动ID
    UINT64 m_uRoleID;         // 角色ID
    UINT32 m_dwActivityType;  // 活动类型
    UINT64 m_uJoinTime;       // 参与时间
    UINT32 m_dwDataLen;       // 数据时间长度
    union {
        BYTE m_Bytes[1024];  // 活动数据
        FirstCharge m_FirstCharge;
        OpenFund m_OpenFund;
        LevelGift m_LevelGift;
        VipGift m_VipGift;
        SumRecharge m_SumRecharge;
        SinRecharge m_SinRecharge;
    } m_Data;

    BOOL Create(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO activity (id, type, roleid, join_time, data_len, data) \
            VALUES(?,?,?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint32(0, m_dwActivityID);
        stmt->bindUint32(1, m_dwActivityType);
        stmt->bindUint64(2, m_uRoleID);
        stmt->bindUint64(3, m_uJoinTime);
        stmt->bindInt32(4, m_dwDataLen);
        stmt->bindTinyBlob(5, m_Data.m_Bytes, m_dwDataLen);
        return stmt->execute() == 0;
    }

    BOOL Update(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO activity (id, type, roleid, join_time, data_len, data) \
            VALUES(?,?,?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint32(0, m_dwActivityID);
        stmt->bindUint32(1, m_dwActivityType);
        stmt->bindUint64(2, m_uRoleID);
        stmt->bindUint64(3, m_uJoinTime);
        stmt->bindInt32(4, m_dwDataLen);
        stmt->bindTinyBlob(5, m_Data.m_Bytes, m_dwDataLen);
        return stmt->execute() == 0;
    }

    BOOL Delete(symphony::MySQL::ptr pdb) { return TRUE; }
};

#endif  //__ACTIVITY_DATA_OBJECT_H__