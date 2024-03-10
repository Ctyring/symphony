#include "symphony/servers/proxy_server/proxy_server_module.h"
#include "symphony/log.h"
#include "symphony/symphony.h"
namespace symphony {
namespace ps {
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");
ProxyServerModule::ProxyServerModule()
    : RockModule("ProxyServerModule", "1.0.0", "") {}

bool ProxyServerModule::onServerReady() {
    return true;
}
bool ProxyServerModule::handleRockRequest(symphony::RockRequest::ptr request,
                                          symphony::RockResponse::ptr response,
                                          symphony::RockStream::ptr stream) {
    switch (request->getCmd()) {
        case (int)symphony::proto::MSG_GASVR_REGTO_PROXY_REQ:
            return handleMsgGameSvrRegister(request, response, stream);
        case (int)symphony::proto::MSG_BROAD_MESSAGE_NOTIFY:
            return handleMsgBroadMessageNty(request, response, stream);
        case (int)symphony::proto::MSG_NOTIFY_INTO_SCENE:
            return handleMsgNotifyIntoSceneNtf(request, response, stream);
        case (int)symphony::proto::MSG_ENTER_SCENE_REQ:
            return handleMsgEnterSceneReq(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_LOGIN_ACK:
            return handleMsgRoleLoginAck(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_LOGOUT_REQ:
            return handleMsgRoleLogoutReq(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_OTHER_LOGIN_NTY:
            return handleMsgKickoutNty(request, response, stream);
        case (int)symphony::proto::MSG_REMOVE_CONNECT_NTY:
            return handleMsgRemoveConnectNty(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_LIST_REQ:
            return handleMsgRelayToLogic(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_CREATE_REQ:
            return handleMsgRelayToLogic(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_DELETE_REQ:
            return handleMsgRelayToLogic(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_LOGIN_REQ:
            return handleMsgRelayToLogic(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_RECONNECT_REQ:
            return handleMsgReconnectReq(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_RECONNECT_ACK:
            return handleMsgReconnectAck(request, response, stream);
        default:
            SYMPHONY_LOG_ERROR(g_logger)
                << "ProxyServerModule::handleRockRequest: unknown cmd: "
                << request->getCmd();
            break;
    }
    return true;
}

bool ProxyServerModule::handleMsgGameSvrRegister(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::SvrRegToSvrReq req;
}
bool ProxyServerModule::handleMsgBroadMessageNty(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}
bool ProxyServerModule::handleMsgNotifyIntoSceneNtf(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}
bool ProxyServerModule::handleMsgEnterSceneReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}
bool ProxyServerModule::handleMsgRoleLoginAck(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}
bool ProxyServerModule::handleMsgRoleLogoutReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}
bool ProxyServerModule::handleMsgKickoutNty(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}
bool ProxyServerModule::handleMsgRemoveConnectNty(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}
bool ProxyServerModule::handleMsgRelayToLogic(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}
bool ProxyServerModule::handleMsgReconnectReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}
bool ProxyServerModule::handleMsgReconnectAck(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}

void ProxyServerModule::onTimer() {}

std::string ProxyServerModule::statusString() {
    std::stringstream ss;
    return ss.str();
}

extern "C" {

symphony::Module* CreateModule() {
    std::cout << "=============ProxyServerModule Start================="
              << std::endl;
    return new ProxyServerModule;
}

void DestoryModule(symphony::Module* ptr) {
    std::cout << "=============Destory ProxyServerModule================="
              << std::endl;
    delete ptr;
}
}
}  // namespace ps
}  // namespace symphony