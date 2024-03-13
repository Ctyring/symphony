#ifndef __BAG_DATA_OBJECT_H__
#define __BAG_DATA_OBJECT_H__
#include "symphony/common/shared_memory.h"
#include "symphony/db/mysql.h"
#include "symphony/symphony.h"
struct BagDataObject : public ShareObject {
    BagDataObject() {
        m_uGuid = 0;
        m_uRoleID = 0;
        m_ItemGuid = 0;
        m_ItemID = 0;
        m_nCount = 0;
        m_bBind = 0;
        m_nStatus = 0;
    }

    UINT64 m_uGuid;     // 格子的guid
    UINT64 m_uRoleID;   // 角色ID
    UINT64 m_ItemGuid;  // 物品guid
    UINT32 m_ItemID;    // 道具ID
    INT64 m_nCount;     // 个数
    BOOL m_bBind;       // 是否是邦定
    UINT32 m_nStatus;   // 是否删除

    BOOL Create(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "INSERT INTO bag (guid, roleid, itemguid, itemid, count, status) \
            VALUES(?,?,?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uGuid);
        stmt->bindUint64(1, m_uRoleID);
        stmt->bindUint64(2, m_ItemGuid);
        stmt->bindUint32(3, m_ItemID);
        stmt->bindInt64(4, m_nCount);
        stmt->bindUint32(5, m_nStatus);
        return stmt->execute();
    }

    BOOL Update(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO bag (guid, roleid, itemguid, itemid, count, status) \
            VALUES(?,?,?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uGuid);
        stmt->bindUint64(1, m_uRoleID);
        stmt->bindUint64(2, m_ItemGuid);
        stmt->bindUint32(3, m_ItemID);
        stmt->bindInt64(4, m_nCount);
        stmt->bindUint32(5, m_nStatus);
        return stmt->execute();
    }

    BOOL Delete(symphony::MySQL::ptr pdb) {
        std::string szSql = "delete from bag where guid = ?";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uGuid);
        return stmt->execute();
    }
};

#endif  //__BAG_DATA_OBJECT_H__