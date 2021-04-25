/**
 * About: VariadicArgs.h
 * This file provides typedef and definitions for variadic argument helpers.
 */

#ifndef AVIDLIB_PLAT_VARIADICARGS_H
#define AVIDLIB_PLAT_VARIADICARGS_H

/**
 * For now, we just use platform headers.
 * If we get to a point in future where we need to swap this out
 * depending on our target platform, we can add ifdefs.
 */
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Typedef: ALP_VAList
 * Typedef for C library's va_list.
 */
typedef va_list ALP_VAList;

/**
 * Definitions:
 * ALP_VA_START - Alias for C library's va_start.
 * ALP_VA_END   - Alias for C library's va_end.
 */
#define ALP_VA_START va_start
#define ALP_VA_END va_end

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_PLAT_VARIADICARGS_H
