/**
 * About: Math.h
 * This file defines common mathematical functions and helpers.
 */

#ifndef AVIDLIB_QMATH_MATH_H
#define AVIDLIB_QMATH_MATH_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Plat/Bool.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Group: General Operations
 */

/**
 * Function: ALQM_Abs
 *
 * Returns the absolute value (or magnitude) of the input.
 *
 * Parameters:
 *
 * val: Value to compute the absolute value of.
 *
 * Returns:
 *
 * Absolue value of the input.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Abs(ALQM_Scalar val);

/**
 * Function: ALQM_Sqrt
 *
 * Returns the square root of the input.
 *
 * Parameters:
 *
 * val: Value to compute the square root of.
 *
 * Returns:
 *
 * Square root of the input.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Sqrt(ALQM_Scalar val);

/**
 * Function: ALQM_FMod
 *
 * Returns the remainder after dividing the given value by the given denominator.
 * This is also referred to as computing the value "modulo" the denominator.
 *
 * Parameters:
 *
 * val   - Value to divide by the denominator.
 * denom - Value to use as the denominator (or divisor).
 *
 * Returns:
 *
 * Remainder of the calculation (val / denom).
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_FMod(ALQM_Scalar val, ALQM_Scalar denom);

/**
 * Group: Unit Conversions
 */

/**
 * Function: ALQM_DegToRad
 *
 * Converts a value in degrees to the equivalent value in radians.
 *
 * Parameters:
 *
 * deg - Value in degrees.
 *
 * Returns:
 *
 * Equivalent value in radians.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_DegToRad(ALQM_Scalar deg);

/**
 * Function: ALQM_RadToDeg
 *
 * Converts a value in radoans to the equivalent value in degrees.
 *
 * Parameters:
 *
 * rad - Value in radians.
 *
 * Returns:
 *
 * Equivalent value in degrees.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_RadToDeg(ALQM_Scalar rad);

/**
 * Group: Trigonometry (Radians)
 */

/**
 * Function: ALQM_SinRad
 *
 * Returns the sine of the provided value, where the value is specified in radians.
 *
 * Parameters:
 *
 * rad - Value in radians.
 *
 * Returns:
 *
 * Sine of the value.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_SinRad(ALQM_Scalar rad);

/**
 * Function: ALQM_CosRad
 *
 * Returns the cosine of the provided value, where the value is specified in radians.
 *
 * Parameters:
 *
 * rad - Value in radians.
 *
 * Returns:
 *
 * Cosine of the value.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_CosRad(ALQM_Scalar rad);

/**
 * Function: ALQM_SinCosRad
 *
 * Convenience function that computes the sine and cosine of the provided value,
 * where the value is specified in radians.
 *
 * Parameters:
 *
 * rad    - Value in radians.
 * outSin - Variable that receives the sine of the input value.
 * outCos - Variable that receives the cosine of the input value.
 */
API_AVIDLIB_QMATH void ALQM_SinCosRad(ALQM_Scalar rad, ALQM_Scalar* outSin, ALQM_Scalar* outCos);

/**
 * Function: ALQM_TanRad
 *
 * Returns the tangent of the provided value, where the value is specified in radians.
 *
 * Parameters:
 *
 * rad - Value in radians.
 *
 * Returns:
 *
 * Tangent of the value.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_TanRad(ALQM_Scalar rad);

/**
 * Function: ALQM_ASinRad
 *
 * Given a value in the range [-1 1], returns the inverse sine of this value
 * (ie. the original angle that produced the sine value), in radians.
 *
 * If the input is out of range, behaviour is undefined.
 *
 * Parameters:
 *
 * val - Value in range [-1 1].
 *
 * Returns:
 *
 * Angle in radians, where the sine of this angle is equal to val.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_ASinRad(ALQM_Scalar val);

/**
 * Function: ALQM_ACosRad
 *
 * Given a value in the range [-1 1], returns the inverse cosine of this value
 * (ie. the original angle that produced the cosine value), in radians.
 *
 * If the input is out of range, behaviour is undefined.
 *
 * Parameters:
 *
 * val - Value in range [-1 1].
 *
 * Returns:
 *
 * Angle in radians, where the cosine of this angle is equal to val.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_ACosRad(ALQM_Scalar val);

/**
 * Function: ALQM_ATan2Rad
 *
 * Returns the principal value of the inverse tangent of y/x, in radians.
 *
 * The function takes the signs of y and x into account to determine the quadrant.
 *
 * If both y and x are zero, behaviour is undefined.
 *
 * Parameters:
 *
 * y - Numerator of the input ratio.
 * x - Denominator of the input ratio.
 *
 * Returns:
 *
 * Principal inverse tangent of y/x in radians, in the range [-pi pi].
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_ATan2Rad(ALQM_Scalar y, ALQM_Scalar x);

/**
 * Group: Trigonometry (Degrees)
 */

/**
 * Function: ALQM_SinDeg
 *
 * Returns the sine of the provided value, where the value is specified in degrees.
 *
 * Parameters:
 *
 * rad - Value in degrees.
 *
 * Returns:
 *
 * Sine of the value.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_SinDeg(ALQM_Scalar deg);

/**
 * Function: ALQM_CosDeg
 *
 * Returns the cosine of the provided value, where the value is specified in degrees.
 *
 * Parameters:
 *
 * rad - Value in degrees.
 *
 * Returns:
 *
 * Cosine of the value.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_CosDeg(ALQM_Scalar deg);

/**
 * Function: ALQM_SinCosDeg
 *
 * Convenience function that computes the sine and cosine of the provided value,
 * where the value is specified in degrees.
 *
 * Parameters:
 *
 * rad    - Value in degrees.
 * outSin - Variable that receives the sine of the input value.
 * outCos - Variable that receives the cosine of the input value.
 */
API_AVIDLIB_QMATH void ALQM_SinCosDeg(ALQM_Scalar deg, ALQM_Scalar* outSin, ALQM_Scalar* outCos);

/**
 * Function: ALQM_TanDeg
 *
 * Returns the tangent of the provided value, where the value is specified in degrees.
 *
 * Parameters:
 *
 * rad - Value in degrees.
 *
 * Returns:
 *
 * Tangent of the value.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_TanDeg(ALQM_Scalar deg);

/**
 * Function: ALQM_ASinDeg
 *
 * Given a value in the range [-1 1], returns the inverse sine of this value
 * (ie. the original angle that produced the sine value), in degrees.
 *
 * If the input is out of range, behaviour is undefined.
 *
 * Parameters:
 *
 * val - Value in range [-1 1].
 *
 * Returns:
 *
 * Angle in degrees, where the sine of this angle is equal to val.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_ASinDeg(ALQM_Scalar val);

/**
 * Function: ALQM_ACosDeg
 *
 * Given a value in the range [-1 1], returns the inverse cosine of this value
 * (ie. the original angle that produced the cosine value), in degrees.
 *
 * If the input is out of range, behaviour is undefined.
 *
 * Parameters:
 *
 * val - Value in range [-1 1].
 *
 * Returns:
 *
 * Angle in degrees, where the cosine of this angle is equal to val.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_ACosDeg(ALQM_Scalar val);

/**
 * Function: ALQM_ATan2Deg
 *
 * Returns the principal value of the inverse tangent of y/x, in degrees.
 *
 * The function takes the signs of y and x into account to determine the quadrant.
 *
 * If both y and x are zero, behaviour is undefined.
 *
 * Parameters:
 *
 * y - Numerator of the input ratio.
 * x - Denominator of the input ratio.
 *
 * Returns:
 *
 * Principal inverse tangent of y/x in degrees, in the range [-pi pi].
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_ATan2Deg(ALQM_Scalar y, ALQM_Scalar x);

/**
 * Group: Floating Point Comparisons
 */

/**
 * Function: ALQM_ScalarsExactlyEqual
 *
 * Compares two scalars for exact equality.
 *
 * Exact floating-point number comparisons are disallowed via compiler flag by default.
 * If you want to check if two scalars are *exactly* equal, use this function.
 * Note, however, that most of the time you should be doing an approximate comparison.
 *
 * Parameters:
 *
 * lhs - Left hand side of the comparison.
 * rhs - Right hand side of the comparison.
 *
 * Returns:
 *
 * True if the scalars are exactly equal, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_ScalarsExactlyEqual(ALQM_Scalar lhs, ALQM_Scalar rhs);

/**
 * Function: ALQM_ScalarExactlyZero
 *
 * Compares a scalar for exact equality with zero.
 *
 * Exact floating-point number comparisons are disallowed via compiler flag by default.
 * If you want to check if a scalar is *exactly* equal, use this function.
 * Note, however, that most of the time you should be doing an approximate comparison.
 *
 * Parameters:
 *
 * val - Value to compare against zero.
 *
 * Returns:
 *
 * True if the scalar is exactly zero, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_ScalarExactlyZero(ALQM_Scalar val);

/**
 * Function: ALQM_ScalarsApproximatelyEqual
 *
 * Compares two scalars for approximate equality.
 *
 * This function follows the methodology described at
 * <https://embeddeduse.com/2019/08/26/qt-compare-two-floats/>.
 * It is modelled on the "pragmatic solution" from that page:
 *
 * ======= C++ =======
 * bool floatCompare(float f1, float f2) const
 * {
 *     if (qAbs(f1 - f2) <= 1.0e-5f)
 *     {
 *         return true;
 *     }
 *
 *     return qAbs(f1 - f2) <= 1.0e-5f * qMax(qAbs(f1), qAbs(f2));
 * }
 * ===================
 *
 * The pragmatic solution compares whether the absolute difference
 * between the two values are less than or equal to an epsilon.
 * If it is, the values are considered approximately equal.
 *
 * If the absolute difference is greater than the epsilon, the comparison
 * is performed again but with the epsilon scaled by the maximum of the
 * magnitudes of either of the values. This means that for larger values,
 * a larger equality tolerance is used.
 *
 * In <ALQM_ScalarsApproximatelyEqual>, the epsilon used is <ALQM_SCALAR_EPSILON>.
 * Additionally, it performs preliminary checks to detect whether either lhs or
 * rhs is zero, and adds 1 to each of these if this is the case, in order to
 * avoid issues around comparisons against zero.
 *
 * Parameters:
 *
 * lhs - Left hand side of the comparison.
 * rhs - Right hand side of the comparison.
 *
 * Returns:
 *
 * True if the scalars are approximately equal, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_ScalarsApproximatelyEqual(ALQM_Scalar lhs, ALQM_Scalar rhs);

/**
 * Function: ALQM_ScalarApproximatelyZero
 *
 * Compares a scalar for approximate equality with zero.
 *
 * This function is a helper for calling <ALQM_ScalarsApproximatelyEqual>.
 *
 * Parameters:
 *
 * val - Value to compare against zero.
 *
 * Returns:
 *
 * True if the scalar is approximately zero, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_ScalarApproximatelyZero(ALQM_Scalar val);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_MATH_H
