#include "account_server_module.h"
#include <regex>
#include "account_manager.h"
#include "account_server_protocol.h"
#include "game_log_manager.h"
#include "symphony/proto/msg_account.pb.h"
#include "symphony/proto/msg_id.pb.h"
#include "symphony/proto/msg_ret_code.pb.h"
#include "symphony/symphony.h"
#include "symphony/util/str_util.h"
namespace symphony {
namespace as {
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");
AccountServerModule::AccountServerModule()
    : RockModule("LogServerModule", "1.0.0", "") {}

bool AccountServerModule::onServerReady() {
    if (!m_AccountManager.Init()) {
        return false;
    }

    return true;
}
bool AccountServerModule::handleRockRequest(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    switch (request->getCmd()) {
        case (int)ASCommand::MSG_ACCOUNT_REG_REQ: {
            return handleMsgAccountRegReq(request, response, stream);
        }
        case (int)ASCommand::MSG_ACCOUNT_LOGIN_REQ: {
            return handleMsgAccountLoginReq(request, response, stream);
        }
        case (int)ASCommand::MSG_SEAL_ACCOUNT_REQ: {
            return handleMsgSealAccountReq(request, response, stream);
        }
        case (int)ASCommand::MSG_SET_LAST_SERVER_NTY: {
            return handleMsgSetLastServerNty(request, response, stream);
        }
        default:
            SYMPHONY_LOG_WARN(g_logger)
                << "invalid cmd=0x" << std::hex << request->getCmd();
            return true;
    }
    return true;
}

bool AccountServerModule::handleMsgAccountRegReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::AccountRegReq req;
    req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    SYMPHONY_LOG_INFO(g_logger)
        << "handleMsgAccountRegReq: " << req.DebugString() << std::endl;

    symphony::proto::AccountRegAck ack;

    std::string strAccountName = req.accountname();

    if (m_AccountManager.CheckAccountName(strAccountName, false)) {
        ack.set_retcode(MRC_ACCOUNT_NAME_ERR_FMT);
        response->setBody(ack.SerializeAsString());
        return true;
    }

    str_util::stringTrim(strAccountName);

    CAccountObject* pAccount =
        m_AccountManager.GetAccountObject(strAccountName, req.channel());
    if (pAccount != NULL) {
        ack.set_retcode(MRC_ACCOUNT_NAME_EXIST);

        response->setCmd((int)symphony::proto::MSG_ACCOUNT_REG_ACK);
        response->setBody(ack.SerializeAsString());
        return true;
    }

    pAccount = m_AccountManager.CreateAccountObject(
        strAccountName, req.password(), req.channel());
    if (pAccount == NULL) {
        ack.set_retcode(MRC_UNKNOW_ERROR);

        SYMPHONY_LOG_ERROR(g_logger)
            << "Error CAccountMsgHandler::OnMsgAccountRegReq "
               "RetCode:MRC_UNKNOW_ERROR";
    } else {
        ack.set_retcode(MRC_SUCCESSED);
        ack.set_accountid(pAccount->m_ID);
        CGameLogManager::GetInstancePtr()->LogAccountCreate(
            pAccount->m_ID, pAccount->m_strName, req.reglog());
    }

    return true;
}

bool AccountServerModule::handleMsgAccountLoginReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::AccountLoginReq req;
    req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    SYMPHONY_LOG_INFO(g_logger)
        << "handleMsgAccountLoginReq: " << req.DebugString() << std::endl;

    symphony::proto::AccountLoginAck ack;
    ack.set_review(req.review());
    ack.set_channel(req.channel());
    ack.set_ipaddr(req.loginlog().ipaddr());

    std::string strAccountName = req.accountname();

    if (!m_AccountManager.CheckAccountName(strAccountName, req.channel())) {
        ack.set_retcode(MRC_ACCOUNT_NAME_ERR_FMT);
        SYMPHONY_LOG_ERROR(g_logger)
            << "Error CAccountMsgHandler::OnMsgAccountLoginReq "
               "RetCode:MRC_ACCOUNT_NAME_ERR_FMT";
        response->setCmd((int)symphony::proto::MSG_ACCOUNT_LOGIN_ACK);
        response->setBody(ack.SerializeAsString());
        return true;
    }

    CommonConvert::StringTrim(strAccountName);

    CAccountObject* pAccObj =
        m_AccountManager.GetAccountObject(strAccountName, req.channel());
    if (pAccObj != NULL) {
        // ERROR_RETURN_FALSE(pAccObj->m_ID != 0);
        if (pAccObj->m_ID == 0) {
            return false;
        }
        if (pAccObj->m_uSealTime != 0 &&
            CommonFunc::GetCurrTime() < pAccObj->m_uSealTime) {
            ack.set_retcode(MRC_ACCOUNT_SEALED);
            ack.set_lastsvrid(0);
            ack.set_accountid(0);
        } else if (req.password() != pAccObj->m_strPassword) {
            ack.set_retcode(MRC_INVALID_PASSWORD);
            ack.set_lastsvrid(0);
            ack.set_accountid(0);
        } else {
            ack.set_retcode(MRC_SUCCESSED);
            ack.set_lastsvrid(pAccObj->m_nLastSvrID[0]);
            ack.set_accountid(pAccObj->m_ID);
            CGameLogManager::GetInstancePtr()->LogAccountLogin(
                pAccObj->m_ID, pAccObj->m_strName, req.loginlog());
        }
        response->setCmd((int)symphony::proto::MSG_ACCOUNT_LOGIN_ACK);
        response->setBody(ack.SerializeAsString());
        return TRUE;
    }

    if (!req.fromchannel()) {
        ack.set_retcode(MRC_ACCOUNT_NAME_NOT_EXIST);
        ack.set_lastsvrid(0);
        ack.set_accountid(0);
        response->setCmd((int)symphony::proto::MSG_ACCOUNT_LOGIN_ACK);
        response->setBody(ack.SerializeAsString());
        return TRUE;
    }

    pAccObj = m_AccountManager.CreateAccountObject(
        strAccountName, req.password(), req.channel());
    if (pAccObj == NULL) {
        ack.set_retcode(MRC_UNKNOW_ERROR);
        SYMPHONY_LOG_ERROR(g_logger)
            << "Error CAccountMsgHandler::OnMsgAccountLoginReq "
               "RetCode:MRC_UNKNOW_ERROR";
    } else {
        ack.set_retcode(MRC_SUCCESSED);
        ack.set_accountid(pAccObj->m_ID);
        ack.set_lastsvrid(0);
        CGameLogManager::GetInstancePtr()->LogAccountCreate(
            pAccObj->m_ID, pAccObj->m_strName, req.loginlog());
        CGameLogManager::GetInstancePtr()->LogAccountLogin(
            pAccObj->m_ID, pAccObj->m_strName, req.loginlog());
    }

    response->setCmd((int)symphony::proto::MSG_ACCOUNT_LOGIN_ACK);
    response->setBody(ack.SerializeAsString());
    return TRUE;
}
bool AccountServerModule::handleMsgSealAccountReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::SealAccountReq req;
    req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());

    symphony::proto::SealAccountAck ack;
    uint64_t uAccountID = req.accountid();
    int32_t nLastSvrID = 0;
    if (m_AccountManager.SealAccount(uAccountID, req.accountname(),
                                     req.channel(), req.seal(), req.sealtime(),
                                     nLastSvrID)) {
        ack.set_retcode(MRC_SUCCESSED);

        if (req.seal()) {
            ack.set_accountid(uAccountID);
            ack.set_serverid(nLastSvrID);
        }
    } else {
        ack.set_retcode(MRC_UNKNOW_ERROR);
    }

    response->setCmd((int)symphony::proto::MSG_SEAL_ACCOUNT_ACK);
    response->setBody(ack.SerializeAsString());

    return true;
}
bool AccountServerModule::handleMsgSetLastServerNty(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {
    symphony::proto::SetLastServerNty Nty;

    Nty.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    m_AccountManager.SetLastServer(Nty.accountid(), Nty.serverid());

    return true;
}

bool AccountServerModule::handleRockNotify(symphony::RockNotify::ptr notify,
                                           symphony::RockStream::ptr stream) {
    return true;
}
bool AccountServerModule::onConnect(symphony::Stream::ptr stream) {
    return true;
}
bool AccountServerModule::onDisconnect(symphony::Stream::ptr stream) {
    return true;
}
std::string AccountServerModule::statusString() {
    std::string ss;
    return ss;
}

extern "C" {

symphony::Module* CreateModule() {
    std::cout << "=============AccountServerModule Start================="
              << std::endl;
    return new AccountServerModule;
}

void DestoryModule(symphony::Module* ptr) {
    std::cout << "=============Destory AccountServerModule================="
              << std::endl;
    delete ptr;
}
}
}  // namespace as

}  // namespace symphony
