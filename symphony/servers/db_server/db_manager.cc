#include "db_manager.h"
#include "log.h"
namespace symphony {
namespace db {
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");
DBManager::DBManager() {
    std::map<std::string, std::string> params;
    params["host"] = "127.0.0.1";
    params["user"] = "root";
    params["passwd"] = "123456";
    params["dbname"] = "db_game";

    symphony::MySQL::ptr m(new symphony::MySQL(params));
    m->connect();
    m_game_db = m;
}
bool DBManager::getRoleList(uint64_t u64AccountID,
                            symphony::proto::RoleListAck& Ack) {
    std::string sql = "select * from player where account_id = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64AccountID);
    if (!stmt) {
        return false;
    }

    auto res = std::dynamic_pointer_cast<symphony::MySQLStmtRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getRoleList";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getRoleList errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }

    while (res->next()) {
        symphony::proto::RoleItem* pNode = Ack.add_rolelist();
        // pNode->set_roleid(res.getInt64Field("id", 0));
        // pNode->set_name(res.getStringField("name"));
        // pNode->set_carrer(res.getIntField("carrerid", 0));
        // pNode->set_level(res.getIntField("level", 0));
    }
}

bool DBManager::getRoleData(uint64_t u64ID,
                            symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getBagData(uint64_t u64ID,
                           symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getCopyData(uint64_t u64ID,
                            symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getEquipData(uint64_t u64ID,
                             symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getGemData(uint64_t u64ID,
                           symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getPetData(uint64_t u64ID,
                           symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getPartnerData(uint64_t u64ID,
                               symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getTaskData(uint64_t u64ID,
                            symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getMailData(uint64_t u64ID,
                            symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getActivtyData(uint64_t u64ID,
                               symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getMailData(uint64_t u64ID,
                            symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getCounterData(uint64_t u64ID,
                               symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getFriendData(uint64_t u64ID,
                              symphony::proto::DBRoleLoginAck& Ack) {}

bool DBManager::getSkillData(uint64_t u64ID,
                             symphony::proto::DBRoleLoginAck& Ack) {}
}  // namespace db
}  // namespace symphony
