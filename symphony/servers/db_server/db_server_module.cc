#include "db_server_module.h"
#include "db_manager.h"
#include "db_server_protocol.h"
#include "symphony/log.h"
#include "symphony/proto/msg_game.pb.h"
#include "symphony/proto/msg_id.pb.h"
#include "symphony/proto/msg_ret_code.pb.h"
#include "symphony/proto/msg_role.pb.h"
namespace symphony {
namespace db {
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");
DBServerModule::DBServerModule() : RockModule("DBServerModule", "1.0.0", "") {}
bool DBServerModule::onServerReady() {
    return true;
}
bool DBServerModule::handleRockRequest(symphony::RockRequest::ptr request,
                                       symphony::RockResponse::ptr response,
                                       symphony::RockStream::ptr stream) {
    switch (request->getCmd()) {
        case (int)symphony::db::DSCommand::MSG_ROLE_LIST_REQ:
            return handleMsgRoleListReq(request, response, stream);
        case (int)symphony::db::DSCommand::MSG_ROLE_LOGIN_REQ:
            return handleMsgRoleLoginReq(request, response, stream);
        case (int)symphony::db::DSCommand::MSG_ROLE_DELETE_REQ:
            return handleMsgRoleDeleteReq(request, response, stream);
        case (int)symphony::db::DSCommand::MSG_DB_EXE_SQL_REQ:
            return handleMsgExeSqlReq(request, response, stream);
        case (int)symphony::db::DSCommand::MSG_LOGIC_REGTO_DBSVR_REQ:
            return handleMsgLogicSvrRegReq(request, response, stream);
        default:
            SYMPHONY_LOG_ERROR(g_logger)
                << "unknow cmd: " << request->getCmd() << std::endl;
            return false;
    }
    return true;
}
bool handleMsgRoleListReq(symphony::RockRequest::ptr request,
                          symphony::RockResponse::ptr response,
                          symphony::RockStream::ptr stream) {
    symphony::proto::RoleListReq req;
    req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    SYMPHONY_LOG_INFO(g_logger)
        << "handleMsgRoleListReq: " << req.DebugString() << std::endl;
    symphony::proto::RoleListAck ack;
    DBMgr::GetInstance()->getRoleList(req.accountid(), ack);
    response->setCmd((int)symphony::proto::MSG_ROLE_LIST_ACK);
    response->setBody(ack.SerializeAsString());
    return true;
}
bool handleMsgRoleLoginReq(symphony::RockRequest::ptr request,
                           symphony::RockResponse::ptr response,
                           symphony::RockStream::ptr stream) {
    symphony::proto::RoleLoginReq req;
    req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    SYMPHONY_LOG_INFO(g_logger)
        << "handleMsgRoleLoginReq: " << req.DebugString() << std::endl;
    symphony::proto::DBRoleLoginAck ack;
    ack.set_retcode(MRC_SUCCESSED);
    ack.set_roleid(req.roleid());
    if (!DBMgr::GetInstance()->getRoleData(req.roleid(), ack)) {
        ack.set_retcode(MRC_INVALID_ROLEID);
        ack.set_roleid(req.roleid());
        response->setCmd((int)symphony::proto::MSG_ROLE_LOGIN_ACK);
        response->setBody(ack.SerializeAsString());
        return true;
    }

    DBMgr::GetInstance()->getBagData(req.roleid(), ack);
    DBMgr::GetInstance()->getCopyData(req.roleid(), ack);
    DBMgr::GetInstance()->getEquipData(req.roleid(), ack);
    DBMgr::GetInstance()->getGemData(req.roleid(), ack);
    DBMgr::GetInstance()->getPetData(req.roleid(), ack);
    DBMgr::GetInstance()->getPartnerData(req.roleid(), ack);
    DBMgr::GetInstance()->getTaskData(req.roleid(), ack);
    DBMgr::GetInstance()->getMountData(req.roleid(), ack);
    DBMgr::GetInstance()->getActivtyData(req.roleid(), ack);
    DBMgr::GetInstance()->getMailData(req.roleid(), ack);
    DBMgr::GetInstance()->getCounterData(req.roleid(), ack);
    DBMgr::GetInstance()->getFriendData(req.roleid(), ack);
    DBMgr::GetInstance()->getSkillData(req.roleid(), ack);
    response->setCmd((int)symphony::proto::MSG_ROLE_LOGIN_ACK);
    response->setBody(ack.SerializeAsString());
    return true;
}
bool handleMsgRoleDeleteReq(symphony::RockRequest::ptr request,
                            symphony::RockResponse::ptr response,
                            symphony::RockStream::ptr stream) {
    symphony::proto::RoleDeleteReq req;
    req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    return true;
}
bool handleMsgExeSqlReq(symphony::RockRequest::ptr request,
                        symphony::RockResponse::ptr response,
                        symphony::RockStream::ptr stream) {
    return true;
}
bool handleMsgLogicSvrRegReq(symphony::RockRequest::ptr request,
                             symphony::RockResponse::ptr response,
                             symphony::RockStream::ptr stream) {
    symphony::proto::LogicRegToDbSvrReq req;
    req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());

    symphony::proto::LogicRegToDbSvrAck ack;
    ack.set_retcode(MRC_SUCCESSED);
    response->setCmd((int)symphony::proto::MSG_LOGIC_REGTO_DBSVR_ACK);
    response->setBody(ack.SerializeAsString());
    return true;
}

bool DBServerModule::handleRockNotify(symphony::RockNotify::ptr notify,
                                      symphony::RockStream::ptr stream) {
    return true;
}
bool DBServerModule::onConnect(symphony::Stream::ptr stream) {
    return true;
}
bool DBServerModule::onDisconnect(symphony::Stream::ptr stream) {
    return true;
}
std::string DBServerModule::statusString() {
    std::stringstream ss;
    return ss.str();
}

extern "C" {

symphony::Module* CreateModule() {
    std::cout << "=============DBServerModule Start================="
              << std::endl;
    return new DBServerModule;
}

void DestoryModule(symphony::Module* ptr) {
    std::cout << "=============Destory DBServerModule================="
              << std::endl;
    delete ptr;
}
}
}  // namespace db
}  // namespace symphony