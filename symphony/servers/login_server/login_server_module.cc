#include "symphony/servers/login_server/login_server_module.h"
#include "symphony/module.h"
#include "symphony/symphony.h"
namespace symphony {
namespace los {
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");
LoginServerModule::LoginServerModule()
    : RockModule("LoginServerModule", "1.0.0", "") {}

bool LoginServerModule::onServerReady() {
    return true;
}
bool LoginServerModule::handleRockRequest(symphony::RockRequest::ptr request,
                                          symphony::RockResponse::ptr response,
                                          symphony::RockStream::ptr stream) {
    switch (request->getCmd()) {}
}

bool LoginServerModule::handleMsgCheckVersionReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::CheckVersionReq req;
    req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    SYMPHONY_LOG_INFO(g_logger)
        << "handleMsgCheckVersionReq: " << req.DebugString() << std::endl;
    symphony::proto::CheckVersionAck ack;
    ack.set_retcode(MRC_SUCCESSED);
    ack.set_clientverion("0.0.1");
    response->setCmd((int)symphony::proto::MSG_CHECK_VERSION_ACK);
    response->setBody(ack.SerializeAsString());
    return true;
}
bool LoginServerModule::handleMsgAccountRegReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::AccountRegReq req;
    req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    auto sock = (sockaddr_in*)stream->getRemoteAddress()->getAddr();
    struct in_addr in = sock->sin_addr;
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &in, str, sizeof(str));
    uint32_t ip = htonl(inet_addr(str));
    req.mutable_reglog()->set_ipaddr(ip);

    response->setCmd((int)symphony::proto::MSG_ACCOUNT_REG_REQ);
    response->setBody(req.SerializeAsString());
    return true;
}
bool LoginServerModule::handleMsgAccountLoginReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::AccountLoginReq req;
    req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    auto sock = (sockaddr_in*)stream->getRemoteAddress()->getAddr();
    struct in_addr in = sock->sin_addr;
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &in, str, sizeof(str));
    uint32_t ip = htonl(inet_addr(str));
    req.mutable_loginlog()->set_ipaddr(ip);

    response->setCmd((int)symphony::proto::MSG_ACCOUNT_LOGIN_REQ);
    response->setBody(req.SerializeAsString());
    return true;
}
bool LoginServerModule::handleMsgServerListReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::ClientServerListReq req;
    req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    symphony::proto::ClientServerListAck ack;

    auto sock = (sockaddr_in*)stream->getRemoteAddress()->getAddr();
    struct in_addr in = sock->sin_addr;
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &in, str, sizeof(str));
    uint32_t ip = htonl(inet_addr(str));

    bool bReviewClient = req.review();
    for (auto itor = m_LogicSvrMgr.begin(); itor != m_LogicSvrMgr.end();
         itor++) {
        LogicServerNode* pTempNode = itor->second;
        // 如果是评审包
        if (bReviewClient) {
            if (pTempNode->m_ServerFlag != ESF_REVIEW) {
                continue;
            }
        } else {
            if (pTempNode->m_ServerFlag == ESF_REVIEW ||
                pTempNode->m_ServerFlag == ESF_SHUTDOWN) {
                continue;
            }

            if (!pTempNode->CheckIP(ip)) {
                // 需要检测IP
                continue;
            }

            if (!pTempNode->CheckChannel(req.channel())) {
                // 需要检测渠道
                continue;
            }

            if (!pTempNode->CheckVersion(req.version())) {
                // 需要检测版本
                continue;
            }
        }

        symphony::proto::ClientServerNode* pClientNode = ack.add_svrnode();
        pClientNode->set_svrid(pTempNode->m_nServerID);
        pClientNode->set_svrname(pTempNode->m_strSvrName);
        pClientNode->set_svrflag(pTempNode->m_ServerFlag);
        pClientNode->set_cornermark(pTempNode->m_CornerMark);
        pClientNode->set_svropentime(pTempNode->m_uSvrOpenTime);
        pClientNode->set_svrstatus(pTempNode->m_ServerStatus);

        if (pTempNode->m_ServerStatus != ESS_SVR_ONLINE) {
            if (pTempNode->m_ServerFlag >= ESF_GOOD &&
                pTempNode->m_ServerFlag <= ESF_FULL) {
                pClientNode->set_svrflag(ESF_MAINTAIN);
            }
        }
    }

    response->setCmd((int)symphony::proto::MSG_SERVER_LIST_ACK);
    response->setBody(ack.SerializeAsString());

    return true;
}
bool LoginServerModule::handleMsgSelectServerReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::SelectServerReq req;
    req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());

    ERROR_RETURN_TRUE(req.serverid() != 0);
    ERROR_RETURN_TRUE(req.accountid() > 0);
    if (!CLoginClientMgr::GetInstancePtr()->CheckClientMessage(
            nConnID, pPacket->m_nMsgID)) {
        CLog::GetInstancePtr()->LogError("非法的消息请求SelectServer!!!");
        return TRUE;
    }

    CLoginClientMgr::GetInstancePtr()->RemoveByConnID(nConnID);

    LogicServerNode* pServerNode =
        m_LogicSvrMgr.GetLogicServerInfo(Req.serverid());
    if (pServerNode == NULL) {
        CLog::GetInstancePtr()->LogError("选择服务器错误 无效的服务器ID:%d",
                                         Req.serverid());
        SelectServerAck Ack;
        Ack.set_serveraddr("0.0.0.0");
        Ack.set_serverport(0);
        Ack.set_retcode(MRC_INVALID_SERVER_ID);
        ERROR_RETURN_TRUE(ServiceBase::GetInstancePtr()->SendMsgProtoBuf(
            nConnID, MSG_SELECT_SERVER_ACK, 0, 0, Ack));
        return TRUE;
    }

    if (pServerNode->m_ServerFlag == ESF_MAINTAIN ||
        pServerNode->m_ServerStatus != ESS_SVR_ONLINE) {
        CLog::GetInstancePtr()->LogError("服务器:%d 维护中 ServerFlag:%d",
                                         Req.serverid(),
                                         pServerNode->m_ServerFlag);
        SelectServerAck Ack;
        Ack.set_serveraddr("0.0.0.0");
        Ack.set_serverport(0);
        Ack.set_retcode(MRC_SERVER_MAINTAIN);
        ERROR_RETURN_TRUE(ServiceBase::GetInstancePtr()->SendMsgProtoBuf(
            nConnID, MSG_SELECT_SERVER_ACK, 0, 0, Ack));
        return TRUE;
    }

    if (pServerNode->m_ServerStatus != ESS_SVR_ONLINE) {
        CLog::GetInstancePtr()->LogError("选择服务器错误 服务器:%d 不在线",
                                         Req.serverid());
        SelectServerAck Ack;
        Ack.set_serveraddr("0.0.0.0");
        Ack.set_serverport(0);
        Ack.set_retcode(MRC_SERVER_NOT_AVAILABLE);
        ERROR_RETURN_TRUE(ServiceBase::GetInstancePtr()->SendMsgProtoBuf(
            nConnID, MSG_SELECT_SERVER_ACK, 0, 0, Ack));
        return TRUE;
    }

    if (pServerNode->m_uSvrOpenTime > CommonFunc::GetCurrTime()) {
        SelectServerAck Ack;
        Ack.set_serveraddr("0.0.0.0");
        Ack.set_serverport(0);
        Ack.set_retcode(MRC_SERVER_NOT_OPENTIME);
        ERROR_RETURN_TRUE(ServiceBase::GetInstancePtr()->SendMsgProtoBuf(
            nConnID, MSG_SELECT_SERVER_ACK, 0, 0, Ack));
        return TRUE;
    }

    Req.set_checkrole(pServerNode->m_ServerFlag == ESF_BUSY);
    ERROR_RETURN_TRUE(ServiceBase::GetInstancePtr()->SendMsgProtoBuf(
        pServerNode->m_nConnID, MSG_SELECT_SERVER_REQ, 0, nConnID, Req));

    return TRUE;
}
bool LoginServerModule::handleMsgAccountRegAck(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream);
bool LoginServerModule::handleMsgAccountLoginAck(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream);
bool LoginServerModule::handleMsgLogicSvrRegReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream);
bool LoginServerModule::handleMsgLogicUpdateReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream);
bool LoginServerModule::handleMsgSelectServerAck(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream);
bool LoginServerModule::handleMsgSealAccountAck(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream);
bool LoginServerModule::handleMsgGameParamReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream);

extern "C" {

symphony::Module* CreateModule() {
    std::cout << "=============LoginServerModule Start================="
              << std::endl;
    return new LoginServerModule;
}

void DestoryModule(symphony::Module* ptr) {
    std::cout << "=============Destory LoginServerModule================="
              << std::endl;
    delete ptr;
}
}
}  // namespace los
}  // namespace symphony