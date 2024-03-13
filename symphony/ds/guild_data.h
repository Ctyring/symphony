#ifndef __GUILD_DATA_OBJECT_H__
#define __GUILD_DATA_OBJECT_H__
#include "symphony/common/shared_memory.h"

struct GuildDataObject : public ShareObject {
    GuildDataObject() {
        m_uGuid = 0;
        m_Level = 0;
        m_uCreateTime = 0;
        memset(m_szName, 0, GUILD_NAME_LEN);
        memset(m_szNotice, 0, GUILD_NOTICE_LEN);
    }

    INT32 m_Level;                             // 等级
    UINT64 m_uGuid;                            // guid
    CHAR m_szName[GUILD_NAME_LEN];             // 名字
    CHAR m_szNotice[GUILD_NOTICE_LEN];         // 公告
    UINT64 m_ApplyRoles[GUILD_MAX_APPLY_NUM];  // 申请id
    UINT64 m_uCreateTime;

    BOOL Create(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO guild (id, name, level, notice, create_time) \
            VALUES(?,?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uGuid);
        stmt->bindString(1, m_szName);
        stmt->bindInt32(2, m_Level);
        stmt->bindString(3, m_szNotice);
        stmt->bindUint64(4, m_uCreateTime);
        return stmt->execute() == 0;
    }

    BOOL Update(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO guild (id, name, level, notice, create_time) \
            VALUES(?,?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uGuid);
        stmt->bindString(1, m_szName);
        stmt->bindInt32(2, m_Level);
        stmt->bindString(3, m_szNotice);
        stmt->bindUint64(4, m_uCreateTime);
        return stmt->execute() == 0;
    }

    BOOL Delete(symphony::MySQL::ptr pdb) {
        std::string szSql = "delete from guild where id = ?";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uGuid);
        return stmt->execute() == 0;
    }
};

struct MemberDataObject : public ShareObject {
    MemberDataObject() {}

    UINT64 m_uRoleID;
    UINT64 m_uGuildID;  // 公会的guid
    UINT32 m_Pos;
    UINT64 m_uJoinTime;

    BOOL Create(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO guild_member (guildid, roleid, join_time, pose) \
            VALUES(?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uGuildID);
        stmt->bindUint64(1, m_uRoleID);
        stmt->bindUint64(2, m_uJoinTime);
        stmt->bindInt32(3, m_Pos);
        return stmt->execute() == 0;
    }

    BOOL Update(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "REPLACE INTO guild_member (guildid, roleid, join_time, pose) \
            VALUES(?,?,?,?);";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uGuildID);
        stmt->bindUint64(1, m_uRoleID);
        stmt->bindUint64(2, m_uJoinTime);
        stmt->bindInt32(3, m_Pos);
        return stmt->execute() == 0;
    }

    BOOL Delete(symphony::MySQL::ptr pdb) {
        std::string szSql =
            "delete from guild_member where guildid = ? and roleid = ?";
        auto stmt = pdb->prepare(szSql);
        if (!stmt) {
            return FALSE;
        }
        stmt->bindUint64(0, m_uGuildID);
        stmt->bindUint64(1, m_uRoleID);
        return stmt->execute() == 0;
    }
};

#endif  //__GUILD_DATA_OBJECT_H__