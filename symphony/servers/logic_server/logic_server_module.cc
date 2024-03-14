#include "symphony/servers/logic_server/logic_server_module.h"
#include "game_log_manager.h"
#include "global_data_manager.h"
#include "login_code_manager.h"
#include "player_manager.h"
#include "player_object.h"
#include "role_module.h"
#include "symphony/common/config_file.h"
#include "symphony/ds/global_data.h"
#include "symphony/ds/static_data.h"
#include "symphony/log.h"
#include "symphony/servers/logic_server/simple_manager.h"
#include "symphony/symphony.h"
namespace symphony {
namespace lcs {
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");

LogicServerModule::LogicServerModule()
    : RockModule("LogicServerModule", "1.0.0", "") {}

bool onServerReady() {
    return true;
}
bool handleRockRequest(symphony::RockRequest::ptr request,
                       symphony::RockResponse::ptr response,
                       symphony::RockStream::ptr stream) {
    switch (request->getCmd()) {
        case (int)symphony::proto::MSG_SELECT_SERVER_REQ:
            return handleMsgSelectServerReq(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_LIST_REQ:
            return handleMsgRoleListReq(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_LIST_ACK:
            return handleMsgRoleListAck(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_CREATE_REQ:
            return handleMsgRoleCreateReq(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_DELETE_REQ:
            return handleMsgRoleDeleteReq(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_LOGIN_REQ:
            return handleMsgRoleLoginReq(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_LOGIN_ACK:
            return handleMsgRoleLoginAck(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_LOGOUT_REQ:
            return handleMsgRoleLogoutReq(request, response, stream);
        case (int)symphony::proto::MSG_DISCONNECT_NTY:
            return handleMsgRoleDisconnect(request, response, stream);
        case (int)symphony::proto::MSG_ABORT_SCENE_NTF:
            return handleMsgAbortSceneNtf(request, response, stream);
        case (int)symphony::proto::MSG_MAIN_COPY_REQ:
            return handleMsgMainCopyReq(request, response, stream);
        case (int)symphony::proto::MSG_BACK_TO_CITY_REQ:
            return handleMsgBackToCityReq(request, response, stream);
        case (int)symphony::proto::MSG_CHAT_MESSAGE_REQ:
            return handleMsgChatMessageReq(request, response, stream);
        case (int)symphony::proto::MSG_ROLE_RECONNECT_REQ:
            return handleMsgReconnectReq(request, response, stream);
        case (int)symphony::proto::MSG_SEAL_ACCOUNT_NTY:
            return handleMsgSealAccountNtf(request, response, stream);
        default:
            SYMPHONY_LOG_ERROR(g_logger)
                << "unknow cmd: " << request->getCmd() << std::endl;
            return false;
    }
    return true;
}
bool handleRockNotify(symphony::RockNotify::ptr notify,
                      symphony::RockStream::ptr stream) {
    return true;
}
bool onConnect(symphony::Stream::ptr stream) {
    return true;
}
bool onDisconnect(symphony::Stream::ptr stream) {
    return true;
}
std::string statusString() {
    std::stringstream ss;
    return ss.str();
}

bool handleMsgSelectServerReq(symphony::RockRequest::ptr request,
                              symphony::RockResponse::ptr response,
                              symphony::RockStream::ptr stream) {
    symphony::proto::SelectServerReq Req;
    Req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());

    // ERROR_RETURN_TRUE(Req.accountid() != 0);

    symphony::proto::SelectServerAck Ack;
    Ack.set_retcode(MRC_SUCCESSED);
    Ack.set_accountid(Req.accountid());
    Ack.set_serverid(CConfigFile::GetInstancePtr()->GetIntValue("areaid"));
    Ack.set_logincode(
        CLoginCodeManager::GetInstancePtr()->CreateLoginCode(Req.accountid()));

    response->setCmd((int)symphony::proto::MSG_SELECT_SERVER_ACK);
    response->setBody(Ack.SerializeAsString());
    return true;
}
bool handleMsgRoleListReq(symphony::RockRequest::ptr request,
                          symphony::RockResponse::ptr response,
                          symphony::RockStream::ptr stream) {
    symphony::proto::RoleListReq Req;
    Req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    if (Req.accountid() == 0) {
        SYMPHONY_LOG_ERROR(g_logger) << "accountid is 0" << std::endl;
        return true;
    }

    if (!CLoginCodeManager::GetInstancePtr()->CheckLoginCode(Req.accountid(),
                                                             Req.logincode())) {
        //      RoleListAck Ack;
        //      Ack.set_retcode(MRC_ILLEGAL_LOGIN_REQ);
        //      return
        //      ServiceBase::GetInstancePtr()->SendMsgProtoBuf(pNetPacket->m_nConnID,
        //      MSG_ROLE_LIST_ACK, 0, pHeader->dwUserData, Ack);

        // 还需要通知网关断开这个连结
    }

    response->setCmd((int)symphony::proto::MSG_ROLE_LIST_REQ);
    response->setBody(request->getBody());
    return true;
}
bool handleMsgRoleListAck(symphony::RockRequest::ptr request,
                          symphony::RockResponse::ptr response,
                          symphony::RockStream::ptr stream) {
    symphony::proto::RoleListAck Ack;
    Ack.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());

    std::vector<UINT64> vtRoleIDs;
    CSimpleManager::GetInstancePtr()->GetRoleIDsByAccountID(Ack.accountid(),
                                                            vtRoleIDs);

    if (Ack.rolelist_size() == vtRoleIDs.size()) {
        response->setCmd((int)symphony::proto::MSG_ROLE_LIST_ACK);
        response->setBody(Ack.SerializeAsString());
        return true;
    }

    // 否则说明有玩家的数据还没有写到数据库中
    // 这个时候就说明这个玩家的数据需要从内存中取

    for (INT32 i = 0; i < vtRoleIDs.size(); i++) {
        UINT64 uRoleID = vtRoleIDs.at(i);
        BOOL bFind = FALSE;

        for (int j = 0; j < Ack.rolelist_size(); j++) {
            const symphony::proto::RoleItem& item = Ack.rolelist(j);
            if (item.roleid() == uRoleID) {
                bFind = TRUE;
                break;
            }
        }

        // 表示没有找到,这时候,就只能从内存中来取了
        if (!bFind) {
            CPlayerObject* pPlayer =
                CPlayerManager::GetInstancePtr()->GetPlayer(uRoleID);
            if (pPlayer == NULL) {
                return true;
            }

            CRoleModule* pRoleModule =
                (CRoleModule*)pPlayer->GetModuleByType(MT_ROLE);
            if (pRoleModule == NULL) {
                return true;
            }

            symphony::proto::RoleItem* pNode = Ack.add_rolelist();
            pNode->set_roleid(pRoleModule->m_pRoleDataObject->m_uRoleID);
            pNode->set_name(pRoleModule->m_pRoleDataObject->m_szName);
            pNode->set_carrer(pRoleModule->m_pRoleDataObject->m_CarrerID);
            pNode->set_level(pRoleModule->m_pRoleDataObject->m_Level);
        }
    }

    response->setCmd((int)symphony::proto::MSG_ROLE_LIST_ACK);
    response->setBody(Ack.SerializeAsString());
}
bool handleMsgRoleCreateReq(symphony::RockRequest::ptr request,
                            symphony::RockResponse::ptr response,
                            symphony::RockStream::ptr stream) {
    symphony::proto::RoleCreateReq Req;
    Req.ParsePartialFromArray(request->getBody().c_str(),
                              request->getBody().size());
    // 检验名字是否可用
    if (Req.accountid() == 0 || Req.carrer() == 0) {
        return true;
    }

    symphony::proto::RoleCreateAck Ack;

    Ack.set_accountid(Req.accountid());
    Ack.set_roleid(0);
    Ack.set_carrer(Req.carrer());
    Ack.set_name(Req.name());

    std::string strName = Req.name();

    if (!CommonConvert::IsTextUTF8(strName.c_str(), (UINT32)strName.size())) {
        Ack.set_retcode(MRC_ROLE_NAME_MUST_UTF8);
        response->setCmd((int)symphony::proto::MSG_ROLE_CREATE_ACK);
        response->setBody(Ack.SerializeAsString());
        return true;
    }

    if (CSimpleManager::GetInstancePtr()->CheckNameExist(strName)) {
        Ack.set_retcode(MRC_ROLE_NAME_EXIST);
        response->setCmd((int)symphony::proto::MSG_ROLE_CREATE_ACK);
        response->setBody(Ack.SerializeAsString());
        return TRUE;
    }

    StCarrerInfo* pCarrerInfo =
        CStaticData::GetInstancePtr()->GetCarrerInfo(Req.carrer());
    if (pCarrerInfo == NULL) {
        Ack.set_retcode(MRC_INVALID_CARRERID);
        response->setCmd((int)symphony::proto::MSG_ROLE_CREATE_ACK);
        response->setBody(Ack.SerializeAsString());
        return TRUE;
    }

    UINT64 u64RoleID = CGlobalDataManager::GetInstancePtr()->MakeNewGuid();
    if (u64RoleID == 0) {
        return true;
    }
    if (u64RoleID == 0) {
        return true;
    }

    CSimpleInfo* pSimpleInfo =
        CSimpleManager::GetInstancePtr()->CreateSimpleInfo(
            u64RoleID, Req.accountid(), Req.name(), Req.carrer());
    if (pSimpleInfo == NULL) {
        return true;
    }

    CPlayerObject* pPlayer =
        CPlayerManager::GetInstancePtr()->CreatePlayer(u64RoleID);
    if (pPlayer == NULL || pPlayer->Init(u64RoleID) == FALSE) {
        return true;
    }

    CRoleModule* pRoleModule = (CRoleModule*)pPlayer->GetModuleByType(MT_ROLE);
    pRoleModule->InitBaseData(u64RoleID, Req.name(), Req.carrer(),
                              Req.accountid(), Req.channel());
    pPlayer->OnCreate(u64RoleID);

    CGameLogManager::GetInstancePtr()->LogRoleCreate(pPlayer);

    Ack.set_retcode(MRC_SUCCESSED);
    Ack.set_roleid(u64RoleID);
    response->setCmd((int)symphony::proto::MSG_ROLE_CREATE_ACK);
    response->setBody(Ack.SerializeAsString());

    return TRUE;
}
bool handleMsgRoleDeleteReq(symphony::RockRequest::ptr request,
                            symphony::RockResponse::ptr response,
                            symphony::RockStream::ptr stream);
bool handleMsgRoleLoginReq(symphony::RockRequest::ptr request,
                           symphony::RockResponse::ptr response,
                           symphony::RockStream::ptr stream);
bool handleMsgRoleLoginAck(symphony::RockRequest::ptr request,
                           symphony::RockResponse::ptr response,
                           symphony::RockStream::ptr stream);
bool handleMsgRoleLogoutReq(symphony::RockRequest::ptr request,
                            symphony::RockResponse::ptr response,
                            symphony::RockStream::ptr stream);
bool handleMsgRoleDisconnect(symphony::RockRequest::ptr request,
                             symphony::RockResponse::ptr response,
                             symphony::RockStream::ptr stream);
bool handleMsgAbortSceneNtf(symphony::RockRequest::ptr request,
                            symphony::RockResponse::ptr response,
                            symphony::RockStream::ptr stream);
bool handleMsgMainCopyReq(symphony::RockRequest::ptr request,
                          symphony::RockResponse::ptr response,
                          symphony::RockStream::ptr stream);
bool handleMsgBackToCityReq(symphony::RockRequest::ptr request,
                            symphony::RockResponse::ptr response,
                            symphony::RockStream::ptr stream);
bool handleMsgChatMessageReq(symphony::RockRequest::ptr request,
                             symphony::RockResponse::ptr response,
                             symphony::RockStream::ptr stream);
bool handleMsgReconnectReq(symphony::RockRequest::ptr request,
                           symphony::RockResponse::ptr response,
                           symphony::RockStream::ptr stream);
bool handleMsgSealAccountNtf(symphony::RockRequest::ptr request,
                             symphony::RockResponse::ptr response,
                             symphony::RockStream::ptr stream);
}  // namespace lcs
}  // namespace symphony