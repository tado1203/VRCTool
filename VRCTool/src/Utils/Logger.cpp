#include "pch.h"

#include "logger.h"

void Logger::Log(const std::string& message) {
    std::ofstream logFile("VRCTool/log.txt", std::ios::app); // append mode

    std::cout << message << '\n';

    if (logFile.is_open()) {
        logFile << message << '\n';
    } else {
        std::cerr << "Failed to open log.txt for writing." << '\n';
    }
}