#include "center_server_module.h"
#include "symphony/servers/center_server/logic_svr_manager.h"
#include "symphony/symphony.h"
namespace symphony {
namespace cs {
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");
typedef std::shared_ptr<CenterServerModule> ptr;

CenterServerModule::CenterServerModule()
    : RockModule("CenterServerModule", "1.0.0", "") {}

bool CenterServerModule::onServerReady() {
    return true;
}
bool CenterServerModule::handleRockRequest(symphony::RockRequest::ptr request,
                                           symphony::RockResponse::ptr response,
                                           symphony::RockStream::ptr stream) {
    switch (request->getCmd()) {
        case (int)symphony::proto::MSG_LOGIC_REGTO_CENTER_REQ:
            return handleMsgLogicSvrRegReq(request, response, stream);
        default:
            SYMPHONY_LOG_ERROR(g_logger)
                << "unknow cmd: " << request->getCmd() << std::endl;
            return false;
    }
    return true;
}
bool CenterServerModule::handleRockNotify(symphony::RockNotify::ptr notify,
                                          symphony::RockStream::ptr stream) {
    return true;
}
bool CenterServerModule::onConnect(symphony::Stream::ptr stream) {
    return true;
}
bool CenterServerModule::onDisconnect(symphony::Stream::ptr stream) {
    return true;
}
std::string statusString() {
    std::stringstream ss;
    return ss.str();
}

bool CenterServerModule::handleMsgLogicSvrRegReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::SvrRegToSvrReq Req;
    Req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());

    CLogicSvrMgr::GetInstancePtr()->RegisterLogicServer(
        stream->getConnId(), Req.serverid(), Req.servername());
    SYMPHONY_LOG_INFO(g_logger)
        << "ServerID:" << Req.serverid() << " Register Successed!";

    symphony::proto::SvrRegToSvrAck Ack;
    Ack.set_retcode(MRC_SUCCESSED);
    response->setCmd((int)symphony::proto::MSG_LOGIC_REGTO_CENTER_ACK);
    response->setBody(Ack.SerializeAsString());
    return true;
}
}  // namespace cs
}  // namespace symphony