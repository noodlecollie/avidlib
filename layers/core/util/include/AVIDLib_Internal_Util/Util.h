#ifndef AVIDLIB_INTERNAL_UTIL_UTIL_H
#define AVIDLIB_INTERNAL_UTIL_UTIL_H

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// #define min and #define max are evil. We define macros that aren't as likely
// to collide catastrophically with other names in the global namespace.
#define ALU_MIN(a, b) ((a) < (b) ? (a) : (b))
#define ALU_MAX(a, b) ((a) > (b) ? (a) : (b))

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_INTERNAL_UTIL_UTIL_H
