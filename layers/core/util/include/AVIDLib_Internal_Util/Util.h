#ifndef AVIDLIB_UTIL_UTIL_H
#define AVIDLIB_UTIL_UTIL_H

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
#define ALU_MIN(a, b) ((a) < (b) ? (a) : (b))
#define ALU_MAX(a, b) ((a) > (b) ? (a) : (b))

static inline void* ALU_MemCpy(void* restrict dest, const void* restrict src, ALP_Size count)
{
	return memcpy(dest, src, count);
}

static inline void* ALU_MemSet(void* ptr, ALP_UInt8 value, ALP_Size num)
{
	return memset(ptr, value, num);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_UTIL_UTIL_H
