/**
 * About: EulerAngle.h
 * This file defines an Euler angle with pitch, yaw, and roll components.
 */

#ifndef AVIDLIB_QMATH_EULERANGLE_H
#define AVIDLIB_QMATH_EULERANGLE_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Plat/Bool.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Struct: ALQM_EulerAngle
 * Defines an Euler angle with pitch, yaw, and roll components.
 *
 * Euler angles are usually in degrees, but can also be in radians.
 * See the conversion functions <ALQM_EulerAngle_DegToRad> and
 * <ALQM_EulerAngle_RadToDeg>.
 */
typedef struct _ALQM_EulerAngle
{
	/**
	 * Variable: v
	 * Contains the pitch, yaw, and roll components of the Euler angle.
	 */
	ALQM_Scalar v[3];
} ALQM_EulerAngle;

/**
 * Section: Constants
 */

/**
 * Constant: ALQM_EULERANGLE_MAX_PITCH_DELTA
 * Maximum deviation from zero, in degrees, that pitch is allowed to be
 * for a normalised angle. This avoids gimbal lock at the poles.
 */
#define ALQM_EULERANGLE_MAX_PITCH_DELTA 89

/**
 * Enum: ALQM_EulerAxis
 * ALQM_PITCH - Pitch component of an <ALQM_EulerAngle>.
 * ALQM_YAW - Yaw component of an <ALQM_EulerAngle>.
 * ALQM_ROLL - Roll component of an <ALQM_EulerAngle>.
 */
typedef enum _ALQM_EulerAxis
{
	ALQM_PITCH = 0,
	ALQM_YAW = 1,
	ALQM_ROLL = 2
} ALQM_EulerAxis;

/**
 * Section: Operator Functions
 * All functions below assume that their inputs are valid Euler angles.
 * If this is not the case, undefined behaviour will result.
 *
 * Checking can be turned on by enabling the *PERFORM_VALIDITY_CHECKS*
 * CMake option. If this is turned on and invalid inputs are provided
 * to any of the functions below, an assertion failure will result.
 *
 * For functions which take an input and output angle,
 * the same angle object is allowed to be used for both parameters.
 * This can be useful for applying unary operations.
 */

/**
 * Group: Data Accessors
 * The following functions allow direct data access to the Euler angle.
 * They should be preferred when passing a raw <ALQM_Scalar> array is required.
 */

/**
 * Function: ALQM_EulerAngle_Data
 *
 * Returns a mutable pointer to the beginning of the angle's data.
 * There are 3 components.
 *
 * Parameters:
 *
 * a - Euler angle whose data should be returned.
 *
 * Returns:
 *
 * Mutable pointer to the angle's data.
 */
API_AVIDLIB_QMATH ALQM_Scalar* ALQM_EulerAngle_Data(ALQM_EulerAngle* a);

/**
 * Function: ALQM_EulerAngle_CData
 *
 * Returns a const pointer to the beginning of the angle's data.
 * There are 3 components.
 *
 * Parameters:
 *
 * a - Euler angle whose data should be returned.
 *
 * Returns:
 *
 * Const pointer to the angle's data.
 */
API_AVIDLIB_QMATH const ALQM_Scalar* ALQM_EulerAngle_CData(const ALQM_EulerAngle* a);

/**
 * Group: Chainable Modifier Functions
 * The following functions take a pointer to the Euler angle that is modified,
 * and also return this pointer. This allows function calls to be chained,
 * where the output of one call can be passed into another.
 */

/**
 * Function: ALQM_EulerAngle_Zero
 *
 * Sets all components of the Euler angle to zero.
 *
 * Parameters:
 *
 * aOut - Euler angle to set to zero.
 *
 * Returns:
 *
 * aOut.
 */
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_EulerAngle_Zero(ALQM_EulerAngle* aOut);

/**
 * Function: ALQM_EulerAngle_Copy
 *
 * Copies the values from aIn to aOut.
 *
 * Parameters:
 *
 * aIn  - Euler angle whose values are copied.
 * aOut - Euler angle that receives these values.
 *
 * Returns:
 *
 * aOut.
 */
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_EulerAngle_Copy(const ALQM_EulerAngle* aIn, ALQM_EulerAngle* aOut);

/**
 * Function: ALQM_EulerAngle_DegToRad
 *
 * Converts the values of an Euler angle from degrees to radians.
 *
 * Parameters:
 *
 * aIn  - Euler angle whose values will be converted. Values are assumed to be in degrees.
 * aOut - Euler angle that receives these values in radians.
 *
 * Returns:
 *
 * aOut.
 */
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_EulerAngle_DegToRad(const ALQM_EulerAngle* aIn, ALQM_EulerAngle* aOut);

/**
 * Function: ALQM_EulerAngle_RadToDeg
 *
 * Converts the values of an Euler angle from radians to degrees.
 *
 * Parameters:
 *
 * aIn  - Euler angle whose values will be converted. Values are assumed to be in radians.
 * aOut - Euler angle that receives these values in degrees.
 *
 * Returns:
 *
 * aOut.
 */
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_EulerAngle_RadToDeg(const ALQM_EulerAngle* aIn, ALQM_EulerAngle* aOut);

/**
 * Function: ALQM_EulerAngle_NormaliseDeg
 *
 * "Normalises" the values of an Euler angle so that they lie within specific ranges:
 *
 * - *Pitch:* [-89 89]
 * - *Yaw:* [0 360)
 * - *Roll:* [-180 180)
 *
 * It is assumed that the angles are in degrees.
 *
 * Parameters:
 *
 * aIn  - Euler angles whose values will be normalised.
 * aOut - Euler angle that receives these normalised values.
 *
 * Returns:
 *
 * aOut.
 */
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_EulerAngle_NormaliseDeg(const ALQM_EulerAngle* aIn, ALQM_EulerAngle* aOut);

/**
 * Group: Constant Functions
 * These functions do not modify the Euler angles they operate on.
 */

/**
 * Function: ALQM_EulerAngle_ExactlyEqual
 *
 * Returns whether two Euler angles are exactly equal.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_EulerAngle_ApproximatelyEqual>.
 *
 * Parameters:
 *
 * aLHS - Left hand side of the comparison.
 * aRHS - Right hand side of the comparison.
 *
 * Returns:
 *
 * True if the Euler angles are exactly equal, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_EulerAngle_ExactlyEqual(const ALQM_EulerAngle* aLHS, const ALQM_EulerAngle* aRHS);

/**
 * Function: ALQM_EulerAngle_ApproximatelyEqual
 *
 * Returns whether two Euler angles are approximately equal.
 *
 * This is essentially a componentwise comparison which calls <ALQM_ScalarsApproximatelyEqual>.
 *
 * Parameters:
 *
 * aLHS - Left hand side of the comparison.
 * aRHS - Right hand side of the comparison.
 *
 * Returns:
 *
 * True if the Euler angles are approximately equal, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_EulerAngle_ApproximatelyEqual(const ALQM_EulerAngle* aLHS, const ALQM_EulerAngle* aRHS);

/**
 * Function: ALQM_EulerAngle_ExactlyZero
 *
 * Returns whether all the Euler angle's components are exactly zero.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_EulerAngle_ApproximatelyZero>.
 *
 * Parameters:
 *
 * a - Euler angle whose components are compared against zero.
 *
 * Returns:
 *
 * True if all the Euler angle's components are exactly zero, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_EulerAngle_ExactlyZero(const ALQM_EulerAngle* a);

/**
 * Function: ALQM_EulerAngle_ApproximatelyZero
 *
 * Returns whether all the Euler angle's components are approximately zero.
 *
 * Parameters:
 *
 * a - Euler angle whose components are compared against zero.
 *
 * Returns:
 *
 * True if all the Euler angle's components are approximately zero, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_EulerAngle_ApproximatelyZero(const ALQM_EulerAngle* a);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_EULERANGLE_H
