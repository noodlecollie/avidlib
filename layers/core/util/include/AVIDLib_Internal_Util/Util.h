#ifndef AVIDLIB_INTERNAL_UTIL_UTIL_H
#define AVIDLIB_INTERNAL_UTIL_UTIL_H

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <string.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// #define min and #define max are evil. We define macros that aren't as likely
// to collide catastrophically with other names in the global namespace.
#define ALU_MIN(a, b) ((a) < (b) ? (a) : (b))
#define ALU_MAX(a, b) ((a) > (b) ? (a) : (b))

// Convenience macro to mark an input argument as being unused.
#define ALU_UNUSED(arg) (void)(arg)

// Convenience macro for determining the length of an array.
#define ALU_ARRAY_LENGTH(arr) (sizeof(arr) / sizeof((arr)[0]))

// Alias for offsetof
#define ALP_OFFSETOF(struct, member) offsetof(struct, member)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_INTERNAL_UTIL_UTIL_H
