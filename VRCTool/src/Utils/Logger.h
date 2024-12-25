#pragma once

#include "pch.h"

#include <format>

class Logger {
public:
    static void Log(const std::string& message);

    template<typename... Args>
    static void Log(const std::string& format, Args... args) {
        std::ostringstream oss;
        Format(oss, format, args...);
        Log(oss.str());
    }

private:
    template<typename... Args>
    static void Format(std::ostringstream& oss, const std::string& format, Args... args) {
        oss << std::vformat(format, std::make_format_args(args...));
    }
};