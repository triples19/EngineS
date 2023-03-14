#pragma once

namespace EngineS {

#define ES_PLATFORM_WINDOWS 1
#define ES_PLATFORM_LINUX 2
#define ES_PLATFORM_APPLE 3

#define ES_COMPILER_MSVC 1
#define ES_COMPILER_GNUC 2
#define ES_COMPILER_CLANG 3
#define ES_COMPILER_APPLECLANG 4

#define ES_ENDIAN_LITTLE 1
#define ES_ENDIAN_BIG 2

#define ES_ARCH_32 1
#define ES_ARCH_64 2

// Platform
// ref: https://github.com/cpredef/predef/blob/master/OperatingSystems.md
#if defined(__WIN32__) || defined(_WIN32)
#    define ES_PLATFORM ES_PLATFORM_WINDOWS
#elif defined(__APPLE__)
#    define ES_PLATFORM ES_PLATFORM_APPLE
#else
#    define ES_PLATFORM ES_PLATFORM_LINUX
#endif

// Compiler
// ref: https://github.com/cpredef/predef/blob/master/Compilers.md
#if defined(__clang__)
#    if defined(__apple_build_version__)
#        define ES_COMPILER ES_COMPILER_APPLECLANG
#    else
#        define ES_COMPILER ES_COMPILER_CLANG
#    endif
#    define ES_COMPILER_VERSION (((__clang_major__)*100) + (__clang_minor__ * 10) + __clang_patchlevel__)
#elif defined(__GNUC__)
#    define ES_COMPILER ES_COMPILER_GNUC
#    define ES_COMPILER_VERSION (((__GNUC__)*100) + (__GNUC_MINOR__ * 10) + __GNUC_PATCHLEVEL__)
#elif defined(_MSC_VER)
#    define ES_COMPILER ES_COMPILER_MSVC
#    define ES_COMPILER_VERSION _MSC_VER
#else
#    error "Unknown compiler"
#endif

// Architecture
// ref: https://github.com/cpredef/predef/blob/master/Architectures.md
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || \
    defined(__s390__) || defined(__s390x__) || defined(_LP64) || defined(__LP64__)
#    define ES_ARCH_TYPE ES_ARCH_64
#else
#    define ES_ARCH_TYPE ES_ARCH_32
#endif

// inline
#if ES_COMPILER == ES_COMPILER_MSVC
#    define ES_INLINE inline
#    define ES_FORCE_INLINE __forceinline
#elif ES_COMPILER == ES_COMPILER_GNUC
#    define ES_INLINE inline
#    define ES_FORCE_INLINE inline __attribute__((always_inline))
#elif ES_COMPILER == ES_COMPILER_CLANG || ES_COMPILER == ES_COMPILER_APPLECLANG
#    define ES_INLINE inline
#    define ES_FORCE_INLINE inline __attribute__((always_inline))
#else
#    define ES_INLINE inline
#    define ES_FORCE_INLINE inline // no force inline for other platforms possible
#endif

// warnings
#if ES_COMPILER == ES_COMPILER_GNUC
#    define ES_BEGIN_DISABLE_DEPRECATED_WARNING \
        _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#    define ES_END_DISABLE_DEPRECATED_WARNING _Pragma("GCC diagnostic pop")

#    define ES_BEGIN_DISABLE_CONDITIONAL_EXPR_WARNING
#    define ES_END_DISABLE_CONDITIONAL_EXPR_WARNING
#    if ES_COMP_VER >= 700
#        define ES_BEGIN_DISABLE_EXCEPT_TYPE_WARNING \
            _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wnoexcept-type\"")
#        define ES_END_DISABLE_EXCEPT_TYPE_WARNING _Pragma("GCC diagnostic pop")
#    else
#        define ES_BEGIN_DISABLE_EXCEPT_TYPE_WARNING
#        define ES_END_DISABLE_EXCEPT_TYPE_WARNING
#    endif

#    if ES_COMP_VER >= 510
#        define ES_BEGIN_DISABLE_OVERRIDE_WARNING \
            _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wsuggest-override\"")
#        define ES_END_DISABLE_OVERRIDE_WARNING _Pragma("GCC diagnostic pop")
#    else
#        define ES_BEGIN_DISABLE_OVERRIDE_WARNING
#        define ES_END_DISABLE_OVERRIDE_WARNING
#    endif

#    if ES_COMP_VER >= 900
#        define ES_BEGIN_DISABLE_INIT_LIST_WARNING \
            _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Winit-list-lifetime\"")
#        define ES_END_DISABLE_INIT_LIST_WARNING _Pragma("GCC diagnostic pop")
#    else
#        define ES_BEGIN_DISABLE_INIT_LIST_WARNING
#        define ES_END_DISABLE_INIT_LIST_WARNING
#    endif

#    define ES_DECLARE_PLUGIN_CTOR __attribute__((constructor))
#    define ES_DECLARE_PLUGIN_DTOR __attribute__((destructor))
#elif ES_COMPILER == ES_COMPILER_CLANG || ES_COMPILER == ES_COMPILER_APPLECLANG

#    if defined(__has_warning) && __has_warning("-Wdeprecated-declarations")
#        define ES_BEGIN_DISABLE_DEPRECATED_WARNING \
            _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#        define ES_END_DISABLE_DEPRECATED_WARNING _Pragma("clang diagnostic pop")
#    else
#        define ES_BEGIN_DISABLE_DEPRECATED_WARNING
#        define ES_END_DISABLE_DEPRECATED_WARNING
#    endif

#    define ES_BEGIN_DISABLE_CONDITIONAL_EXPR_WARNING
#    define ES_END_DISABLE_CONDITIONAL_EXPR_WARNING

#    if defined(__has_warning) && __has_warning("-Wnoexcept-type")
#        define ES_BEGIN_DISABLE_EXCEPT_TYPE_WARNING \
            _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wnoexcept-type\"")
#        define ES_END_DISABLE_EXCEPT_TYPE_WARNING _Pragma("clang diagnostic pop")
#    else
#        define ES_BEGIN_DISABLE_EXCEPT_TYPE_WARNING
#        define ES_END_DISABLE_EXCEPT_TYPE_WARNING
#    endif

#    if defined(__has_warning) && __has_warning("-Winconsistent-missing-override")
#        define ES_BEGIN_DISABLE_OVERRIDE_WARNING \
            _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Winconsistent-missing-override\"")
#        define ES_END_DISABLE_OVERRIDE_WARNING _Pragma("clang diagnostic pop")
#    else
#        define ES_BEGIN_DISABLE_OVERRIDE_WARNING
#        define ES_END_DISABLE_OVERRIDE_WARNING
#    endif

#    define ES_BEGIN_DISABLE_INIT_LIST_WARNING
#    define ES_END_DISABLE_INIT_LIST_WARNING

#    define ES_DECLARE_PLUGIN_CTOR __attribute__((__constructor__))
#    define ES_DECLARE_PLUGIN_DTOR __attribute__((__destructor__))

#elif ES_COMPILER == ES_COMPILER_MSVC
#    define ES_BEGIN_DISABLE_DEPRECATED_WARNING __pragma(warning(push)) __pragma(warning(disable : 4996))
#    define ES_END_DISABLE_DEPRECATED_WARNING __pragma(warning(pop))

#    define ES_BEGIN_DISABLE_CONDITIONAL_EXPR_WARNING __pragma(warning(push)) __pragma(warning(disable : 4127))
#    define ES_END_DISABLE_CONDITIONAL_EXPR_WARNING __pragma(warning(pop))

#    define ES_BEGIN_DISABLE_EXCEPT_TYPE_WARNING
#    define ES_END_DISABLE_EXCEPT_TYPE_WARNING
#    define ES_DECLARE_PLUGIN_CTOR
#    define ES_DECLARE_PLUGIN_DTOR
#    define ES_BEGIN_DISABLE_OVERRIDE_WARNING
#    define ES_END_DISABLE_OVERRIDE_WARNING
#    define ES_BEGIN_DISABLE_INIT_LIST_WARNING
#    define ES_END_DISABLE_INIT_LIST_WARNING
#endif

} // namespace EngineS
