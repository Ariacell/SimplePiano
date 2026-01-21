#pragma once

#include "log.h"

#include <filesystem>

#define PIANOCORE_INTERNAL_ASSERT_CHECK(condition, message, ...) \
    {                                                            \
        if (!(condition)) {                                      \
            PIANOCORE_LOG_ERROR(message, ##__VA_ARGS__);         \
        }                                                        \
    }

#define PIANOCORE_ASSERT_ARGS(condition, message, ...) \
    PIANOCORE_INTERNAL_ASSERT_CHECK(condition, message, ##__VA_ARGS__)
#define PIANOCORE_ASSERT_NO_ARGS(condition)                              \
    PIANOCORE_INTERNAL_ASSERT_CHECK(                                     \
        condition, "Assertion failed: %s, file %s, line %s", #condition, \
        std::filesystem::path(__FILE__).string().c_str(),                \
        std::to_string(__LINE__).c_str())

#define PIANOCORE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro

#define PIANOCORE_ASSERT(...)                                         \
    PIANOCORE_INTERNAL_ASSERT_GET_MACRO_NAME(                         \
        __VA_ARGS__, PIANOCORE_ASSERT_ARGS, PIANOCORE_ASSERT_NO_ARGS) \
    (__VA_ARGS__)
