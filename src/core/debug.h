/*
 * Debug header
 *
 * WARNING: for the moment, GCC with Intel processor only supported
 * INTEL is due to INTEL asm instruction
 * TODO: propably better to fix this
 */

#ifndef ENGINE_CORE_DEBUG_H_
#define ENGINE_CORE_DEBUG_H_

#include <stdio.h>


// -----------------------------------------------------------------------------
// ASSERTIONS
// -----------------------------------------------------------------------------
#ifdef _ASSERTIONS_ENABLED //Usually on debug mode only

#define debugBreak() \
    __asm__("int $3") // GCC with Intel only
#define assertFailureMsg(EXP) \
    fprintf(stderr, "[ASSERT] %s:%d: error: "#EXP" should be true", __FILE__, __LINE__)

// ASSERT Macro
// NOTE: doesn't work like <assert.h>
// If assertion are not enabled, EXP is totally removed
#   define ASSERT(EXP) \
        if (EXP) {} \
        else { \
            assertFailureMsg(EXP); \
            debugBreak(); \
        }
#else
    // Simply skip the insert
#   define ASSERT(EXP)
#endif



#endif // End header protector


