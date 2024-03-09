#ifndef __COMMON_SOCKET__
#define __COMMON_SOCKET__
#include <sys/socket.h>
#include <string>
#define SOCKET_ERROR (-1)

namespace CommonSocket {
// 设置套接字为可重用状态
bool SetSocketReuseable(int hSocket);

// 设置套接字为非阻塞状态
bool SetSocketBlock(int hSocket, bool bBlock);

bool SetSocketNoDelay(int hSocket);

bool SetSocketKeepAlive(int hSocket,
                        int nKeepInterval,
                        int nKeepCount,
                        int nKeepIdle);

bool InitNetwork();

bool UninitNetwork();

int CreateSocket(int af = AF_INET, int type = SOCK_STREAM, int protocol = 0);

bool BindSocket(int hSocket, const struct sockaddr* pAddr, int nNamelen);

bool ListenSocket(int hSocket, int nBacklog);

bool ConnectSocket(int hSocket, const char* pAddr, short sPort);

int32_t GetSocketLastError();

bool IsSocketValid(int hSocket);

void ShutdownSend(int hSocket);

void ShutdownRecv(int hSocket);

void _ShutdownSocket(int hSocket);

void CloseSocket(int hSocket);

std::string GetLocalIP();

uint32_t IpAddrStrToInt(char* pszIpAddr);

uint32_t IpAddrStrToInt(const char* pszIpAddr);

std::string IpAddrIntToStr(uint32_t dwIpAddr);

bool SetSocketBuffSize(int hSocket, int32_t nRecvSize, int32_t nSendSize);

bool SetSocketTimeOut(int hSocket, int32_t nSendTime, int32_t nRecvTime);

std::string GetRemoteIP(int hSocket);

uint32_t HostToNet(int32_t nValue);

uint32_t NetToHost(int32_t nValue);

void IgnoreSignal();

std::string HttpGet(std::string strHost,
                    int32_t nPort,
                    std::string strPath,
                    std::string strContent);

#ifdef WIN32
bool ConnectSocketEx(int hSocket,
                     const char* pAddr,
                     short sPort,
                     LPOVERLAPPED lpOverlapped);

bool AcceptSocketEx(int hListenSocket,
                    int hAcceptSocket,
                    char* pBuff,
                    LPOVERLAPPED lpOverlapped);

bool GetSocketAddress(int hSocket,
                      char* pDataBuffer,
                      sockaddr_in*& pAddrClient,
                      sockaddr_in*& pAddrLocal);

bool DisconnectEx(int hSocket, LPOVERLAPPED lpOverlapped, bool bReuse);
#endif
}  // namespace CommonSocket

#endif /* __COMMON_SOCKET__*/