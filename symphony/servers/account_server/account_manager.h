#pragma once
#include <stdint.h>
#include <map>
#include <queue>
#include <string>
#include <thread>
#include "symphony/ds/avl_tree.h"

namespace symphony {
namespace as {
struct CAccountObject {
    uint64_t m_ID = 0;
    std::string m_strName;
    std::string m_strPassword;
    int32_t m_nLastSvrID[2] = {0};
    int32_t m_nChannel = 0;      // 渠道ID
    uint64_t m_uSealTime = 0;    // 封禁结束时间
    uint64_t m_uCreateTime = 0;  // 创建时间
    int32_t m_nLoginCount = 0;
};

class CAccountObjectMgr : public AVLTree<uint64_t, CAccountObject> {
   public:
    CAccountObjectMgr();
    ~CAccountObjectMgr();

   public:
    bool LoadCacheAccount();

   public:
    CAccountObject* GetAccountObjectByID(uint64_t m_u64AccountID);

    CAccountObject* CreateAccountObject(const std::string& strName,
                                        const std::string& strPwd,
                                        int32_t nChannel);

    bool ReleaseAccountObject(uint64_t m_u64AccountID);

    bool SealAccount(uint64_t& uAccountID,
                     const std::string& strName,
                     int32_t nChannel,
                     bool bSeal,
                     int32_t nSealTime,
                     int32_t& nLastSvrID);

    bool SetLastServer(uint64_t uAccountID, int32_t ServerID);

    CAccountObject* AddAccountObject(uint64_t uAccountID,
                                     const char* pStrName,
                                     int32_t nChannel);

    CAccountObject* GetAccountObject(const std::string& name, int32_t nChannel);

    bool SaveAccountThread();

    bool Init();

    bool Uninit();

    bool IsRun();

    bool CheckAccountName(const std::string& strName, bool bFromChannel);

   public:
    std::map<std::string, CAccountObject*> m_mapNameObj;

    std::queue<CAccountObject*> m_ArrChangedAccount;

    bool m_IsRun;

    std::thread* m_pThread;

    uint64_t m_u64MaxID;

    bool m_bCrossChannel;  // 是否区分渠道
};
}  // namespace as
}  // namespace symphony
