#include "Logger.hpp"
#include "Core/Macros.hpp"

#include <cassert>

namespace EngineS {

static Logger* s_SharedInstance;

Logger* Logger::Instance() {
    if (!s_SharedInstance) {
        s_SharedInstance = new (std::nothrow) Logger;
        assert(s_SharedInstance != nullptr);
    }
    return s_SharedInstance;
}

Logger::Logger() :
#ifdef ES_DEBUG
    _level(LogLevel::Debug)
#else
    _level(LogLevel::Info)
#endif
{
}

std::string Logger::GetPrefix(LogLevel level, std::source_location location) {
    auto getFileName = [](std::source_location location) {
        const char* fullName  = location.file_name();
        const char* lastSlash = strrchr(fullName, '/') ? strrchr(fullName, '/') : strrchr(fullName, '\\');
        const char* filename  = lastSlash ? lastSlash + 1 : fullName;
        return filename;
    };
    using namespace fmt::literals;
    return fmt::format(
        "[{level}] [{file}:{line}]",
        "level"_a = logLevelStr[static_cast<int>(level)],
        "file"_a  = getFileName(location),
        "line"_a  = location.line()
    );
}

void Logger::Log(LogLevel level, std::string message, std::source_location location) {
    if (_level > level)
        return;
    std::string fullMessage = fmt::format("{} {}", GetPrefix(level, location), message);

    fmt::print("{}\n", fullMessage);

    if (_logFile.is_open()) {
        fmt::print(_logFile, "{}\n", fullMessage);
    }
}

void Logger::Open(const std::filesystem::path& filePath) {
    _logFile.open(filePath);
    if (_logFile.fail()) {
        Logger::Error("Failed to create log file {}", filePath.string());
    } else {
        Logger::Info("Opened log file {}", filePath.string());
    }
}

void Logger::Close() {
    _logFile.close();
}

} // namespace EngineS