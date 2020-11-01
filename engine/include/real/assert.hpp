// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_ASSERT
#define REAL_ASSERT

#include "real/logger.hpp"

#define REAL_EXPAND_MACRO(x) x
#define REAL_STRINGIFY_MACRO(x) #x

//region real_dbg_assert and real_debugbreak()
// Thanks https://github.com/nemequ/portable-snippets/tree/master/debug-trap for knowledge
#if defined(__has_builtin) && !defined(__ibmxl__)
#  if __has_builtin(__builtin_debugtrap)
#    define real_debugbreak() __builtin_debugtrap()
#  elif __has_builtin(__debugbreak)
#    define real_debugbreak() __debugbreak()
#  endif
#endif
#if !defined(real_debugbreak)
#  if defined(_MSC_VER) || defined(__INTEL_COMPILER)
#    define real_debugbreak() __debugbreak()
#  elif defined(__ARMCC_VERSION)
#    define real_debugbreak() __breakpoint(42)
#  elif defined(__ibmxl__) || defined(__xlC__)
#    include <builtins.h>
#    define real_debugbreak() __trap(42)
#  elif defined(__DMC__) && defined(_M_IX86)
static inline void real_debugbreak(void) { __asm int 3h; }
#  elif defined(__i386__) || defined(__x86_64__)
static inline void real_debugbreak(void) { __asm__ __volatile__("int3"); }
#  elif defined(__thumb__)
static inline void real_debugbreak(void) { __asm__ __volatile__(".inst 0xde01"); }
#  elif defined(__aarch64__)
	 static inline void real_debugbreak(void) { __asm__ __volatile__(".inst 0xd4200000"); }
#  elif defined(__arm__)
	 static inline void real_debugbreak(void) { __asm__ __volatile__(".inst 0xe7f001f0"); }
#  elif defined (__alpha__) && !defined(__osf__)
	 static inline void real_debugbreak(void) { __asm__ __volatile__("bpt"); }
#  elif defined(_54_)
	 static inline void real_debugbreak(void) { __asm__ __volatile__("ESTOP"); }
#  elif defined(_55_)
	 static inline void real_debugbreak(void) { __asm__ __volatile__(";\n .if (.MNEMONIC)\n ESTOP_1\n .else\n ESTOP_1()\n .endif\n NOP"); }
#  elif defined(_64P_)
	 static inline void real_debugbreak(void) { __asm__ __volatile__("SWBP 0"); }
#  elif defined(_6x_)
	 static inline void real_debugbreak(void) { __asm__ __volatile__("NOP\n .word 0x10000000"); }
#  elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ == 0) && defined(__GNUC__)
#    define real_debugbreak() __builtin_trap()
#  else
#    include <signal.h>
#    if defined(SIGTRAP)
#      define real_debugbreak() raise(SIGTRAP)
#    else
#      define real_debugbreak() raise(SIGABRT)
#    endif
#  endif
#endif

#if defined(HEDLEY_LIKELY)
#  define REAL_DBG_LIKELY(expr) HEDLEY_LIKELY(expr)
#elif defined(__GNUC__) && (__GNUC__ >= 3)
#  define REAL_DBG_LIKELY(expr) __builtin_expect(!!(expr), 1)
#else
#  define REAL_DBG_LIKELY(expr) (!!(expr))
#endif

#if defined(REAL_DEBUG)
#  define real_dbg_assert(expr) do { \
    if (!REAL_DBG_LIKELY(expr)) { \
      real_debugbreak(); \
    } \
  } while (0)
# define real_msg_assert(expr, ...) do { \
    if (!REAL_DBG_LIKELY(expr)) { \
      REAL_EXPAND_MACRO(REAL_CORE_ERROR)(__VA_ARGS__); \
    } \
  } while (0)
#else
#  define real_dbg_assert(expr)
#  define real_msg_assert(expr, ...)
#endif

//endregion


#endif //REAL_ASSERT
