#pragma once

#include <stdio.h>

#include <string>

namespace PianoCore {

class Log {
public:
    template <typename... Args>
    static void Info(const std::string& formatString, Args&&... args) {
        printf("[Info]: ");
        printf(formatString.c_str(), std::forward<Args>(args)...);
        printf("\n");
    }

    template <typename... Args>
    static void Warning(const std::string& formatString, Args&&... args) {
        printf("[Warning]: ");
        printf(formatString.c_str(), std::forward<Args>(args)...);
        printf("\n");
    }

    template <typename... Args>
    static void Error(const std::string& formatString, Args&&... args) {
        printf("[Error]: ");
        printf(formatString.c_str(), std::forward<Args>(args)...);
        printf("\n");
    }
};

}  // namespace PianoCore

#define PIANOCORE_LOG_INFO(message, ...) \
    PianoCore::Log::Info(message, ##__VA_ARGS__)
#define PIANOCORE_LOG_WARNING(message, ...) \
    PianoCore::Log::Warning(message, ##__VA_ARGS__)
#define PIANOCORE_LOG_ERROR(message, ...) \
    PianoCore::Log::Error(message, ##__VA_ARGS__)
