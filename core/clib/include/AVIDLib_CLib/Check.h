#ifndef AVIDLIB_CLIB_CHECK_H
#define AVIDLIB_CLIB_CHECK_H

// Always make sure that assertions defined in this file actually take effect.
#ifdef NDEBUG
#define NDEBUG_WAS_SET
#undef NDEBUG
#endif

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

// This maps to an assertion which will always be checked
#define ALC_ASSERT_ALWAYS(expr) assert(expr)

#ifdef AVIDLIB_DEBUG
// This maps to an assertion which will only be checked in debug mode.
#define ALC_ASSERT(expr) assert(expr)
#else
#define ALC_ASSERT(expr)
#endif // AVIDLIB_DEBUG

#ifdef AVIDLIB_VALIDITY_CHECKS
// This maps to an if-statement that will only exist if AVIDLIB_VALIDITY_CHECKS is defined.
// If this is not defined, this macro evaluates to nothing.
// This is designed to be used where the if-statement constitutes a sanity check on
// values which are expected to always be valid under normal use. For example:
// ALC_IF_VALID( ptr )
// {
//     SomeFunction(ptr->val);
// }
#define ALC_IF_VALID(expr) if ( !!(expr) )

// This substitutes a ternary expression, and returns expected or fallback depending on
// whether the expression is true or false. If AVIDLIB_VALIDITY_CHECKS is not defined,
// expected is always returned.
#define ALC_RET_VALID(expr, expected, fallback) ( (expr) ? (expected) : (fallback) )
#else
#define ALC_IF_VALID(expr)
#define ALC_RET_VALID(expr, expected, fallback) (expected)
#endif // AVIDLIB_VALIDITY_CHECKS

#ifdef __cplusplus
} // extern "C"
#endif

// Restore the previous state of NDEBUG.
#ifdef NDEBUG_WAS_SET
#define NDEBUG
#undef NDEBUG_WAS_SET
#endif

#endif // AVIDLIB_CLIB_CHECK_H
