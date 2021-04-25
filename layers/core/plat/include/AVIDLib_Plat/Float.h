/**
 * About: Float.h
 * This file provides floating point-related definitions for the chosen platform.
 */

#ifndef AVIDLIB_PLAT_FLOAT_H
#define AVIDLIB_PLAT_FLOAT_H

/**
 * For now, we just use platform headers.
 * If we get to a point in future where we need to swap this out
 * depending on our target platform, we can add ifdefs.
 */
#include <float.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Types: Floating Point Numbers
 * ALP_Float32 - 32-bit floating point numerical type.
 * ALP_Float64 - 64-bit floating point numerical type.
 */
typedef float ALP_Float32;
typedef double ALP_Float64;

/**
 * Constants: Floating Point Number Ranges
 * ALP_FLOAT32_MIN - Minimum value of a 32-bit floating point number.
 * ALP_FLOAT32_MAX - Maximum value of a 32-bit floating point number.
 * ALP_FLOAT64_MIN - Minimum value of a 64-bit floating point number.
 * ALP_FLOAT64_MAX - Maximum value of a 64-bit floating point number.
 */
#define ALP_FLOAT32_MIN FLT_MIN
#define ALP_FLOAT32_MAX FLT_MAX
#define ALP_FLOAT64_MIN DBL_MIN
#define ALP_FLOAT64_MAX DBL_MAX

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_PLAT_FLOAT_H
