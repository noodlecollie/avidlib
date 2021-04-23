/**
 * About: Constants.h
 * This file provides mathematical constants for use with other mathematical objects.
 */

#ifndef AVIDLIB_QMATH_CONSTANTS_H
#define AVIDLIB_QMATH_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constant: ALQM_PI
 * Approximation of the mathematical constant pi.
 */
#define ALQM_PI 3.14159265358979323846f

/**
 * Constant: ALQM_NAN
 * Originally defined in Quake's codebase to determine a float value set to "not a number".
 */
#define ALQM_NAN (255 << 23)

/**
 * Macro: ALQM_ISNAN
 * Expands to an expression which is true if the argument is "not a number", or false otherwise.
 */
#define ALQM_ISNAN(x) (((*(int *)&(x)) & ALQM_NAN) == ALQM_NAN)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_CONSTANTS_H
