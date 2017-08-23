/*
 * General project configurations and settings.
 *
 * WARNING
 * At the moment, only GCC supported.
 */

#pragma once


// FORCE_INLINE MACRO
#ifdef _DEBUG
#   define FORCE_INLINE inline // In Debug mode, doesn't fore inline
#else
#   define FORCE_INLINE inline __attribute__((always_inline))
#endif


#define GCC_ALIGNED(n) __attribute__((aligned(n)))

