#include "symphony/servers/login_server/login_server_module.h"
#include "login_client_manager.h"
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
    switch (request->getCmd()) {
        default:
            SYMPHONY_LOG_ERROR(g_logger)
                << "unknow cmd: " << request->getCmd() << std::endl;
            return true;
    }
    return true;
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
    if (req.serverid() != 0) {
        return true;
    }
    if (req.accountid() > 0) {
        return true;
    }

    int32_t nConnID = stream->getConnId();
    if (!CLoginClientMgr::GetInstancePtr()->CheckClientMessage(
            nConnID, request->getCmd())) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "非法的消息请求SelectServer!!!" << std::endl;
        return TRUE;
    }

    CLoginClientMgr::GetInstancePtr()->RemoveByConnID(nConnID);

    LogicServerNode* pServerNode =
        m_LogicSvrMgr.GetLogicServerInfo(req.serverid());
    if (pServerNode == NULL) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "选择服务器错误 无效的服务器ID:" << req.serverid() << std::endl;
        symphony::proto::SelectServerAck ack;
        ack.set_serveraddr("0.0.0.0");
        ack.set_serverport(0);
        ack.set_retcode(MRC_INVALID_SERVER_ID);
        response->setCmd((int)symphony::proto::MSG_SELECT_SERVER_ACK);
        response->setBody(ack.SerializeAsString());
        return TRUE;
    }

    if (pServerNode->m_ServerFlag == ESF_MAINTAIN ||
        pServerNode->m_ServerStatus != ESS_SVR_ONLINE) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "服务器:" << req.serverid()
            << " 维护中 ServerFlag:" << pServerNode->m_ServerFlag << std::endl;
        symphony::proto::SelectServerAck ack;
        ack.set_serveraddr("0.0.0.0");
        ack.set_serverport(0);
        ack.set_retcode(MRC_SERVER_MAINTAIN);
        response->setCmd((int)symphony::proto::MSG_SELECT_SERVER_ACK);
        response->setBody(ack.SerializeAsString());
        return TRUE;
    }

    if (pServerNode->m_ServerStatus != ESS_SVR_ONLINE) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "选择服务器错误 服务器:" << req.serverid() << " 不在线"
            << std::endl;
        symphony::proto::SelectServerAck ack;
        ack.set_serveraddr("0.0.0.0");
        ack.set_serverport(0);
        ack.set_retcode(MRC_SERVER_NOT_AVAILABLE);
        response->setCmd((int)symphony::proto::MSG_SELECT_SERVER_ACK);
        response->setBody(ack.SerializeAsString());
        return TRUE;
    }

    if (pServerNode->m_uSvrOpenTime > CommonFunc::GetCurrTime()) {
        symphony::proto::SelectServerAck ack;
        ack.set_serveraddr("0.0.0.0");
        ack.set_serverport(0);
        ack.set_retcode(MRC_SERVER_NOT_OPENTIME);
        response->setCmd((int)symphony::proto::MSG_SELECT_SERVER_ACK);
        response->setBody(ack.SerializeAsString());
        return TRUE;
    }

    req.set_checkrole(pServerNode->m_ServerFlag == ESF_BUSY);
    response->setCmd((int)symphony::proto::MSG_SELECT_SERVER_REQ);
    response->setBody(req.SerializeAsString());
    return TRUE;
}
bool LoginServerModule::handleMsgAccountRegAck(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::AccountRegAck ack;
    ack.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());

    if (stream->getConnId() == 0) {
        return true;
    }

    response->setCmd((int)symphony::proto::MSG_ACCOUNT_REG_ACK);
    response->setBody(ack.SerializeAsString());
    return true;
}
bool LoginServerModule::handleMsgAccountLoginAck(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::AccountLoginAck Ack;
    Ack.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());

    INT32 nConnID = stream->getConnId();
    if (nConnID == 0) {
        return TRUE;
    }

    LogicServerNode* pNode = m_LogicSvrMgr.GetLogicServerInfo(Ack.lastsvrid());
    if (pNode == NULL) {
        pNode = m_LogicSvrMgr.GetSuggestServer(Ack.review(), Ack.channel(),
                                               Ack.ipaddr());
    }

    if (pNode == NULL) {
        Ack.set_lastsvrid(0);
        Ack.set_lastsvrname("No Server");
    } else {
        Ack.set_lastsvrid(pNode->m_nServerID);
        Ack.set_lastsvrname(pNode->m_strSvrName);
    }

    response->setCmd((int)symphony::proto::MSG_ACCOUNT_LOGIN_ACK);
    response->setBody(Ack.SerializeAsString());

    return TRUE;
}
bool LoginServerModule::handleMsgLogicSvrRegReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::LogicRegToLoginReq Req;
    Req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    m_LogicSvrMgr.RegisterLogicServer(stream->getConnId(), Req.serverid(),
                                      Req.serverport(), Req.httpport(),
                                      Req.servername(), Req.svrinnerip());
    symphony::proto::LogicRegToLoginAck Ack;
    Ack.set_retcode(MRC_SUCCESSED);

    LogicServerNode* pServerNode =
        m_LogicSvrMgr.GetLogicServerInfo(Req.serverid());
    if (pServerNode != NULL) {
        Ack.set_svropentime(pServerNode->m_uSvrOpenTime);
    }

    response->setCmd((int)symphony::proto::MSG_LOGIC_REGTO_LOGIN_ACK);
    response->setBody(Ack.SerializeAsString());

    // CConnection* pConnection =
    //     ServiceBase::GetInstancePtr()->GetConnectionByID(pPacket->m_nConnID);
    // ERROR_RETURN_TRUE(pConnection != NULL);
    // pConnection->SetConnectionData(1);
    return true;
}
bool LoginServerModule::handleMsgLogicUpdateReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::LogicUpdateInfoReq Req;
    Req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());

    if (Req.serverid() <= 0) {
        return TRUE;
    }
    m_LogicSvrMgr.UpdateLogicServerInfo(
        Req.serverid(), Req.maxonline(), Req.curonline(), Req.totalnum(),
        Req.cachenum(), Req.status(), Req.dberrcnt(), Req.servername());

    LogicServerNode* pServerNode =
        m_LogicSvrMgr.GetLogicServerInfo(Req.serverid());
    if (pServerNode == NULL) {
        return TRUE;
    }

    symphony::proto::LogicUpdateInfoAck Ack;
    Ack.set_svropentime(pServerNode->m_uSvrOpenTime);
    Ack.set_retcode(MRC_SUCCESSED);
    response->setCmd((int)symphony::proto::MSG_LOGIC_UPDATE_ACK);
    response->setBody(Ack.SerializeAsString());
    return true;
}
bool LoginServerModule::handleMsgSelectServerAck(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::SelectServerAck Ack;
    Ack.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());

    if (Ack.retcode() != MRC_SUCCESSED) {
        response->setCmd((int)symphony::proto::MSG_SELECT_SERVER_ACK);
        response->setBody(Ack.SerializeAsString());
        return TRUE;
    }

    LogicServerNode* pNode = m_LogicSvrMgr.GetLogicServerInfo(Ack.serverid());
    if (pNode == NULL) {
        return TRUE;
    }

    Ack.set_serveraddr(pNode->m_strOuterAddr);
    Ack.set_serverport(pNode->m_nPort);
    Ack.set_retcode(MRC_SUCCESSED);

    response->setCmd((int)symphony::proto::MSG_SELECT_SERVER_ACK);
    response->setBody(Ack.SerializeAsString());

    symphony::proto::SetLastServerNty Nty;
    Nty.set_accountid(Ack.accountid());
    Nty.set_serverid(Ack.serverid());

    symphony::RockRequest::ptr to_cmd =
        std::make_shared<symphony::RockRequest>();
    // to_cmd->setSn(symphony::Atomic::addFetch(m_sn, 1));
    to_cmd->setCmd((int)symphony::proto::MSG_SET_LAST_SERVER_NTY);
    to_cmd->setBody(Nty.SerializeAsString());
    stream->request(to_cmd, 1000);
    return true;
    // CGameService::GetInstancePtr()->SendCmdToAccountConnection(
    //     MSG_SET_LAST_SERVER_NTY, 0, 1, Nty);
}
bool LoginServerModule::handleMsgSealAccountAck(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::SealAccountAck Ack;
    Ack.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());

    int nConnID = stream->getConnId();
    if (nConnID == 0) {
        return true;
    }

    std::string strResult = CommonConvert::IntToString((int64_t)0);
    response->setCmd((int)symphony::proto::MSG_SEAL_ACCOUNT_ACK);
    response->setBody(strResult);

    if (Ack.retcode() != MRC_SUCCESSED) {
        return TRUE;
    }

    if (Ack.accountid() > 0) {
        symphony::proto::SealAccountNtf Ntf;
        Ntf.set_accountid(Ack.accountid());
        // INT32 nLogicConnID = m_LogicSvrMgr.GetLogicConnID(Ack.serverid());

        symphony::RockRequest::ptr to_cmd =
            std::make_shared<symphony::RockRequest>();
        // to_cmd->setSn(symphony::Atomic::addFetch(m_sn, 1));
        to_cmd->setCmd((int)symphony::proto::MSG_SEAL_ACCOUNT_NTY);
        to_cmd->setBody(Ntf.SerializeAsString());
        stream->request(to_cmd, 1000);
    }

    return TRUE;
}
bool LoginServerModule::handleMsgGameParamReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::Msg_GameParamReq Req;
    Req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());

    symphony::proto::Msg_GameParamAck Ack;
    for (INT32 i = 0; i < (int)m_LogicSvrMgr.m_vtGameParam.size(); i++) {
        GameParamNode& tNode = m_LogicSvrMgr.m_vtGameParam.at(i);
        if (tNode.m_nChannel == 0 || tNode.m_nChannel == Req.channel()) {
            Ack.add_paramkey(tNode.m_strParamKey);
            Ack.add_paramvalue(tNode.m_strParamValue);
        }
    }

    response->setCmd((int)symphony::proto::MSG_GAME_PARAM_ACK);
    response->setBody(Ack.SerializeAsString());
    return TRUE;
}

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