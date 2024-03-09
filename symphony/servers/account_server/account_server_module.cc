#include "account_server_module.h"
#include <regex>
#include "account_server_protocol.h"
#include "symphony/proto/msg_account.pb.h"
#include "symphony/proto/msg_id.pb.h"
#include "symphony/proto/msg_ret_code.pb.h"
#include "util/str_util.h"
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
        // CGameLogManager::GetInstancePtr()->LogAccountCreate(
        //     pAccount->m_ID, pAccount->m_strName, req.reglog());
    }

    return true;
}

bool AccountServerModule::handleMsgAccountLoginReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}
bool AccountServerModule::handleMsgSealAccountReq(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}
bool AccountServerModule::handleMsgSetLastServerNty(
    symphony::RockRequest::ptr request,
    symphony::RockResponse::ptr response,
    symphony::RockStream::ptr stream) {}

bool AccountServerModule::handleRockNotify(symphony::RockNotify::ptr notify,
                                           symphony::RockStream::ptr stream) {}
bool AccountServerModule::onConnect(symphony::Stream::ptr stream) {}
bool AccountServerModule::onDisconnect(symphony::Stream::ptr stream) {}
std::string AccountServerModule::statusString() {}
}  // namespace as

}  // namespace symphony
