#ifndef __DATA_MODULE_POOL_H__
#define __DATA_MODULE_POOL_H__

#include "symphony/ds/activity_data.h"
#include "symphony/ds/bag_data.h"
#include "symphony/ds/copy_data.h"
#include "symphony/ds/counter_data.h"
#include "symphony/ds/equip_data.h"
#include "symphony/ds/friend_data.h"
#include "symphony/ds/gem_data.h"
#include "symphony/ds/global_data.h"
#include "symphony/ds/guild_data.h"
#include "symphony/ds/mail_data.h"
#include "symphony/ds/mount_data.h"
#include "symphony/ds/partner_data.h"
#include "symphony/ds/pay_data.h"
#include "symphony/ds/pet_data.h"
#include "symphony/ds/role_data.h"
#include "symphony/ds/seal_data.h"
#include "symphony/ds/skill_data.h"
#include "symphony/ds/task_data.h"
#include "symphony/symphony.h"

class CDataPool {
    CDataPool();
    ~CDataPool();

   public:
    static CDataPool* GetInstancePtr();

    BOOL InitDataPool();

    BOOL ReleaseDataPool();

    BOOL RestoreFromShareMemory();

    SharedMemoryBase* GetSharePool(EShareData nIndex);

   protected:
    std::vector<SharedMemoryBase*> m_vtDataObjectPools;
    UINT32 m_dwSharePageSize;
};

namespace DataPool {
template <class T>
T* CreateObject(EShareData nIndex, BOOL bNewBlock = TRUE) {
    SharedMemoryBase* pShareBase =
        CDataPool::GetInstancePtr()->GetSharePool(nIndex);

    T* pTmp = static_cast<T*>(pShareBase->NewObject(bNewBlock));

    if (pTmp == NULL) {
        CLog::GetInstancePtr()->LogError(
            "CreateObject Error, Reason:%s",
            CommonFunc::GetLastErrorStr(CommonFunc::GetLastError()).c_str());
    }

    return pTmp;
}
}  // namespace DataPool

#endif  //__DATA_MODULE_POOL_H__