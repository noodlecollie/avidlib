#ifndef AVIDLIB_PLAT_UTIL_H
#define AVIDLIB_PLAT_UTIL_H

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <string.h>

#include "AVIDLib_Plat/Int.h"

#ifdef __cplusplus
extern "C" {
#endif

// #define min and #define max are evil. We define macros that aren't as likely
// to collide catastrophically with other names in the global namespace.
#define ALP_MIN(a, b) ((a) < (b) ? (a) : (b))
#define ALP_MAX(a, b) ((a) > (b) ? (a) : (b))

static inline void* ALP_MemCpy(void* restrict dest, const void* restrict src, ALP_Size count)
{
	return memcpy(dest, src, count);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_PLAT_UTIL_H