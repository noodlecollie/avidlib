/**
 * About: Bool.h
 * This file provides boolean-related definitions for the chosen platform.
 */

#ifndef AVIDLIB_PLAT_BOOL_H
#define AVIDLIB_PLAT_BOOL_H

/**
 * Bool comes as part of C++, so don't mess with anything if this header
 * has been imported into a C++ application.
 */
#ifndef __cplusplus

/**
 * For now, we just use platform headers.
 * If we get to a point in future where we need to swap this out
 * depending on our target platform, we can add ifdefs.
 */
#include <stdbool.h>

#endif // __cplusplus

/**
 * Type: ALP_Bool
 * AVIDLib boolean type.
 */
typedef bool ALP_Bool;

/**
 * Constants: Boolean Constants
 * ALP_TRUE  - AVIDLib constant representing a "true" value.
 * ALP_FALSE - AVIDLib constant representing a "false" value.
 */
#define ALP_TRUE true
#define ALP_FALSE false

#endif // AVIDLIB_PLAT_BOOL_H
