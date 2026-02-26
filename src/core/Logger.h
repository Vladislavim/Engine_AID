#pragma once

#include <fstream>
#include <mutex>
#include <string>

enum class LogLevel {
    Info,
    Warn,
    Error
};

class Logger {
public:
    static Logger& instance();

    bool initialize(const std::string& filePath);
    void shutdown();
    void log(LogLevel level, const std::string& message);

    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);

private:
    Logger() = default;
    std::string timestamp() const;
    const char* levelText(LogLevel level) const;

    std::ofstream file_;
    std::mutex mutex_;
    bool ready_{false};
};
