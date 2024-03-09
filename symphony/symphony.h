/**
 * @file symphony.h
 * @brief symphony头文件
 * @author cty
 * @email 564628276@qq.com
 * @date 2019-05-24
 * @copyright Copyright (c) cty All rights reserved
 */
#ifndef __SYMPHONY_SYMPHONY_H__
#define __SYMPHONY_SYMPHONY_H__

#include "address.h"
#include "application.h"
#include "bytearray.h"
#include "config.h"
#include "daemon.h"
#include "endian.h"
#include "env.h"
#include "fd_manager.h"
#include "fiber.h"
#include "hook.h"
#include "iomanager.h"
#include "library.h"
#include "log.h"
#include "macro.h"
#include "module.h"
#include "mutex.h"
#include "noncopyable.h"
// #include "protocol.h"
#include "scheduler.h"
#include "singleton.h"
#include "socket.h"
#include "stream.h"
#include "tcp_server.h"
#include "thread.h"
#include "timer.h"
#include "uri.h"
#include "util.h"
#include "worker.h"

// #include "db/db.h"
// #include "db/mysql.h"
#include "db/sqlite3.h"

#include "ds/cache_status.h"
#include "ds/lru_cache.h"
#include "ds/timed_cache.h"
#include "ds/timed_lru_cache.h"

#include "email/email.h"
#include "email/smtp.h"

#include "http/http.h"
#include "http/http11_common.h"
#include "http/http11_parser.h"
#include "http/http_connection.h"
#include "http/http_parser.h"
#include "http/http_server.h"
#include "http/http_session.h"
#include "http/httpclient_parser.h"
#include "http/servlet.h"
// #include "http/session_data.h"
#include "http/ws_connection.h"
#include "http/ws_server.h"
#include "http/ws_servlet.h"
#include "http/ws_session.h"

#include "rock/rock_protocol.h"
#include "rock/rock_server.h"
#include "rock/rock_stream.h"

#include "streams/async_socket_stream.h"
#include "streams/load_balance.h"
#include "streams/socket_stream.h"
#include "streams/zlib_stream.h"

#include "util/crypto_util.h"
#include "util/hash_util.h"
#include "util/json_util.h"

#include "symphony/common/convert.h"
#include "symphony/common/func.h"
#include "symphony/common/socket.h"
#include "symphony/common/time.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

#define WSAEWOULDBLOCK EWOULDBLOCK
#define WSAEINPROGRESS EINPROGRESS
#define WSAEALREADY EALREADY
#define WSAENOTSOCK ENOTSOCK
#define WSAEDESTADDRREQ EDESTADDRREQ
#define WSAEMSGSIZE EMSGSIZE
#define WSAEPROTOTYPE EPROTOTYPE
#define WSAENOPROTOOPT ENOPROTOOPT
#define WSAEPROTONOSUPPORT EPROTONOSUPPORT
#define WSAESOCKTNOSUPPORT ESOCKTNOSUPPORT
#define WSAEOPNOTSUPP EOPNOTSUPP
#define WSAEPFNOSUPPORT EPFNOSUPPORT
#define WSAEAFNOSUPPORT EAFNOSUPPORT
#define WSAEADDRINUSE EADDRINUSE
#define WSAEADDRNOTAVAIL EADDRNOTAVAIL
#define WSAENETDOWN ENETDOWN
#define WSAENETUNREACH ENETUNREACH
#define WSAENETRESET ENETRESET
#define WSAECONNABORTED ECONNABORTED
#define WSAECONNRESET ECONNRESET
#define WSAENOBUFS ENOBUFS
#define WSAEISCONN EISCONN
#define WSAENOTCONN ENOTCONN
#define WSAESHUTDOWN ESHUTDOWN
#define WSAETOOMANYREFS ETOOMANYREFS
#define WSAETIMEDOUT ETIMEDOUT
#define WSAECONNREFUSED ECONNREFUSED
#define WSAELOOP ELOOP
#define WSAENAMETOOLONG ENAMETOOLONG
#define WSAEHOSTDOWN EHOSTDOWN
#define WSAEHOSTUNREACH EHOSTUNREACH
#define WSAENOTEMPTY ENOTEMPTY
#define WSAEPROCLIM EPROCLIM
#define WSAEUSERS EUSERS
#define WSAEDQUOT EDQUOT
#define WSAESTALE ESTALE
#define WSAEREMOTE EREMOTE

typedef char INT8;
typedef unsigned char UINT8;
typedef short INT16;
typedef unsigned short UINT16;
typedef int INT32;
typedef unsigned int UINT32;
typedef int BOOL;
typedef void VOID;
typedef float FLOAT;
typedef double DOUBLE;
typedef long long INT64;
typedef unsigned long long UINT64;
typedef unsigned char BYTE;
typedef char CHAR;
typedef int SOCKET;
typedef int HANDLE;

#define INVALID_SOCKET (-1)
#define TRUE 1
#define FALSE 0
#define INVALID_HANDLE_VALUE 0
#endif

#ifdef OS_PLATFORM_WINDOWS
#ifdef SERVER_ENGINE
#define EngineClass _declspec(dllexport)
#else
#define EngineClass _declspec(dllimport)
#endif
#else
#define EngineClass
#endif