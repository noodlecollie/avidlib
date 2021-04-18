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
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline int ALC_AssertWithFeedback(int expression, const char* expressionStr, const char* file, int line)
{
	if ( !expression )
	{
		fprintf(stderr, "Assertion failed @ %s:%d \"%s\"\n", file, line, expressionStr);
		assert(0 && "Assertion failed - see stderr for information.");
	}

	return expression;
}

// This maps to an assertion which will always be checked
#define ALC_ASSERT_ALWAYS(expr) (ALC_AssertWithFeedback((!!(expr)), #expr, __FILE__, __LINE__))

#ifdef AVIDLIB_DEBUG
// This maps to an assertion which will only be checked in debug mode.
// If compiling without debug mode, this macro evaluates to nothing.
#define ALC_ASSERT_DEBUG(expr) (ALC_ASSERT_ALWAYS(expr))

// This asserts that the value is true if in debug mode,
// but just passes the value back if it is turned off.
// This is useful for if-statements.
#define ALC_CHECK_DEBUG(expr) (ALC_ASSERT_ALWAYS(expr))
#else
#define ALC_ASSERT_DEBUG(expr)
#define ALC_CHECK_DEBUG(expr) (!!(expr))
#endif // AVIDLIB_DEBUG

#ifdef AVIDLIB_VALIDITY_CHECKS
// This maps to an assertion which will only be checked if AVIDLIB_VALIDITY_CHECKS
// is turned on. Otherwise, this macro evaluates to nothing.
#define ALC_ASSERT_VALID(expr) (ALC_ASSERT_ALWAYS(expr))

// This asserts that the value is true if AVIDLIB_VALIDITY_CHECKS is turned on,
// but just passes the value back if it is turned off.
// This is useful for if-statements.
#define ALC_CHECK_VALID(expr) (ALC_ASSERT_ALWAYS(expr))

// This asserts that the value is true if AVIDLIB_VALIDITY_CHECKS is turned on,
// but always evaluates to true if it is turned off.
// This is useful for generating if-statements that check values when required,
// but which can compile down to "if ( true )" otherwise (at which point the
// compiler should optimise them out). It should only be used in cases where
// undefined behaviour may occur if the value is not true.
#define ALC_SANITY_VALID(expr) (ALC_ASSERT_ALWAYS(expr))

// This checks the condition and returns "expected" if the condition is true,
// or "fallback" if it is false. An assertion is failed if the condition is false,
// but only if AVIDLIB_VALIDITY_CHECKS is turned on.
#define ALC_TERNARY_VALID(expr, expected, fallback) (ALC_ASSERT_ALWAYS(expr) ? (expected) : (fallback))
#else
#define ALC_ASSERT_VALID(expr)
#define ALC_CHECK_VALID(expr) (!!(expr))
#define ALC_SANITY_VALID(expr) (!0)
#define ALC_TERNARY_VALID(expr, expected, fallback) ((!!(expr)) ? (expected) : (fallback))
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
