#include "log_server_module.h"
#include "log_server_protocol.h"
#include "orm_out/symphony/log/account_create_info.h"
#include "orm_out/symphony/log/account_login_info.h"
#include "orm_out/symphony/log/role_chat_info.h"
#include "orm_out/symphony/log/role_create_info.h"
#include "orm_out/symphony/log/role_login_info.h"
#include "orm_out/symphony/log/role_logout_info.h"

#include "symphony/log.h"
namespace symphony {
namespace ls {
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");
LogServerModule::LogServerModule()
    : RockModule("LogServerModule", "1.0.0", "") {
    std::map<std::string, std::string> params;
    params["host"] = "127.0.0.1";
    params["user"] = "root";
    params["passwd"] = "123456";
    params["dbname"] = "db_log";

    symphony::MySQL::ptr m(new symphony::MySQL(params));
    m->connect();
    m_log_db = m;
}
bool LogServerModule::handleRockRequest(symphony::RockRequest::ptr request,
                                        symphony::RockResponse::ptr response,
                                        symphony::RockStream::ptr stream) {
    switch (request->getCmd()) {
        case (int)LSCommand::TICK: {
            handleTick(request, response, stream);
            break;
        }
        case (int)LSCommand::ACCOUNT_CREATE: {
            handleAccountCreate(request, response, stream);
            break;
        }
        case (int)LSCommand::ACCOUNT_LOGIN: {
            handleAccountLogin(request, response, stream);
            break;
        }
        case (int)LSCommand::ROLE_CREATE: {
            handleRoleCreate(request, response, stream);
            break;
        }
        case (int)LSCommand::ROLE_LOGIN: {
            handleRoleLogin(request, response, stream);
            break;
        }
        case (int)LSCommand::ROLE_LOGOUT: {
            handleRoleLogout(request, response, stream);
            break;
        }
        case (int)LSCommand::ROLE_CHAT: {
            handleRoleChat(request, response, stream);
            break;
        }
        default:
            SYMPHONY_LOG_WARN(g_logger)
                << "invalid cmd=0x" << std::hex << request->getCmd();
            return true;
    }

    m_write_cnt++;
    if (m_write_cnt > 1000) {
        if (!m_log_db->ping()) {
            SYMPHONY_LOG_ERROR(g_logger) << "ls db ping fail";
        }
        if (!m_log_db->openTransaction(true)) {
            SYMPHONY_LOG_ERROR(g_logger) << "ls db open transaction fail";
        }
        m_write_cnt = 0;
    }
    return true;
}

bool LogServerModule::handleRockNotify(symphony::RockNotify::ptr notify,
                                       symphony::RockStream::ptr stream) {
    return true;
}

bool LogServerModule::onConnect(symphony::Stream::ptr stream) {
    return true;
}

bool LogServerModule::onDisconnect(symphony::Stream::ptr stream) {
    return true;
}

bool LogServerModule::handleAccountCreate(symphony::RockRequest::ptr request,
                                          symphony::RockResponse::ptr response,
                                          symphony::RockStream::ptr stream) {
    symphony::log::AccountCreateInfo::ptr aci(
        new symphony::log::AccountCreateInfo);
    auto account_info = request->getAsPB<symphony::ls::AccountCreateInfo>();
    if (!account_info) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid account_info";
        return false;
    }
    aci->setAccountid(account_info->accountid());
    aci->setVersion(account_info->version());
    aci->setChannel(account_info->channel());
    aci->setOptime(account_info->optime());
    aci->setImodel(account_info->imodel());
    aci->setImei(account_info->imei());
    aci->setIp(account_info->ip());
    aci->setOpenid(account_info->openid());
    aci->setIdfa(account_info->idfa());
    aci->setUuid(account_info->uuid());
    symphony::log::AccountCreateInfoDao::Insert(aci, m_log_db);
    return true;
}

bool LogServerModule::handleAccountLogin(symphony::RockRequest::ptr request,
                                         symphony::RockResponse::ptr response,
                                         symphony::RockStream::ptr stream) {
    symphony::log::AccountLoginInfo::ptr aci(
        new symphony::log::AccountLoginInfo);
    auto account_info = request->getAsPB<symphony::ls::AccountLoginInfo>();
    if (!account_info) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid account_info";
        return false;
    }
    aci->setAccountid(account_info->accountid());
    aci->setVersion(account_info->version());
    aci->setChannel(account_info->channel());
    aci->setOptime(account_info->optime());
    aci->setImodel(account_info->imodel());
    aci->setImei(account_info->imei());
    aci->setIp(account_info->ip());
    aci->setOpenid(account_info->openid());
    aci->setIdfa(account_info->idfa());
    aci->setUuid(account_info->uuid());
    symphony::log::AccountLoginInfoDao::Insert(aci, m_log_db);
    return true;
}

bool LogServerModule::handleRoleCreate(symphony::RockRequest::ptr request,
                                       symphony::RockResponse::ptr response,
                                       symphony::RockStream::ptr stream) {
    symphony::log::RoleCreateInfo::ptr rci(new symphony::log::RoleCreateInfo);
    auto role_info = request->getAsPB<symphony::ls::RoleCreateInfo>();
    if (!role_info) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid account_info";
        return false;
    }
    rci->setRoleid(role_info->roleid());
    rci->setAccountid(role_info->accountid());
    rci->setAreaid(role_info->areaid());
    rci->setChannel(role_info->channel());
    rci->setOptime(role_info->optime());
    rci->setRolename(role_info->rolename());
    rci->setImodel(role_info->imodel());
    rci->setImei(role_info->imei());
    rci->setIdfa(role_info->idfa());
    rci->setUuid(role_info->uuid());
    symphony::log::RoleCreateInfoDao::Insert(rci, m_log_db);
    return true;
}

bool LogServerModule::handleRoleLogin(symphony::RockRequest::ptr request,
                                      symphony::RockResponse::ptr response,
                                      symphony::RockStream::ptr stream) {
    symphony::log::RoleLoginInfo::ptr rli(new symphony::log::RoleLoginInfo);
    auto role_info = request->getAsPB<symphony::ls::RoleLoginInfo>();
    if (!role_info) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid account_info";
        return false;
    }
    rli->setRoleid(role_info->roleid());
    rli->setAccountid(role_info->accountid());
    rli->setChannel(role_info->channel());
    rli->setLevel(role_info->level());
    rli->setViplevel(role_info->viplevel());
    rli->setOptime(role_info->optime());
    rli->setAreaid(role_info->areaid());
    rli->setRolename(role_info->rolename());
    rli->setUuid(role_info->uuid());
    rli->setIdfa(role_info->idfa());
    rli->setImei(role_info->imei());
    rli->setImodel(role_info->imodel());
    symphony::log::RoleLoginInfoDao::Insert(rli, m_log_db);
    return true;
}

bool LogServerModule::handleRoleLogout(symphony::RockRequest::ptr request,
                                       symphony::RockResponse::ptr response,
                                       symphony::RockStream::ptr stream) {
    symphony::log::RoleLogoutInfo::ptr rli(new symphony::log::RoleLogoutInfo);
    auto role_info = request->getAsPB<symphony::ls::RoleLogoutInfo>();
    if (!role_info) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid account_info";
        return false;
    }
    rli->setRoleid(role_info->roleid());
    rli->setAccountid(role_info->accountid());
    rli->setChannel(role_info->channel());
    rli->setLevel(role_info->level());
    rli->setViplevel(role_info->viplevel());
    rli->setOptime(role_info->optime());
    rli->setAreaid(role_info->areaid());
    rli->setRolename(role_info->rolename());
    rli->setIdfa(role_info->idfa());
    rli->setImei(role_info->imei());
    rli->setImodel(role_info->imodel());
    symphony::log::RoleLogoutInfoDao::Insert(rli, m_log_db);
    return true;
}

bool LogServerModule::handleRoleChat(symphony::RockRequest::ptr request,
                                     symphony::RockResponse::ptr response,
                                     symphony::RockStream::ptr stream) {
    symphony::log::RoleChatInfo::ptr rci(new symphony::log::RoleChatInfo);
    auto role_info = request->getAsPB<symphony::ls::RoleChatInfo>();
    if (!role_info) {
        SYMPHONY_LOG_ERROR(g_logger) << "invalid account_info";
        return false;
    }
    rci->setRoleid(role_info->roleid());
    rci->setLevel(role_info->level());
    rci->setRolename(role_info->rolename());
    rci->setViplevel(role_info->viplevel());
    rci->setAreaid(role_info->areaid());
    rci->setChannel(role_info->channel());
    rci->setText(role_info->text());
    rci->setOptime(role_info->optime());
    rci->setTargetid(role_info->targetid());
    rci->setTargetvip(role_info->targetvip());
    rci->setTargetname(role_info->targetname());
    rci->setChatchl(role_info->chatchl());
    symphony::log::RoleChatInfoDao::Insert(rci, m_log_db);
    return true;
}

bool LogServerModule::handleTick(symphony::RockRequest::ptr request,
                                 symphony::RockResponse::ptr response,
                                 symphony::RockStream::ptr stream) {
    // SYMPHONY_LOG_DEBUG(g_logger) << "handleTick";
    return true;
}

void LogServerModule::onTimer() {
    // 获取时间
    uint64_t now = symphony::GetCurrentMS();
    if (m_last_write_time == 0) {
        m_last_write_time = now;
    }

    if (m_write_cnt == 0) {
        return;
    }

    if (now - m_last_write_time > 1000) {
        if (!m_log_db->ping()) {
            SYMPHONY_LOG_ERROR(g_logger) << "ls db ping fail";
        }
        if (!m_log_db->openTransaction(true)) {
            SYMPHONY_LOG_ERROR(g_logger) << "ls db open transaction fail";
        }

        m_last_write_time = now;
        m_write_cnt = 0;
    }
}

std::string LogServerModule::statusString() {
    std::stringstream ss;
    return ss.str();
}

extern "C" {

symphony::Module* CreateModule() {
    std::cout << "=============LogServerModule Start================="
              << std::endl;
    return new LogServerModule;
}

void DestoryModule(symphony::Module* ptr) {
    std::cout << "=============Destory LogServerModule================="
              << std::endl;
    delete ptr;
}
}

}  // namespace ls
}  // namespace symphony