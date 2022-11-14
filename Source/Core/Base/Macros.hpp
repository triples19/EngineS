#pragma once

#include "Core/Logging/LoggingSystem.hpp"
#include "Function/Global/Global.hpp"

// Logging macros
#define FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG_PREFIX fmt::format("[{0}:{1}] {2} > ", FILENAME, __LINE__, __FUNCTION__)
#define LOG_DEBUG(...) LoggingSystem::Instance()->Debug(LOG_PREFIX, __VA_ARGS__)
#define LOG_INFO(...) LoggingSystem::Instance()->Info(LOG_PREFIX, __VA_ARGS__)
#define LOG_WARN(...) LoggingSystem::Instance()->Warn(LOG_PREFIX, __VA_ARGS__)
#define LOG_ERROR(...) LoggingSystem::Instance()->Error(LOG_PREFIX, __VA_ARGS__)
#define LOG_FATAL(...) LoggingSystem::Instance()->Fatal(LOG_PREFIX, __VA_ARGS__)

// callback macro using lambda
#define ENGINES_CALLBACK(func) [&](auto... args) { func(args...); }