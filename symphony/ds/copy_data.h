#ifndef __COPY_DATA_OBJECT_H__
#define __COPY_DATA_OBJECT_H__
#include "symphony/common/shared_memory.h"

struct CopyDataObject : public ShareObject {
    CopyDataObject() {
        m_uRoleID = 0;
        m_dwBattleCnt = 0;
        m_dwResetCnt = 0;
        m_dwStarNum = 0;
        m_dwCopyID = 0;
        m_uBattleTime = 0;
        m_uResetTime = 0;
    }

    UINT64 m_uRoleID;
    UINT32 m_dwCopyID;
    UINT32 m_dwBattleCnt;
    UINT32 m_dwResetCnt;
    UINT32 m_dwStarNum;
    UINT64 m_uBattleTime;
    UINT64 m_uResetTime;

    BOOL Create(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO copy (copyid, roleid, star, battlecnt, resetcnt, battletime, resettime) \
            VALUES(?,?,?,?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint32(0, m_dwCopyID);
        stmt->bindUint64(1, m_uRoleID);
        stmt->bindUint32(2, m_dwStarNum);
        stmt->bindInt32(3, m_dwBattleCnt);
        stmt->bindInt32(4, m_dwResetCnt);
        stmt->bindUint64(5, m_uBattleTime);
        stmt->bindUint64(6, m_uResetTime);
        return stmt->execute() == 0;
    }

    BOOL Update(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO copy (copyid, roleid, star, battlecnt, resetcnt, battletime, resettime) \
            VALUES(?,?,?,?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint32(0, m_dwCopyID);
        stmt->bindUint64(1, m_uRoleID);
        stmt->bindUint32(2, m_dwStarNum);
        stmt->bindInt32(3, m_dwBattleCnt);
        stmt->bindInt32(4, m_dwResetCnt);
        stmt->bindUint64(5, m_uBattleTime);
        stmt->bindUint64(6, m_uResetTime);
        return stmt->execute() == 0;
    }

    BOOL Delete(symphony::MySQL::ptr pdb) {
        std::string szSql = "delete from copy where copyid = ? and roleid = ?";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint32(0, m_dwCopyID);
        stmt->bindUint64(1, m_uRoleID);
        return stmt->execute() == 0;
    }
};

struct ChapterDataObject : public ShareObject {
    ChapterDataObject() {
        m_uRoleID = 0;
        m_dwCopyType = 0;
        m_dwChapter = 0;
        m_dwStarAward = 0;
        m_dwSceneAward = 0;
    }

    UINT64 m_uRoleID;
    UINT32 m_dwCopyType;
    UINT32 m_dwChapter;
    UINT32 m_dwStarAward;
    UINT32 m_dwSceneAward;

    BOOL Create(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO chapter (chapterid, copytype, roleid, staraward, sceneaward) \
            VALUES(?,?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint32(0, m_dwChapter);
        stmt->bindUint32(1, m_dwCopyType);
        stmt->bindUint64(2, m_uRoleID);
        stmt->bindUint32(3, m_dwStarAward);
        stmt->bindUint32(4, m_dwSceneAward);
        return stmt->execute() == 0;
    }

    BOOL Update(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO chapter (chapterid, copytype, roleid, staraward, sceneaward) \
            VALUES(?,?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint32(0, m_dwChapter);
        stmt->bindUint32(1, m_dwCopyType);
        stmt->bindUint64(2, m_uRoleID);
        stmt->bindUint32(3, m_dwStarAward);
        stmt->bindUint32(4, m_dwSceneAward);
        return stmt->execute() == 0;
    }

    BOOL Delete(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "delete from chapter where chapterid = ? and roleid = ?";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint32(0, m_dwChapter);
        stmt->bindUint64(1, m_uRoleID);
        return stmt->execute() == 0;
    }
};

#endif  //__COPY_DATA_OBJECT_H__