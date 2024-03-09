#include "db_manager.h"
#include "symphony/log.h"
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

    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
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
        pNode->set_roleid(res->getInt64Field("id", 0));
        pNode->set_name(res->getStringField("name"));
        pNode->set_carrer(res->getIntField("carrerid", 0));
        pNode->set_level(res->getIntField("level", 0));
    }

    return true;
}

bool DBManager::getRoleData(uint64_t u64ID,
                            symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from player where id = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getRoleData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getRoleData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }

    symphony::proto::DBRoleData* pData = Ack.mutable_roledata();
    pData->set_roleid(res->getInt64Field("id", 0));
    pData->set_name(res->getStringField("name"));
    pData->set_carrerid(res->getIntField("carrerid", 0));
    pData->set_level(res->getIntField("level", 0));
    pData->set_exp(res->getInt64Field("exp", 0));
    pData->set_accountid(res->getInt64Field("accountid", 0));
    pData->set_citycopyid(res->getIntField("citycopyid", 0));
    pData->add_action(res->getInt64Field("action1", 0));
    pData->add_action(res->getInt64Field("action2", 0));
    pData->add_action(res->getInt64Field("action3", 0));
    pData->add_action(res->getInt64Field("action4", 0));
    pData->add_actime(res->getInt64Field("actime1", 0));
    pData->add_actime(res->getInt64Field("actime2", 0));
    pData->add_actime(res->getInt64Field("actime3", 0));
    pData->add_actime(res->getInt64Field("actime4", 0));
    pData->set_createtime(res->getInt64Field("createtime", 0));
    pData->set_logontime(res->getInt64Field("logontime", 0));
    pData->set_logofftime(res->getInt64Field("logofftime", 0));
    pData->set_guildid(res->getInt64Field("guildid", 0));
    pData->set_channel(res->getIntField("channel", 0));
    pData->set_onlinetime(res->getIntField("onlinetime", 0));

    return true;
}

bool DBManager::getBagData(uint64_t u64ID,
                           symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select* from bag where roleid = % lld";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getBagData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getBagData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }

    symphony::proto::DBBagData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_bagdata();
        }
        symphony::proto::DBBagItem* pItem = pData->add_itemlist();
        pItem->set_guid(res->getInt64Field("guid", 0));
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_itemguid(res->getInt64Field("itemguid", 0));
        pItem->set_itemid(res->getIntField("itemid", 0));
        pItem->set_count(res->getInt64Field("count", 0));
    }

    return true;
}

bool DBManager::getCopyData(uint64_t u64ID,
                            symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from copy where roleid = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getCopyData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getCopyData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    symphony::proto::DBCopyData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_copydata();
        }
        symphony::proto::DBCopyItem* pItem = pData->add_copylist();
        pItem->set_copyid(res->getIntField("copyid", 0));
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_starnum(res->getIntField("star", 0));
        pItem->set_battlecnt(res->getIntField("battlecnt", 0));
        pItem->set_resetcnt(res->getIntField("resetcnt", 0));
        pItem->set_battletime(res->getInt64Field("battletime", 0));
        pItem->set_resettime(res->getInt64Field("resettime", 0));
    }

    sql = "select * from chapter where roleid = ?";
    stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getCopyData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getCopyData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_copydata();
        }
        symphony::proto::DBChapterItem* pItem = pData->add_chapterlist();
        pItem->set_copytype(res->getIntField("copytype", 0));
        pItem->set_chapterid(res->getIntField("chapterid", 0));
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_staraward(res->getIntField("staraward", 0));
        pItem->set_sceneaward(res->getIntField("sceneaward", 0));
    }

    return true;
}

bool DBManager::getEquipData(uint64_t u64ID,
                             symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from equip where roleid = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getEquipData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getEquipData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    symphony::proto::DBEquipData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_equipdata();
        }
        symphony::proto::DBEquipItem* pItem = pData->add_equiplist();
        pItem->set_guid(res->getInt64Field("guid", 0));
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_equipid(res->getIntField("equipid", 0));
        pItem->set_isusing(res->getIntField("isuse", 0));
        pItem->set_refinelevel(res->getIntField("refinelvl", 0));
        pItem->set_starlevel(res->getIntField("starlvl", 0));
        pItem->set_strengthlvl(res->getIntField("strengthlvl", 0));
    }
    return true;
}

bool DBManager::getGemData(uint64_t u64ID,
                           symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from gem where roleid = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getGemData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getGemData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    symphony::proto::DBGemData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_gemdata();
        }
        symphony::proto::DBGemItem* pItem = pData->add_gemlist();
        pItem->set_guid(res->getInt64Field("guid", 0));
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_gemid(res->getIntField("gemid", 0));
        pItem->set_pos(res->getIntField("pos", 0));
        pItem->set_refinelevel(res->getIntField("refinelvl", 0));
        pItem->set_starlevel(res->getIntField("starlvl", 0));
        pItem->set_strengthlvl(res->getIntField("strengthlvl", 0));
    }

    return true;
}

bool DBManager::getPetData(uint64_t u64ID,
                           symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from pet where roleid = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getPetData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getPetData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    symphony::proto::DBPetData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_petdata();
        }
        symphony::proto::DBPetItem* pItem = pData->add_petlist();
        pItem->set_guid(res->getInt64Field("guid", 0));
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_petid(res->getIntField("petid", 0));
        pItem->set_refinelevel(res->getIntField("refinelvl", 0));
        pItem->set_strengthlvl(res->getIntField("strengthlvl", 0));
        pItem->set_starlevel(res->getIntField("starlvl", 0));
        pItem->set_isusing(res->getIntField("isuse", 0));
    }

    return true;
}

bool DBManager::getPartnerData(uint64_t u64ID,
                               symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from partner where roleid = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getPartnerData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getPartnerData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    symphony::proto::DBPartnerData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_partnerdata();
        }
        symphony::proto::DBPartnerItem* pItem = pData->add_partnerlist();
        pItem->set_guid(res->getInt64Field("guid", 0));
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_partnerid(res->getIntField("partnerid", 0));
        pItem->set_refinelevel(res->getIntField("refinelvl", 0));
        pItem->set_strengthlvl(res->getIntField("strengthlvl", 0));
        pItem->set_starlevel(res->getIntField("starlvl", 0));
        pItem->set_setpos(res->getIntField("setpos", 0));
    }

    return true;
}

bool DBManager::getTaskData(uint64_t u64ID,
                            symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from task where roleid = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getTaskData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getTaskData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    symphony::proto::DBTaskData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_taskdata();
        }
        symphony::proto::DBTaskItem* pItem = pData->add_tasklist();
        pItem->set_taskid(res->getIntField("id", 0));
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_status(res->getIntField("task_status", 0));
        pItem->set_progress(res->getIntField("progress", 0));
    }

    return true;
}
bool DBManager::getMountData(uint64_t u64ID,
                             symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from mount where roleid = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from GetMountData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from GetMountData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    symphony::proto::DBMountData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_mountdata();
        }
        symphony::proto::DBMountItem* pItem = pData->add_mountlist();
        pItem->set_guid(res->getInt64Field("guid", 0));
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_mountid(res->getIntField("mountid", 0));
        pItem->set_refinelevel(res->getIntField("refinelvl", 0));
        pItem->set_strengthlvl(res->getIntField("strengthlvl", 0));
        pItem->set_starlevel(res->getIntField("starlvl", 0));
        pItem->set_isusing(res->getIntField("isuse", 0));
    }

    return true;
}

bool DBManager::getActivtyData(uint64_t u64ID,
                               symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from activity where roleid = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getActivtyData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getActivtyData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    symphony::proto::DBActivityData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_activitydata();
        }
        symphony::proto::DBActivityItem* pItem = pData->add_activitylist();
        int32_t nLen = res->getIntField("data_len", 0);
        pItem->set_activityid(res->getIntField("id", 0));
        pItem->set_activitytype(res->getIntField("type", 0));
        pItem->set_roleid(res->getIntField("roleid", 0));
        pItem->set_jointime(res->getIntField("join_time", 0));
        pItem->set_datalen(nLen);

        if (nLen > 0) {
            int32_t nLen2 = 0;
            const unsigned char* pData = res->getBlobField("data", nLen2);
            pItem->set_data(pData, nLen);
        }
    }

    return true;
}

bool DBManager::getMailData(uint64_t u64ID,
                            symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from mail where roleid = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getMailData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getMailData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    symphony::proto::DBMailData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_maildata();
        }
        symphony::proto::DBMailItem* pItem = pData->add_maillist();
        pItem->set_guid(res->getInt64Field("id", 0));
        pItem->set_sender(res->getStringField("sendername", 0));
        pItem->set_senderid(res->getInt64Field("senderid", 0));
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_groupid(res->getInt64Field("groupid", 0));
        pItem->set_time(res->getInt64Field("mail_time", 0));
        pItem->set_title(res->getStringField("title", 0));
        pItem->set_content(res->getStringField("content", 0));
        pItem->set_mailtype(res->getIntField("mailtype", 0));
        pItem->set_status(res->getIntField("mailstatus", 0));

        int32_t nLen = 0;
        const unsigned char* pData = res->getBlobField("itemdata", nLen);
        pItem->set_items(pData, nLen);
    }

    return true;
}

bool DBManager::getCounterData(uint64_t u64ID,
                               symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from counter where roleid = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getCounterData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getCounterData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    symphony::proto::DBCounterData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_counterdata();
        }
        symphony::proto::DBCounterItem* pItem = pData->add_counterlist();
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_counterid(res->getIntField("id", 0));
        pItem->set_index(res->getIntField("cindex", 0));
        pItem->set_value(res->getInt64Field("value", 0));
        pItem->set_time(res->getInt64Field("time", 0));
    }

    return true;
}

bool DBManager::getFriendData(uint64_t u64ID,
                              symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from relationship where roleid = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getFriendData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getFriendData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    symphony::proto::DBFriendData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_frienddata();
        }
        symphony::proto::DBFriendItem* pItem = pData->add_friendlist();
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_friendid(res->getInt64Field("other_id", 0));
    }

    return true;
}

bool DBManager::getSkillData(uint64_t u64ID,
                             symphony::proto::DBRoleLoginAck& Ack) {
    std::string sql = "select * from skill where roleid = ?";
    symphony::MySQLStmt::ptr stmt = symphony::MySQLStmt::Create(m_game_db, sql);
    stmt->bindUint64(1, u64ID);
    if (!stmt) {
        return false;
    }
    auto res = std::dynamic_pointer_cast<symphony::MySQLRes>(stmt->query());
    if (!res) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid sql from getSkillData";
        return false;
    }
    if (res->getErrno()) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "from getSkillData errno=" << res->getErrno()
            << " errstr=" << res->getErrStr();
        return false;
    }
    symphony::proto::DBSkillData* pData = NULL;
    while (res->next()) {
        if (pData == NULL) {
            pData = Ack.mutable_skilldata();
        }
        symphony::proto::DBSkillItem* pItem = pData->add_skilllist();
        pItem->set_skillid(res->getIntField("id", 0));
        pItem->set_roleid(res->getInt64Field("roleid", 0));
        pItem->set_level(res->getIntField("level", 0));
        pItem->set_keypos(res->getIntField("key_pos", 0));
    }

    return true;
}
}  // namespace db
}  // namespace symphony
