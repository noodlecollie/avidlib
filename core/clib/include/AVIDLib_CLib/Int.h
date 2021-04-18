#ifndef AVIDLIB_CLIB_INT_H
#define AVIDLIB_CLIB_INT_H

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t ALC_UInt8;
typedef int8_t ALC_Int8;
typedef char ALC_Char;

typedef uint16_t ALC_UInt16;
typedef int16_t ALC_Int16;

typedef uint32_t ALC_UInt32;
typedef int32_t ALC_Int32;

typedef uint64_t ALC_UInt64;
typedef int64_t ALC_Int64;

typedef size_t ALC_Size;

#define ALC_UINT8_MIN UINT8_MIN
#define ALC_UINT8_MAX UINT8_MAX
#define ALC_INT8_MIN INT8_MIN
#define ALC_INT8_MAX INT8_MAX

#define ALC_UINT16_MIN UINT16_MIN
#define ALC_UINT16_MAX UINT16_MAX
#define ALC_INT16_MIN INT16_MIN
#define ALC_INT16_MAX INT16_MAX

#define ALC_UINT32_MIN UINT32_MIN
#define ALC_UINT32_MAX UINT32_MAX
#define ALC_INT32_MIN INT32_MIN
#define ALC_INT32_MAX INT32_MAX

#define ALC_SIZE_MAX SIZE_MAX

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CLIB_INT_H
