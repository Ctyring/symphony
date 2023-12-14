/**
 * @file macro.h
 * @brief 常用宏的封装
 * @author cty
 * @email 564628276@qq.com
 * @date 2019-06-01
 * @copyright Copyright (c) cty All rights reserved
 */
#ifndef __SYMPHONY_MACRO_H__
#define __SYMPHONY_MACRO_H__

#include <assert.h>
#include <string.h>
#include "log.h"
#include "util.h"

#if defined __GNUC__ || defined __llvm__
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率成立
#define SYMPHONY_LIKELY(x) __builtin_expect(!!(x), 1)
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率不成立
#define SYMPHONY_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define SYMPHONY_LIKELY(x) (x)
#define SYMPHONY_UNLIKELY(x) (x)
#endif
/// 断言宏封装
#define SYMPHONY_ASSERT(x)                                  \
    if (SYMPHONY_UNLIKELY(!(x))) {                          \
        SYMPHONY_LOG_ERROR(SYMPHONY_LOG_ROOT())             \
            << "ASSERTION: " #x << "\nbacktrace:\n"         \
            << symphony::BacktraceToString(100, 2, "    "); \
        assert(x);                                          \
    }
/// 断言宏封装
#define SYMPHONY_ASSERT2(x, w)                              \
    if (SYMPHONY_UNLIKELY(!(x))) {                          \
        SYMPHONY_LOG_ERROR(SYMPHONY_LOG_ROOT())             \
            << "ASSERTION: " #x << "\n"                     \
            << w << "\nbacktrace:\n"                        \
            << symphony::BacktraceToString(100, 2, "    "); \
        assert(x);                                          \
    }
#endif