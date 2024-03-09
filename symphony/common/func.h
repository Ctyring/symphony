#ifndef __COMMON_FUNCTION__
#define __COMMON_FUNCTION__
#include <stdint.h>
#include <string>
#include <vector>
#define GET_BIT(X, Y) (((X) >> (Y - 1)) & 1)
#define SET_BIT(X, Y) ((X) |= (1 << (Y - 1)))
#define CLR_BIT(X, Y) ((X) &= (~(1 << Y - 1)))

namespace CommonFunc {
int32_t GetProcessorNum();

std::string GetCurrentWorkDir();

bool SetCurrentWorkDir(std::string strPath);

std::string GetCurrentExeDir();

bool CreateDir(std::string& strDir);

bool GetDirFiles(const char* pszDir,
                 char* pszFileType,
                 std::vector<std::string>& vtFileList,
                 bool bRecursion);

bool GetSubDirNames(const char* pszDir,
                    const char* pszBegin,
                    std::vector<std::string>& vtDirList,
                    bool bRecursion);

int32_t GetCurThreadID();

int32_t GetCurProcessID();

void Sleep(int32_t nMilliseconds);

int32_t GetFreePhysMemory();

int32_t GetRandNum(int32_t nType);

int32_t GetLastError();

std::string GetLastErrorStr(int32_t nError);

// HANDLE       CreateShareMemory(std::string strName, int32_t nSize);
//
// HANDLE       OpenShareMemory(std::string strName);

int CreateShareMemory(int32_t nModuleID, int32_t nPage, int32_t nSize);

int OpenShareMemory(int32_t nModuleID, int32_t nPage);

char* GetShareMemory(int hShm);

bool ReleaseShareMemory(char* pMem);

bool CloseShareMemory(int hShm);

bool KillProcess(int32_t nPid);

bool IsProcessExist(int32_t nPid);

int32_t GetProcessID(const char* pszProcName);

bool StartProcess(const char* pszProcName,
                  const char* pszCommandLine = NULL,
                  const char* pszWorkPath = NULL);

bool IsAlreadyRun(std::string strSignName);

bool PrintColorText(char* pSzText, int32_t nColor);

bool GetBitValue(uint64_t nValue, int32_t nPos);

bool SetBitValue(uint64_t& nValue, int32_t nPos, bool bValue);
}  // namespace CommonFunc

#endif /* __COMMON_FUNCTION__*/