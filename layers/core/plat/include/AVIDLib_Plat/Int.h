/*
	About: Int.h
	This file provides integer-related definitions for the chosen platform.
*/

#ifndef AVIDLIB_PLAT_INT_H
#define AVIDLIB_PLAT_INT_H

/*
	For now, we just use platform headers.
	If we get to a point in future where we need to swap this out
	depending on our target platform, we can add ifdefs.
*/
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
	Types: 8-bit Integers
	ALP_UInt8 - AVIDLib unsigned 8-bit integer type.
	ALP_Int8  - AVIDLib signed 8-bit integer type.
	ALP_Char  - AVIDLib character type.
*/
typedef uint8_t ALP_UInt8;
typedef int8_t ALP_Int8;
typedef char ALP_Char;

/*
	Types: 16-bit Integers
	ALP_UInt16 - AVIDLib unsigned 16-bit integer type.
	ALP_Int16  - AVIDLib signed 16-bit integer type.
*/
typedef uint16_t ALP_UInt16;
typedef int16_t ALP_Int16;

/*
	Types: 32-bit integers
	ALP_UInt32 - AVIDLib unsigned 32-bit integer type.
	ALP_Int32  - AVIDLib signed 32-bit integer type.
*/
typedef uint32_t ALP_UInt32;
typedef int32_t ALP_Int32;

/*
	Types: 64-bit integers
	ALP_UInt64 - AVIDLib unsigned 64-bit integer type.
	ALP_Int64  - AVIDLib signed 64-bit integer type.
*/
typedef uint64_t ALP_UInt64;
typedef int64_t ALP_Int64;

/*
	Types: Size types
	ALP_Size - AVIDLib size/index type.
*/
typedef size_t ALP_Size;

/*
	Constants: 8-bit Integer Ranges
	ALP_UINT8_MIN - Minimum value of an 8-bit unsigned integer.
	ALP_UINT8_MAX - Maximum value of an 8-bit unsigned integer.
	ALP_INT8_MIN  - Minimum value of an 8-bit signed integer.
	ALP_INT8_MAX  - Maximum value of an 8-bit signed integer.
*/
#define ALP_UINT8_MIN UINT8_MIN
#define ALP_UINT8_MAX UINT8_MAX
#define ALP_INT8_MIN INT8_MIN
#define ALP_INT8_MAX INT8_MAX

/*
	Constants: 16-bit Integer Ranges
	ALP_UINT16_MIN - Minimum value of a 16-bit unsigned integer.
	ALP_UINT16_MAX - Maximum value of a 16-bit unsigned integer.
	ALP_INT16_MIN  - Minimum value of a 16-bit signed integer.
	ALP_INT16_MAX  - Maximum value of a 16-bit signed integer.
*/
#define ALP_UINT16_MIN UINT16_MIN
#define ALP_UINT16_MAX UINT16_MAX
#define ALP_INT16_MIN INT16_MIN
#define ALP_INT16_MAX INT16_MAX

/*
	Constants: 32-bit Integer Ranges
	ALP_UINT32_MIN - Minimum value of a 32-bit unsigned integer.
	ALP_UINT32_MAX - Maximum value of a 32-bit unsigned integer.
	ALP_INT32_MIN  - Minimum value of a 32-bit signed integer.
	ALP_INT32_MAX  - Maximum value of a 32-bit signed integer.
*/
#define ALP_UINT32_MIN UINT32_MIN
#define ALP_UINT32_MAX UINT32_MAX
#define ALP_INT32_MIN INT32_MIN
#define ALP_INT32_MAX INT32_MAX

/*
	Constants: Size Type Ranges
	ALP_SIZE_MAX - Maximum value of the ALP_Size type.
*/
#define ALP_SIZE_MAX SIZE_MAX

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_PLAT_INT_H
