/**
 * About: Quat.h
 * This file defines a geometric rotation in 3D space.
 */

#ifndef AVIDLIB_QMATH_QUATERNION_H
#define AVIDLIB_QMATH_QUATERNION_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Plat/Bool.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Struct: ALQM_Quat
 * Defines a geometric rotation in 3D space.
 *
 * See <Quat.h> for documentation on functions.
 */
typedef struct _ALQM_Quat
{
	/**
	 * Variable: v
	 * Contains X, Y, Z, and W components of the quaternion.
	 */
	ALQM_Scalar v[4];
} ALQM_Quat;

/**
 * Section: Constants
 */

/**
 * Variable: ALQM_Quat_Identity
 * Quaternion representing an identity transformation.
 * This transformation is defined such that transforming any
 * vector or quaternion by the identity leaves the vector or
 * quaternion unchanged.
 */
API_AVIDLIB_QMATH extern const ALQM_Quat ALQM_Quat_Identity;

/**
 * Enum: ALQM_QuatComponent
 * ALQM_QUATX - X component of an <ALQM_Quat> (sometimes referred to mathematically as i).
 * ALQM_QUATY - Y component of an <ALQM_Quat> (sometimes referred to mathematically as j).
 * ALQM_QUATZ - Z component of an <ALQM_Quat> (sometimes referred to mathematically as k).
 * ALQM_QUATW - W component of an <ALQM_Quat> (sometimes referred to mathematically as the "real" component).
 */
typedef enum _ALQM_QuatComponent
{
	ALQM_QUATX = 0,
	ALQM_QUATY = 1,
	ALQM_QUATZ = 2,
	ALQM_QUATW = 3
} ALQM_QuatComponent;

/**
 * Section: Operator Functions
 * All functions below assume that their inputs are valid quaternions.
 * If this is not the case, undefined behaviour will result.
 *
 * Checking can be turned on by enabling the *PERFORM_VALIDITY_CHECKS*
 * CMake option. If this is turned on and invalid inputs are provided
 * to any of the functions below, an assertion failure will result.
 *
 * For functions which take an input and output quaternion,
 * the same quaternion object is allowed to be used for both parameters.
 * This can be useful for applying unary operations like negation.
 */

/**
 * Group: Data Accessors
 * The following functions allow direct data access to the quaternion.
 * They should be preferred when passing a raw <ALQM_Scalar> array is required.
 */

/**
 * Function: ALQM_Quat_Data
 *
 * Returns a mutable pointer to the beginning of the quaternion's data.
 * There are 3 components.
 *
 * Parameters:
 *
 * q - Quaternion whose data should be returned.
 *
 * Returns:
 *
 * Mutable pointer to the quaternion's data.
 */
API_AVIDLIB_QMATH ALQM_Scalar* ALQM_Quat_Data(ALQM_Quat* q);

/**
 * Function: ALQM_Quat_CData
 *
 * Returns a const pointer to the beginning of the quaternion's data.
 * There are 3 components.
 *
 * Parameters:
 *
 * q - Quaternion whose data should be returned.
 *
 * Returns:
 *
 * Const pointer to the quaternion's data.
 */
API_AVIDLIB_QMATH const ALQM_Scalar* ALQM_Quat_CData(const ALQM_Quat* q);

/**
 * Group: Chainable Modifier Functions
 * The following functions take a pointer to the quaternion that is modified,
 * and also return this pointer. This allows function calls to be chained,
 * where the output of one call can be passed into another.
 */

/**
 * Function: ALQM_Quat_SetIdentity
 *
 * Sets the given quaternion to the identity.
 *
 * Parameters:
 *
 * qOut - Quaternion to set to identity.
 *
 * Returns:
 *
 * qOut.
 */
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_SetIdentity(ALQM_Quat* qOut);

/**
 * Function: ALQM_Quat_Zero
 *
 * Sets every component in the given quaternion to zero.
 *
 * Parameters:
 *
 * qOut - Quaternion to zero.
 *
 * Returns:
 *
 * qOut.
 */
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Zero(ALQM_Quat* qOut);

/**
 * Function: ALQM_Quat_Copy
 *
 * Copies the values from qIn to qOut.
 *
 * Parameters:
 *
 * qIn  - Quaternion whose values are copied.
 * qOut - Quaternion that receives these values.
 *
 * Returns:
 *
 * qOut.
 */
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Copy(const ALQM_Quat* qIn, ALQM_Quat* qOut);

/**
 * Function: ALQM_Quat_SetValuesArray
 *
 * Sets values in the quaternion using a raw ALQM_Scalar array.
 * The count must be at least 4. Data is expected to be specified
 * in XYZW order.
 *
 * Parameters:
 *
 * values - Pointer to an array of scalar values.
 * count  - Length of this array of values.
 * qOut   - Quaternion whose values will be set.
 *
 * Returns:
 *
 * qOut.
 */
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_SetValuesArray(const ALQM_Scalar* values, ALP_Size count, ALQM_Quat* qOut);

/**
 * Function: ALQM_Quat_Multiply
 *
 * Multiplies two quaternions together.
 *
 * Parameters:
 *
 * qLHS - Left hand side of the operation.
 * qRHS - Right hand side of the operation.
 * qOut - Quaternion in which to store the result.
 *
 * Returns:
 *
 * qOut.
 */
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Multiply(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS, ALQM_Quat* qOut);

/**
 * Function: ALQM_Vec3_Normalise
 *
 * Normalises a quaternion to unit length.
 *
 * Parameters:
 *
 * qIn  - Quaternion to normalise.
 * qOut - Quaternion in which to store the result.
 *
 * Returns:
 *
 * qOut.
 */
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Normalise(const ALQM_Quat* qIn, ALQM_Quat* qOut);

/**
 * Function: ALQM_Quat_Add
 *
 * Adds two quaternions together.
 *
 * Parameters:
 *
 * qLHS - Left hand side of the operation.
 * qRHS - Right hand side of the operation.
 * qOut - Quaternion in which to store the result.
 *
 * Returns:
 *
 * qOut.
 */
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Add(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS, ALQM_Quat* qOut);

/**
 * Function: ALQM_Quat_Subtract
 *
 * Subtracts one quaternion from another.
 *
 * Parameters:
 *
 * qLHS - Left hand side of the operation.
 * qRHS - Right hand side of the operation.
 * qOut - Quaternion in which to store the result.
 *
 * Returns:
 *
 * qOut.
 */
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Subtract(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS, ALQM_Quat* qOut);

/**
 * Function: ALQM_Quat_Scale
 *
 * Multiplies a quaternion by a scalar value.
 *
 * Parameters:
 *
 * qIn   - Input quaternion to be scaled.
 * scale - Value by which to scale the quaternion.
 * qOut  - Quaternion in which to store the result.
 *
 * Returns:
 *
 * qOut.
 */
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Scale(const ALQM_Quat* qIn, ALQM_Scalar scale, ALQM_Quat* qOut);

/**
 * Group: Constant Functions
 * These functions do not modify the quaternions they operate on.
 */

/**
 * Function: ALQM_Quat_DotProduct
 *
 * Calculates the dot product (sometimes called the scalar product) of two quaternions.
 *
 * Parameters:
 *
 * qLHS - Left hand side of the operation.
 * qRHS - Right hand side of the operation.
 *
 * Returns:
 *
 * Result of the dot product calculation.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Quat_DotProduct(const ALQM_Quat* q0, const ALQM_Quat* q1);

/**
 * Function: ALQM_Quat_ExactlyEqual
 *
 * Returns whether two Quaternions are exactly equal.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Quat_ApproximatelyEqual>.
 *
 * Parameters:
 *
 * qLHS - Left hand side of the comparison.
 * qRHS - Right hand side of the comparison.
 *
 * Returns:
 *
 * True if the quaternions are exactly equal, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Quat_ExactlyEqual(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS);

/**
 * Function: ALQM_Quat_ApproximatelyEqual
 *
 * Returns whether two quaternions are approximately equal.
 *
 * This is essentially a componentwise comparison which calls <ALQM_ScalarsApproximatelyEqual>.
 *
 * Parameters:
 *
 * qLHS - Left hand side of the comparison.
 * qRHS - Right hand side of the comparison.
 *
 * Returns:
 *
 * True if the quaternions are approximately equal, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Quat_ApproximatelyEqual(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS);

/**
 * Function: ALQM_Quat_ExactlyZero
 *
 * Returns whether all the quaternion's components are exactly zero.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Quat_ApproximatelyZero>.
 *
 * Parameters:
 *
 * q - Quaternion whose components are compared against zero.
 *
 * Returns:
 *
 * True if all the quaternion's components are exactly zero, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Quat_ExactlyZero(const ALQM_Quat* q);

/**
 * Function: ALQM_Quat_ApproximatelyZero
 *
 * Returns whether all the quaternion's components are approximately zero.
 *
 * Parameters:
 *
 * q - Quaternion whose components are compared against zero.
 *
 * Returns:
 *
 * True if all the quaternion's components are approximately zero, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Quat_ApproximatelyZero(const ALQM_Quat* q);

/**
 * Function: ALQM_Quat_ExactlyIdentity
 *
 * Returns whether the quaternion is exactly equal to the identity.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Quat_ApproximatelyIdentity>.
 *
 * Parameters:
 *
 * q - Quaternion which is compared against the identity.
 *
 * Returns:
 *
 * True if the quaternion is exactly equal to the identity, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Quat_ExactlyIdentity(const ALQM_Quat* q);

/**
 * Function: ALQM_Quat_ApproximatelyIdentity
 *
 * Returns whether the quaternion is approximately equal to the identity.
 *
 * Parameters:
 *
 * q - Quaternion which is compared against the identity.
 *
 * Returns:
 *
 * True if the quaternion is approximately equal to the identity, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Quat_ApproximatelyIdentity(const ALQM_Quat* q);

/**
 * Function: ALQM_Quat_Length
 *
 * Returns the length of the quaternion.
 *
 * Parameters:
 *
 * q - Quaternion to calculate length of.
 *
 * Returns:
 *
 * Length of the input quaternion.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Quat_Length(const ALQM_Quat* q);

/**
 * Function: ALQM_Quat_LengthSquared
 *
 * Returns the square of the length of the quaternion. This can be used as
 * an optimisation in the case where the exact length is not required,
 * and so a square root operation can be avoided.
 *
 * Parameters:
 *
 * q - Quaternion to calculate squared length of.
 *
 * Returns:
 *
 * Square of length of the quaternion.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Quat_LengthSquared(const ALQM_Quat* q);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_QUATERNION_H
