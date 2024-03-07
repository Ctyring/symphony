#pragma once
namespace symphony {
namespace ls {

enum class LSCommand {
    LOG_TYPE_NONE = 0x10000,
    TICK = 0x10001,            // 心跳
    ACCOUNT_CREATE = 0x10002,  // 创建账号
    ACCOUNT_LOGIN = 0x10003,   // 登录
    ROLE_CREATE = 0x10004,     // 创建角色
    ROLE_LOGIN = 0x10005,      // 登录角色
    ROLE_LOGOUT = 0x10006,     // 登出
    ROLE_EXP = 0x10007,        // 经验
    ROLE_DIAMOND = 0x10008,    // 钻石
    ROLE_GOLD = 0x10009,       // 金币
    ROLE_LEVEL = 0x1000A,      // 等级
    ROLE_CHAT = 0x1000B,       // 聊天
};
}
}  // namespace symphony