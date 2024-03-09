#ifndef __GAME_LOG_MANAGER_H__
#define __GAME_LOG_MANAGER_H__

#include <string>
#include "symphony/proto/msg_account.pb.h"
#include "symphony/proto/msg_id.pb.h"
class CGameLogManager {
   public:
    CGameLogManager();
    ~CGameLogManager();

   public:
    static CGameLogManager* GetInstancePtr();

    template <typename T>
    bool WriteGameLog(T& Data) {
        // ERROR_RETURN_FALSE(CGameService::GetInstancePtr()->GetLogSvrConnID()
        // >
        //                    0);

        // ServiceBase::GetInstancePtr()->SendMsgRawData(
        //     CGameService::GetInstancePtr()->GetLogSvrConnID(),
        //     symphony::proto::MSG_LOG_DATA_NTF, 0, 0, (const char*)&Data,
        //     sizeof(T));

        return true;
    }

   public:
    bool LogAccountCreate(uint64_t uAccountID,
                          std::string strAccountName,
                          const symphony::proto::AccountLog& Log);
    bool LogAccountLogin(uint64_t uAccountID,
                         std::string strAccountName,
                         const symphony::proto::AccountLog& Log);
};

#endif  //__GAME_LOG_MANAGER_H__