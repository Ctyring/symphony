#include "log_server_module.h"
#include "log_server_protocol.h"
#include "orm_out/symphony/log/account_create_info.h"
#include "orm_out/symphony/log/account_login_info.h"

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
            return handleTick(request, response, stream);
        }
        case (int)LSCommand::ACCOUNT_CREATE: {
            return handleAccountCreate(request, response, stream);
        }
        case (int)LSCommand::ACCOUNT_LOGIN: {
            return handleAccountLogin(request, response, stream);
        }
        default:
            SYMPHONY_LOG_WARN(g_logger)
                << "invalid cmd=0x" << std::hex << request->getCmd();
            break;
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

bool LogServerModule::handleTick(symphony::RockRequest::ptr request,
                                 symphony::RockResponse::ptr response,
                                 symphony::RockStream::ptr stream) {
    // SYMPHONY_LOG_DEBUG(g_logger) << "handleTick";
    return true;
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