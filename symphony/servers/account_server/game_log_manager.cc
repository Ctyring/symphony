// #include "../LogData/LogStruct.h"
// #include "CommonSocket.h"
#include "game_log_manager.h"
#include "log_struct.h"
#include "symphony/common/convert.h"
#include "symphony/common/func.h"
#include "symphony/proto/msg_account.pb.h"
// #include "stdafx.h"

CGameLogManager::CGameLogManager() {}

CGameLogManager::~CGameLogManager() {}

CGameLogManager* CGameLogManager::GetInstancePtr() {
    static CGameLogManager _LogManager;

    return &_LogManager;
}

bool CGameLogManager::LogAccountCreate(uint64_t uAccountID,
                                       std::string strAccountName,
                                       const symphony::proto::AccountLog& Log) {
    Log_AccountCreate log;
    log.m_uAccountID = uAccountID;
    log.m_nChannel = Log.channel();
    log.m_dwIpAddr = Log.ipaddr();
    log.m_uOpTime = CommonFunc::GetCurrTime();
    log.m_dwVersion = CommonConvert::VersionToInt(Log.version());
    CommonConvert::StrCopy(log.m_szImei, Log.imei().c_str(),
                           sizeof(log.m_szImei));
    CommonConvert::StrCopy(log.m_szModel, Log.imodel().c_str(),
                           sizeof(log.m_szModel));
    CommonConvert::StrCopy(log.m_szIdfa, Log.idfa().c_str(),
                           sizeof(log.m_szIdfa));
    CommonConvert::StrCopy(log.m_szUuid, Log.uuid().c_str(),
                           sizeof(log.m_szUuid));
    CommonConvert::StrCopy(log.m_szOpenID, strAccountName.c_str(),
                           sizeof(log.m_szOpenID));

    WriteGameLog(log);

    return true;
}

bool CGameLogManager::LogAccountLogin(uint64_t uAccountID,
                                      std::string strAccountName,
                                      const symphony::proto::AccountLog& Log) {
    Log_AccountLogin log;
    log.m_uAccountID = uAccountID;
    log.m_nChannel = Log.channel();
    log.m_dwIpAddr = Log.ipaddr();
    log.m_uOpTime = CommonFunc::GetCurrTime();
    log.m_dwVersion = CommonConvert::VersionToInt(Log.version());
    CommonConvert::StrCopy(log.m_szImei, Log.imei().c_str(),
                           sizeof(log.m_szImei));
    CommonConvert::StrCopy(log.m_szModel, Log.imodel().c_str(),
                           sizeof(log.m_szModel));
    CommonConvert::StrCopy(log.m_szIdfa, Log.idfa().c_str(),
                           sizeof(log.m_szIdfa));
    CommonConvert::StrCopy(log.m_szUuid, Log.uuid().c_str(),
                           sizeof(log.m_szUuid));
    CommonConvert::StrCopy(log.m_szOpenID, strAccountName.c_str(),
                           sizeof(log.m_szOpenID));

    WriteGameLog(log);

    return true;
}