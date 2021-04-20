#ifndef AVIDLIB_PLAT_INT_H
#define AVIDLIB_PLAT_INT_H

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t ALP_UInt8;
typedef int8_t ALP_Int8;
typedef char ALP_Char;

typedef uint16_t ALP_UInt16;
typedef int16_t ALP_Int16;

typedef uint32_t ALP_UInt32;
typedef int32_t ALP_Int32;

typedef uint64_t ALP_UInt64;
typedef int64_t ALP_Int64;

typedef size_t ALP_Size;

#define ALP_UINT8_MIN UINT8_MIN
#define ALP_UINT8_MAX UINT8_MAX
#define ALP_INT8_MIN INT8_MIN
#define ALP_INT8_MAX INT8_MAX

#define ALP_UINT16_MIN UINT16_MIN
#define ALP_UINT16_MAX UINT16_MAX
#define ALP_INT16_MIN INT16_MIN
#define ALP_INT16_MAX INT16_MAX

#define ALP_UINT32_MIN UINT32_MIN
#define ALP_UINT32_MAX UINT32_MAX
#define ALP_INT32_MIN INT32_MIN
#define ALP_INT32_MAX INT32_MAX

#define ALP_SIZE_MAX SIZE_MAX

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_PLAT_INT_H