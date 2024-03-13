#ifndef __TASK_DATA_OBJECT_H__
#define __TASK_DATA_OBJECT_H__
#include "symphony/common/shared_memory.h"
struct TaskDataObject : public ShareObject {
    TaskDataObject() {
        m_uRoleID = 0;  // 角色ID
        m_nTaskID = 0;  // 任务ID
        m_nTaskStatus = 0;
        m_nProgress = 0;  //
    }

    UINT64 m_uRoleID;     // 角色ID
    INT32 m_nTaskID;      // 任务ID
    INT32 m_nTaskStatus;  // 任务状态
    INT32 m_nProgress;    // 任务进度

    BOOL Create(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO task (id, roleid, task_status, progress) "
            "VALUES(?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindInt32(0, m_nTaskID);
        stmt->bindUint64(1, m_uRoleID);
        stmt->bindInt32(2, m_nTaskStatus);
        stmt->bindInt32(3, m_nProgress);
        return stmt->execute() == 0;
    }

    BOOL Update(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO task (id, roleid, task_status, progress) "
            "VALUES(?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindInt32(0, m_nTaskID);
        stmt->bindUint64(1, m_uRoleID);
        stmt->bindInt32(2, m_nTaskStatus);
        stmt->bindInt32(3, m_nProgress);
        return stmt->execute() == 0;
    }

    BOOL Delete(symphony::MySQL::ptr pdb) { return TRUE; }
};

#endif  //__TASK_DATA_OBJECT_H__