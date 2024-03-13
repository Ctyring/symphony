#ifndef __GLOBAL_DATA_OBJECT_H__
#define __GLOBAL_DATA_OBJECT_H__

#include "symphony/common/shared_memory.h"

#define MAX_EXTRA_INDEX 60

struct GlobalDataObject : public ShareObject {
    GlobalDataObject() {
        m_dwServerID = 0;   // 服务器ID
        m_u64Guid = 0;      // 全局GUID
        m_dwMaxOnline = 0;  // 最大在线人数
        memset(m_exData, 0, sizeof(INT32) * MAX_EXTRA_INDEX);
    }

    UINT32 m_dwServerID;              // 服务器ID
    UINT64 m_u64Guid;                 // 全局GUID
    UINT32 m_dwMaxOnline;             // 最大在线人数
    INT32 m_exData[MAX_EXTRA_INDEX];  // 扩展数据

    BOOL Create(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO globaldata (serverid, maxguid, maxonline, extradata) "
            "VALUES(?, ?, ?, ?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint32(0, m_dwServerID);
        stmt->bindUint64(1, m_u64Guid);
        stmt->bindUint32(2, m_dwMaxOnline);
        stmt->bindTinyBlob(3, m_exData, sizeof(INT32) * MAX_EXTRA_INDEX);
        return stmt->execute() == 0;
    }

    BOOL Update(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO globaldata (serverid, maxguid, maxonline, extradata) "
            "VALUES(?, ?, ?, ?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint32(0, m_dwServerID);
        stmt->bindUint64(1, m_u64Guid);
        stmt->bindUint32(2, m_dwMaxOnline);
        stmt->bindTinyBlob(3, m_exData, sizeof(INT32) * MAX_EXTRA_INDEX);
        return stmt->execute() == 0;
    }

    BOOL Delete(symphony::MySQL::ptr pdb) { return TRUE; }
};

#endif  //__GLOBAL_DATA_OBJECT_H__