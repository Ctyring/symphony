#ifndef __SEAL_DATA_OBJECT_H__
#define __SEAL_DATA_OBJECT_H__
#include "symphony/common/shared_memory.h"

enum ESealReason {
    ESR_GM_OPER = 1,     // 通过GM后台封禁
    ESR_CHANGE_MSG = 2,  // 协议MD5验证失败
};

enum ESealAction {
    ESA_SEAL_LOGIN = 1,  // 封禁登录
    ESA_SEAL_CHAT = 2,   // 封禁聊天
};

struct SealDataObject : public ShareObject {
    SealDataObject() {
        m_uRoleID = 0;
        m_uSealEndTime = 0;
        m_nSealAction = 0;
        m_uSealBeginlTime = 0;
        m_nSealReason = 0;
    }

    UINT64 m_uRoleID;
    INT32 m_nSealAction;
    UINT64 m_uSealEndTime;
    UINT64 m_uSealBeginlTime;
    INT32 m_nSealReason;

    BOOL Create(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "INSERT INTO seal_role (roleid, sealendtime,sealbegintime, sealaction, sealreason) \
            VALUES(?,?,?,?,?);";
        auto stmt = pDB->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uRoleID);
        stmt->bindUint64(1, m_uSealEndTime);
        stmt->bindUint64(2, m_uSealBeginlTime);
        stmt->bindInt32(3, m_nSealAction);
        stmt->bindInt32(4, m_nSealReason);
        return stmt->execute() == 0;
    }

    BOOL Update(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO seal_role (roleid, sealendtime,sealbegintime, sealaction, sealreason) \
            VALUES(?,?,?,?,?);";
        auto stmt = pDB->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uRoleID);
        stmt->bindUint64(1, m_uSealEndTime);
        stmt->bindUint64(2, m_uSealBeginlTime);
        stmt->bindInt32(3, m_nSealAction);
        stmt->bindInt32(4, m_nSealReason);
        return stmt->execute() == 0;
    }

    BOOL Delete(symphony::MySQL::ptr pdb) {
        std::string szSql = "delete from seal_role where roleid = ?";
        auto stmt = pDB->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uRoleID);
        return stmt->execute() == 0;
    }
};

#endif  //__SEAL_DATA_OBJECT_H__