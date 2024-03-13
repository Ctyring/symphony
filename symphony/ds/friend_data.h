#ifndef __FRIEND_DATA_OBJECT_H__
#define __FRIEND_DATA_OBJECT_H__
#include "symphony/common/shared_memory.h"
#include "symphony/db/mysql.h"
struct FriendDataObject : public ShareObject {
    FriendDataObject() {}

    UINT64 m_uRoleID;    // 角色ID
    UINT64 m_uFriendID;  // 好友ID

    BOOL Create(symphony::MySQL::ptr pdb) { return TRUE; }

    BOOL Update(symphony::MySQL::ptr pdb) { return TRUE; }

    BOOL Delete(symphony::MySQL::ptr pdb) { return TRUE; }
};

#endif  //__FRIEND_DATA_OBJECT_H__