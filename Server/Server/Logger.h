#pragma once
#include <iostream>
#include <fstream>
#include <shared_mutex>
#include <mutex>
#include <string>


class Logger {
private:
    std::ofstream file;
    mutable std::shared_mutex shared_mutex;
    std::string filename;  

public:
    Logger(const std::string& filename);
    ~Logger();
    void writeLog(const std::string& message);
    std::string readLog() const;
};