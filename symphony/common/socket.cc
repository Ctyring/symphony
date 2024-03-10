#include "socket.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include "fcntl.h"
#include "symphony/symphony.h"

bool CommonSocket::SetSocketReuseable(int hSocket) {
    int nReuse = 1;

    if (0 != setsockopt(hSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&nReuse,
                        sizeof(int))) {
        return false;
    }

    return true;
}

// 设置套接字阻塞状态
bool CommonSocket::SetSocketBlock(int hSocket, bool bBlock) {
#ifdef WIN32
    u_long iMode = bBlock ? 0 : 1;
    ioctlsocket(hSocket, FIONBIO, &iMode);
#else
    int flags = fcntl(hSocket, F_GETFL, 0);
    fcntl(hSocket, F_SETFL,
          bBlock ? (flags & (~O_NONBLOCK)) : (flags | O_NONBLOCK));
#endif

    return true;
}

bool CommonSocket::SetSocketBuffSize(int hSocket,
                                     int32_t nRecvSize,
                                     int32_t nSendSize) {
    if (nRecvSize > 0) {
        if (0 != setsockopt(hSocket, SOL_SOCKET, SO_RCVBUF, (char*)&nRecvSize,
                            sizeof(int32_t))) {
            return false;
        }
    }

    if (nSendSize > 0) {
        if (0 != setsockopt(hSocket, SOL_SOCKET, SO_SNDBUF, (char*)&nSendSize,
                            sizeof(int32_t))) {
            return false;
        }
    }

    return true;
}

bool CommonSocket::SetSocketTimeOut(int hSocket,
                                    int32_t nSendTime,
                                    int32_t nRecvTime) {
    if (nSendTime > 0) {
#ifdef WIN32
        if (0 != setsockopt(hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&nSendTime,
                            sizeof(int32_t))) {
            return false;
        }
#else
        struct timeval timeout;
        timeout.tv_sec = nSendTime;
        timeout.tv_usec = 0;
        if (0 != setsockopt(hSocket, SOL_SOCKET, SO_SNDTIMEO, &timeout,
                            sizeof(timeout))) {
            return false;
        }
#endif
    }

    if (nRecvTime > 0) {
#ifdef WIN32
        if (0 != setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&nRecvTime,
                            sizeof(int32_t))) {
            return false;
        }
#else
        struct timeval timeout;
        timeout.tv_sec = nRecvTime;
        timeout.tv_usec = 0;
        if (0 != setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout,
                            sizeof(timeout))) {
            return false;
        }
#endif
    }
    return true;
}

std::string CommonSocket::GetRemoteIP(int hSocket) {
    sockaddr_in _sockAddr;

    socklen_t _sockAddr_len = sizeof(_sockAddr);

    memset(&_sockAddr, 0, sizeof(_sockAddr));

    getpeername(hSocket, (sockaddr*)&_sockAddr, &_sockAddr_len);

    char szIpBuffer[100] = {0};

    inet_ntop(AF_INET, &_sockAddr.sin_addr, szIpBuffer, 100);

    return std::string(szIpBuffer);
}

uint32_t CommonSocket::HostToNet(int32_t nValue) {
    return htonl(nValue);
}

uint32_t CommonSocket::NetToHost(int32_t nValue) {
    return ntohl(nValue);
}

void CommonSocket::IgnoreSignal() {
#ifdef WIN32

#else
    struct sigaction sig;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &sig, 0);
    sigaction(SIGHUP, &sig, 0);
#endif
}

std::string CommonSocket::HttpGet(std::string strHost,
                                  int32_t nPort,
                                  std::string strPath,
                                  std::string strContent) {
    char szReq[20480] = {0};
    sprintf(szReq,
            "GET %s?%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: Mozilla/5.0 "
            "(Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 "
            "Firefox/3.6.3\r\n\r\n",
            strPath.c_str(), strContent.c_str(), strHost.c_str());

    int hSocket = CreateSocket();
    if (hSocket == INVALID_SOCKET) {
        return "Create Socket Failed!";
    }

    if (!SetSocketTimeOut(hSocket, 2, 5)) {
        CloseSocket(hSocket);
        return "Set Socket Time out Value Failed!";
    }

    if (!ConnectSocket(hSocket, strHost.c_str(), nPort)) {
        CloseSocket(hSocket);
        return "Connect Socket Failed!";
    }

    send(hSocket, szReq, strlen(szReq), 0);

    char szRecvBuff[10240] = {0};

    // 循环接收
    int32_t nDataLen = 0;
    int32_t nBytes;
    while (
        (nBytes = recv(hSocket, szRecvBuff + nDataLen, 10240 - nDataLen, 0))) {
        nDataLen += nBytes;
        if (nDataLen >= 10240) {
            break;
        }
    }

    CloseSocket(hSocket);

    std::string strRet = szRecvBuff;

    size_t nPos = strRet.find("\r\n\r\n");
    if (nPos == std::string::npos) {
        return "";
    }

    return strRet.substr(nPos + 4);
}

bool CommonSocket::SetSocketNoDelay(int hSocket) {
    int bOn = 1;

    if (0 != setsockopt(hSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&bOn,
                        sizeof(bOn))) {
        return FALSE;
    }

    return TRUE;
}

bool CommonSocket::InitNetwork() {
#if WIN32
    WSADATA wsaData;
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        return FALSE;
    }
#else
    IgnoreSignal();
#endif
    return TRUE;
}

bool CommonSocket::UninitNetwork() {
#if WIN32
    return (0 == WSACleanup());
#endif
    return TRUE;
}

void CommonSocket::CloseSocket(int hSocket) {
#ifdef WIN32
    closesocket(hSocket);
#else
    close(hSocket);
#endif

    hSocket = INVALID_SOCKET;

    return;
}

std::string CommonSocket::GetLocalIP() {
    char hostname[256] = {0};
    int ret = gethostname(hostname, sizeof(hostname));
    if (ret == SOCKET_ERROR) {
        return "";
    }

    hostent* host = gethostbyname(hostname);
    if (host == NULL) {
        return "";
    }

    char szIp[256] = {0};
    strcpy(szIp, inet_ntoa(*(in_addr*)*host->h_addr_list));
    return std::string(szIp);
}

void CommonSocket::ShutdownSend(int hSocket) {
    shutdown(hSocket, 1);
}

void CommonSocket::ShutdownRecv(int hSocket) {
    shutdown(hSocket, 0);
}

void CommonSocket::_ShutdownSocket(int hSocket) {
#ifdef WIN32
    return CommonSocket::CloseSocket(hSocket);
#else
    return CommonSocket::ShutdownSend(hSocket);
#endif
}

int CommonSocket::CreateSocket(int af, int type, int protocol) {
#ifdef WIN32
    return WSASocket(af, type, protocol, NULL, 0, WSA_FLAG_OVERLAPPED);
#else
    return socket(af, type | SOCK_CLOEXEC, protocol);
#endif
}

bool CommonSocket::BindSocket(int hSocket,
                              const struct sockaddr* pAddr,
                              int nNamelen) {
    if (0 != bind(hSocket, pAddr, nNamelen)) {
        return FALSE;
    }

    return TRUE;
}

bool CommonSocket::ListenSocket(int hSocket, int nBacklog) {
    if (0 != listen(hSocket, nBacklog)) {
        return FALSE;
    }

    return TRUE;
}

bool CommonSocket::ConnectSocket(int hSocket, const char* pAddr, short sPort) {
    if (pAddr == NULL) {
        return FALSE;
    }

    sockaddr_in svrAddr;
    memset(&svrAddr, 0, sizeof(svrAddr));
    svrAddr.sin_family = AF_INET;
    svrAddr.sin_port = htons(sPort);
    inet_pton(AF_INET, pAddr, &svrAddr.sin_addr);

    if (0 == connect(hSocket, (const sockaddr*)&svrAddr, sizeof(svrAddr))) {
        return TRUE;
    }

    int nError = CommonSocket::GetSocketLastError();
    if ((WSAEWOULDBLOCK == nError) || (WSAEINPROGRESS == nError)) {
        return TRUE;
    }

    return FALSE;
}

int32_t CommonSocket::GetSocketLastError() {
#ifdef WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
}

bool CommonSocket::IsSocketValid(int hSocket) {
    if ((hSocket == 0) || (hSocket == INVALID_SOCKET)) {
        return FALSE;
    }

    return TRUE;
}

uint32_t CommonSocket::IpAddrStrToInt(char* pszIpAddr) {
    sockaddr_in SvrAddr;

    if (inet_pton(AF_INET, pszIpAddr, &SvrAddr.sin_addr) <= 0) {
        return 0;
    }

    return SvrAddr.sin_addr.s_addr;
}

uint32_t CommonSocket::IpAddrStrToInt(const char* pszIpAddr) {
    sockaddr_in SvrAddr;

    if (inet_pton(AF_INET, pszIpAddr, &SvrAddr.sin_addr) <= 0) {
        return 0;
    }

    return SvrAddr.sin_addr.s_addr;
}

#ifdef WIN32

bool CommonSocket::AcceptSocketEx(int hListenSocket,
                                  int hAcceptSocket,
                                  char* pBuff,
                                  LPOVERLAPPED lpOverlapped) {
    static LPFN_ACCEPTEX lpfnAcceptEx = NULL;

    if (pBuff == NULL) {
        return FALSE;
    }

    DWORD nBytes = 0;
    if (lpfnAcceptEx == NULL) {
        GUID GuidAcceptEx = WSAID_ACCEPTEX;
        if (SOCKET_ERROR ==
            WSAIoctl(hListenSocket, SIO_GET_EXTENSION_FUNCTION_POINTER,
                     &GuidAcceptEx, sizeof(GuidAcceptEx), &lpfnAcceptEx,
                     sizeof(lpfnAcceptEx), &nBytes, NULL, NULL)) {
            return FALSE;
        }
    }

    nBytes = 0;

    if (!lpfnAcceptEx(hListenSocket, hAcceptSocket, pBuff, 0,
                      sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16,
                      &nBytes, lpOverlapped)) {
        if (ERROR_IO_PENDING != CommonSocket::GetSocketLastError()) {
            return FALSE;
        }
    }

    return TRUE;
}

bool CommonSocket::GetSocketAddress(int hSocket,
                                    char* pDataBuffer,
                                    sockaddr_in*& pAddrClient,
                                    sockaddr_in*& pAddrLocal) {
    static LPFN_GETACCEPTEXSOCKADDRS lpfnGetAcceptExSockaddrs = NULL;
    if (lpfnGetAcceptExSockaddrs == NULL) {
        DWORD nBytes;
        GUID GuidAddressEx = WSAID_GETACCEPTEXSOCKADDRS;
        if (SOCKET_ERROR ==
            WSAIoctl(hSocket, SIO_GET_EXTENSION_FUNCTION_POINTER,
                     &GuidAddressEx, sizeof(GuidAddressEx),
                     &lpfnGetAcceptExSockaddrs,
                     sizeof(lpfnGetAcceptExSockaddrs), &nBytes, NULL, NULL)) {
            return FALSE;
        }
    }

    sockaddr_in *pClient = NULL, *pLocal = NULL;
    int nAddrLen = sizeof(sockaddr_in);

    lpfnGetAcceptExSockaddrs(pDataBuffer, 0, sizeof(sockaddr_in) + 16,
                             sizeof(sockaddr_in) + 16, (LPSOCKADDR*)&pLocal,
                             &nAddrLen, (LPSOCKADDR*)&pClient, &nAddrLen);

    pAddrClient = pClient;
    pAddrLocal = pLocal;

    return TRUE;
}

bool CommonSocket::DisconnectEx(int hSocket,
                                LPOVERLAPPED lpOverlapped,
                                bool bReuse) {
    static LPFN_DISCONNECTEX lpfnDisconnectEx = NULL;
    if (lpfnDisconnectEx == NULL) {
        DWORD nBytes;
        GUID GuidAddressEx = WSAID_DISCONNECTEX;
        if (SOCKET_ERROR ==
            WSAIoctl(hSocket, SIO_GET_EXTENSION_FUNCTION_POINTER,
                     &GuidAddressEx, sizeof(GuidAddressEx), &lpfnDisconnectEx,
                     sizeof(lpfnDisconnectEx), &nBytes, NULL, NULL)) {
            return FALSE;
        }
    }

    lpfnDisconnectEx(hSocket, lpOverlapped, bReuse ? TF_REUSE_SOCKET : 0, 0);

    return TRUE;
}

bool CommonSocket::ConnectSocketEx(int hSocket,
                                   const char* pAddr,
                                   short sPort,
                                   LPOVERLAPPED lpOverlapped) {
    static LPFN_CONNECTEX lpfnConnectEx = NULL;

    if (lpfnConnectEx == NULL) {
        DWORD nBytes;
        GUID GuidConnectEx = WSAID_CONNECTEX;
        if (SOCKET_ERROR ==
            WSAIoctl(hSocket, SIO_GET_EXTENSION_FUNCTION_POINTER,
                     &GuidConnectEx, sizeof(GuidConnectEx), &lpfnConnectEx,
                     sizeof(lpfnConnectEx), &nBytes, NULL, NULL)) {
            return FALSE;
        }
    }

    sockaddr_in svrAddr;

    svrAddr.sin_family = AF_INET;

    svrAddr.sin_port = htons(0);

    svrAddr.sin_addr.s_addr = INADDR_ANY;

    CommonSocket::BindSocket(hSocket, (const sockaddr*)&svrAddr,
                             sizeof(sockaddr_in));

    svrAddr.sin_port = htons(sPort);

    inet_pton(AF_INET, pAddr, &svrAddr.sin_addr);

    if (!lpfnConnectEx(hSocket, (const sockaddr*)&svrAddr, sizeof(sockaddr_in),
                       NULL, NULL, NULL, lpOverlapped)) {
        if (ERROR_IO_PENDING != CommonSocket::GetSocketLastError()) {
            return FALSE;
        }
    }

    return TRUE;
}
#endif

std::string CommonSocket::IpAddrIntToStr(uint32_t dwIpAddr) {
    in_addr Addr;

    Addr.s_addr = dwIpAddr;

    char szIpBuffer[100] = {0};
    inet_ntop(AF_INET, &Addr, szIpBuffer, 100);
    return std::string(szIpBuffer);
}

bool CommonSocket::SetSocketKeepAlive(int hSocket,
                                      int nKeepInterval,
                                      int nKeepCount,
                                      int nKeepIdle) {
#ifdef WIN32
    tcp_keepalive alive_in = {0}, alive_out = {0};
    alive_in.keepalivetime = nKeepIdle;  // 开始首次KeepAlive探测前的TCP空闭时间
    alive_in.keepaliveinterval =
        nKeepInterval;  // 两次KeepAlive探测间的时间间隔
    alive_in.onoff = TRUE;
    unsigned long ulBytesReturn = 0;
    int nRet =
        WSAIoctl(hSocket, SIO_KEEPALIVE_VALS, &alive_in, sizeof(alive_in),
                 &alive_out, sizeof(alive_out), &ulBytesReturn, NULL, NULL);

    if (nRet == SOCKET_ERROR) {
        return FALSE;
    }
#else
    int32_t nKeepAlive = 1;
    setsockopt(hSocket, SOL_SOCKET, SO_KEEPALIVE, (void*)&nKeepAlive,
               sizeof(nKeepAlive));
    setsockopt(hSocket, SOL_TCP, TCP_KEEPIDLE, (void*)&nKeepIdle,
               sizeof(nKeepIdle));
    setsockopt(hSocket, SOL_TCP, TCP_KEEPINTVL, (void*)&nKeepInterval,
               sizeof(nKeepInterval));
    setsockopt(hSocket, SOL_TCP, TCP_KEEPCNT, (void*)&nKeepCount,
               sizeof(nKeepCount));
#endif

    return TRUE;
}