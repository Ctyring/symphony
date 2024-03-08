#pragma once
#include "symphony/db/mysql.h"
#include "symphony/proto/msg_login_db.pb.h"
#include "symphony/proto/msg_role.pb.h"
#include "symphony/singleton.h"
namespace symphony {
namespace db {
class DBManager {
   public:
    DBManager();
    bool getRoleList(uint64_t u64AccountID, symphony::proto::RoleListAck& Ack);

    bool getRoleData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getBagData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getCopyData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getEquipData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getGemData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getPetData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getPartnerData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getTaskData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getMailData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getActivtyData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getMailData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getCounterData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getFriendData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

    bool getSkillData(uint64_t u64ID, symphony::proto::DBRoleLoginAck& Ack);

   private:
    symphony::MySQL::ptr m_game_db;
};

typedef symphony::Singleton<DBManager> DBMgr;
}  // namespace db
}  // namespace symphony