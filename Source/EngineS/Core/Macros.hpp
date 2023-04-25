#pragma once

#include "Core/IO/Logger.hpp"

#include <cassert>

// callback macro using lambda
#define ENGINES_CALLBACK(func) [&](auto... args) { func(args...); }

// TODO: move this to somewhere else
#define ES_DEBUG 1

#ifndef ES_ASSERT_MSG
#    if defined(ES_DEBUG) && ES_DEBUG > 0
#        define ES_ASSERT_MSG(COND, MSG)                         \
            do {                                                 \
                if (!(COND)) {                                   \
                    if (std::strlen(MSG) > 0)                    \
                        Logger::Error("Assert failed: {}", MSG); \
                    assert((COND));                              \
                }                                                \
            } while (0)
#        define ES_ASSERT(COND) assert((COND));
#    else
#        define ES_ASSERT(COND, MSG)
#        define ES_ASSERT_NOMSG(COND)
#    endif
#endif

#define ES_CONCAT_IMPL(a, b) a##b
#define ES_CONCAT(a, b) ES_CONCAT_IMPL(a, b)
