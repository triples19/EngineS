#pragma once

#include "Core/Object.hpp"

#include "fmt/color.h"
#include "fmt/core.h"
#include "fmt/ostream.h"
#include <filesystem>
#include <fstream>

#ifdef REFL_COMPILER
// Clang does not fully support consteval of c++20.
// This is a workaround for ReflCompiler to run on this file.
#    define __cpp_consteval
#endif
#include <source_location>

namespace EngineS {

enum class LogLevel : u32 { Trace, Debug, Info, Error, None };

class Logger : public Object {
    ES_OBJECT
    static constexpr const char*     logLevelStr[]   = {"trace", "debug", "info", "error", nullptr};
    static constexpr fmt::text_style logLevelStyle[] = {
        fmt::fg(fmt::terminal_color::white),                     // trace
        fmt::fg(fmt::terminal_color::cyan),                      // debug
        fmt::fg(fmt::terminal_color::green),                     // info
        fmt::fg(fmt::terminal_color::red) | fmt::emphasis::bold, // error
        fmt::fg(fmt::terminal_color::white)};

  public:
    Logger();

    static Logger* Instance();

    static std::string GetPrefix(LogLevel level, std::source_location location);

    void Log(LogLevel level, std::string message, std::source_location location = std::source_location::current());

    void Open(const std::filesystem::path& filePath);
    void Close();

    void     SetLevel(LogLevel level) { _level = level; }
    LogLevel GetLevel() const { return _level; }

    template<class... Ts>
    struct Trace {
        Trace(
            fmt::format_string<Ts...> format,
            Ts&&... args,
            std::source_location location = std::source_location::current()
        ) {
            Instance()->Log(LogLevel::Trace, fmt::format(format, std::forward<Ts>(args)...), location);
        }
    };
    template<class... Ts>
    Trace(fmt::format_string<Ts...>, Ts&&...) -> Trace<Ts...>;

    template<class... Ts>
    struct Debug {
        Debug(
            fmt::format_string<Ts...> format,
            Ts&&... args,
            std::source_location location = std::source_location::current()
        ) {
            Instance()->Log(LogLevel::Debug, fmt::format(format, std::forward<Ts>(args)...), location);
        }
    };
    template<class... Ts>
    Debug(fmt::format_string<Ts...>, Ts&&...) -> Debug<Ts...>;

    template<class... Ts>
    struct Info {
        Info(
            fmt::format_string<Ts...> format,
            Ts&&... args,
            std::source_location location = std::source_location::current()
        ) {
            Instance()->Log(LogLevel::Info, fmt::format(format, std::forward<Ts>(args)...), location);
        }
    };
    template<class... Ts>
    Info(fmt::format_string<Ts...>, Ts&&...) -> Info<Ts...>;

    template<class... Ts>
    struct Error {
        Error(
            fmt::format_string<Ts...> format,
            Ts&&... args,
            const std::source_location& location = std::source_location::current()
        ) {
            Instance()->Log(LogLevel::Error, fmt::format(format, std::forward<Ts>(args)...), location);
        }
    };
    template<class... Ts>
    Error(fmt::format_string<Ts...>, Ts&&...) -> Error<Ts...>;

  private:
    LogLevel      _level;
    std::ofstream _logFile;
};

} // namespace EngineS
