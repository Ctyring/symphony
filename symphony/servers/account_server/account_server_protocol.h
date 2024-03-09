#pragma once
namespace symphony {
namespace as {
enum class ASCommand {
    LOG_TYPE_NONE = 0x12000,
    TICK = 0x12001,                     // 心跳
    MSG_ACCOUNT_REG_REQ = 0x12002,      // 注册账号
    MSG_ACCOUNT_LOGIN_REQ = 0x12003,    // 登录
    MSG_SEAL_ACCOUNT_REQ = 0x12004,     // 封号
    MSG_SET_LAST_SERVER_NTY = 0x12005,  // 设置最后登录服务器
};
}
}  // namespace symphony