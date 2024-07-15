//
#include "Logger.h"

Logger::Logger(const std::string& filename) : filename(filename), file(filename, std::ios_base::app) {
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open log file.");
    }
}

Logger::~Logger() {
    if (file.is_open()) {
        file.close();
    }
}

void Logger::writeLog(const std::string& message) {
    std::unique_lock<std::shared_mutex> lock(shared_mutex);

    if (!file.is_open()) {
        file.open(filename, std::ios_base::app);
    }
    file << message << std::endl;
    file.flush();
}

std::string Logger::readLog() const {
    std::shared_lock<std::shared_mutex> lock(shared_mutex);
    std::ifstream logFile(filename);

    if (!logFile.is_open()) {
        throw std::runtime_error("Failed to open log file.");
    }

    std::string lastLine;
    logFile.seekg(0, std::ios::end);
    if (logFile.tellg() == 0) {
        return "";
    }

    char ch;
    logFile.seekg(-1, std::ios::end);
    logFile.get(ch);
    if (ch == '\n') {
        logFile.seekg(-1, std::ios::cur);
    }

    while (logFile.tellg() > 0) {
        logFile.seekg(-1, std::ios::cur);
        logFile.get(ch);
        if (ch == '\n') {
            break;
        }
        logFile.seekg(-1, std::ios::cur);
    }

    std::getline(logFile, lastLine);
    return lastLine;
}
