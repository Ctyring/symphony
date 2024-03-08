#pragma once
namespace symphony {
namespace db {
enum class LSCommand {
    LOG_TYPE_NONE = 0x11000,
    TICK = 0x11001,                       // 心跳
    MSG_ROLE_LIST_REQ = 0x11002,          // 请求角色列表
    MSG_ROLE_LOGIN_REQ = 0x11003,         // 请求登录
    MSG_ROLE_DELETE_REQ = 0x11004,        // 请求删除角色
    MSG_DB_EXE_SQL_REQ = 0x11005,         // 请求执行sql
    MSG_LOGIC_REGTO_DBSVR_REQ = 0x11006,  // 注册到db server
};
}
}  // namespace symphony