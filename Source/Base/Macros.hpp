#pragma once

#include "Global.hpp"
#include "LoggingSystem.hpp"

#include <cassert>

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

// TODO: move this to somewhere else
#define ES_DEBUG 1

#ifndef ES_ASSERT
#if defined(ES_DEBUG) && ES_DEBUG > 0
#define ES_ASSERT(COND, MSG)                         \
    do {                                             \
        if (!(COND)) {                               \
            if (std::strlen(MSG) > 0)                \
                LOG_FATAL("Assert failed: {}", MSG); \
            assert((COND));                          \
        }                                            \
    } while (0)
#define ES_ASSERT_NOMSG(COND) assert((COND));
#else
#define ES_ASSERT(COND, MSG)
#define ES_ASSERT_NOMSG(COND)
#endif
#endif