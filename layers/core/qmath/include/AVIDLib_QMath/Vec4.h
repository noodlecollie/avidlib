/**
 * About: Vec4.h
 * This file defines a 4D geometric vector.
 */

#ifndef AVIDLIB_QMATH_VEC4_H
#define AVIDLIB_QMATH_VEC4_H

#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Plat/Int.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Struct: ALQM_Vec4
 * Defines a geometric point in 4D space.
 *
 * See <Vec4.h> for documentation on functions.
 */
typedef struct _ALQM_Vec4
{
	/**
	 * Variable: v
	 * Contains X, Y, Z, and W components of the vector.
	 */
	ALQM_Scalar v[4];
} ALQM_Vec4;

/**
 * Section: Constants
 */

/**
 * Variable: ALQM_Vec4_Origin
 * Zero vector representing a point at the 4D origin.
 */
API_AVIDLIB_QMATH extern const ALQM_Vec4 ALQM_Vec4_Origin;

/**
 * Enum: ALQM_Vec4Axis
 * ALQM_VEC4X - X component of an <ALQM_Vec4>.
 * ALQM_VEC4Y - Y component of an <ALQM_Vec4>.
 * ALQM_VEC4Z - Z component of an <ALQM_Vec4>.
 * ALQM_VEC4W - W component of an <ALQM_Vec4>.
 */
typedef enum _ALQM_Vec4Axis
{
	ALQM_VEC4X = 0,
	ALQM_VEC4Y = 1,
	ALQM_VEC4Z = 2,
	ALQM_VEC4W = 3
} ALQM_Vec4Axis;

/**
 * Section: Operator Functions
 * All functions below assume that their inputs are valid vectors.
 * If this is not the case, undefined behaviour will result.
 *
 * Checking can be turned on by enabling the *PERFORM_VALIDITY_CHECKS*
 * CMake option. If this is turned on and invalid inputs are provided
 * to any of the functions below, an assertion failure will result.
 *
 * For functions which take an input and output vector,
 * the same vector object is allowed to be used for both parameters.
 * This can be useful for applying unary operations like negation.
 */

/**
 * Group: Data Accessors
 * The following functions allow direct data access to the vector.
 * They should be preferred when passing a raw <ALQM_Scalar> array is required.
 */

/**
 * Function: ALQM_Vec4_Data
 *
 * Returns a mutable pointer to the beginning of the vector's data.
 * There are 4 components.
 *
 * Parameters:
 *
 * v - Vector whose data should be returned.
 *
 * Returns:
 *
 * Mutable pointer to the vector's data.
 */
API_AVIDLIB_QMATH ALQM_Scalar* ALQM_Vec4_Data(ALQM_Vec4* v);

/**
 * Function: ALQM_Vec4_CData
 *
 * Returns a const pointer to the beginning of the vector's data.
 * There are 4 components.
 *
 * Parameters:
 *
 * v - Vector whose data should be returned.
 *
 * Returns:
 *
 * Const pointer to the vector's data.
 */
API_AVIDLIB_QMATH const ALQM_Scalar* ALQM_Vec4_CData(const ALQM_Vec4* v);

/**
 * Group: Chainable Modifier Functions
 * The following functions take a pointer to the vector that is modified,
 * and also return this pointer. This allows function calls to be chained,
 * where the output of one call can be passed into another.
 */

/**
 * Function: ALQM_Vec4_Zero
 *
 * Sets all components of the vector to zero.
 *
 * Parameters:
 *
 * vOut - Vector to set to zero.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec4* ALQM_Vec4_Zero(ALQM_Vec4* vOut);

/**
 * Function: ALQM_Vec4_Copy
 *
 * Copies the values from vIn to vOut.
 *
 * Parameters:
 *
 * vIn  - Vector whose values are copied.
 * vOut - Vector that receives these values.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec4* ALQM_Vec4_Copy(const ALQM_Vec4* vIn, ALQM_Vec4* vOut);

/**
 * Function: ALQM_Vec4_SetValuesArray
 *
 * Sets values in the vector using a raw ALQM_Scalar array.
 * The count must be at least 4. Data is expected to be specified
 * in XYZW order.
 *
 * Parameters:
 *
 * values - Pointer to an array of scalar values.
 * count  - Length of this array of values.
 * vOut   - Vector whose values will be set.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec4* ALQM_Vec4_SetValuesArray(const ALQM_Scalar* values, ALP_Size count, ALQM_Vec4* vOut);

/**
 * Function: ALQM_Vec4_Add
 *
 * Adds two vectors together.
 *
 * Parameters:
 *
 * vLHS - Left hand side of the addition.
 * vRHS - Right hand side of the addition.
 * vOut - Vector in which to store the result.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec4* ALQM_Vec4_Add(const ALQM_Vec4* vLHS, const ALQM_Vec4* vRHS, ALQM_Vec4* vOut);

/**
 * Function: ALQM_Vec4_Subtract
 *
 * Subtracts one vector from another.
 *
 * Parameters:
 *
 * vLHS - Left hand side of the subtraction.
 * vRHS - Right hand side of the subtraction.
 * vOut - Vector in which to store the result.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec4* ALQM_Vec4_Subtract(const ALQM_Vec4* vLHS, const ALQM_Vec4* vRHS, ALQM_Vec4* vOut);

/**
 * Function: ALQM_Vec4_MultiplyAdd
 *
 * Takes a vector vScaleAdd, scales its values uniformly, and adds these to the values in vIn.
 * The result is stored in vOut.
 *
 * Parameters:
 *
 * vIn        - Vector whose values are used as the reference point.
 * scale      - Value by which to scale the components of vScaledAdd.
 * vScaledAdd - Vector whose components are scaled and added to vIn.
 * vOut       - Vector in which to store the result.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec4* ALQM_Vec4_MultiplyAdd(const ALQM_Vec4* vIn, ALQM_Scalar scale, const ALQM_Vec4* vScaledAdd, ALQM_Vec4* vOut);

/**
 * Function: ALQM_Vec4_Normalise
 *
 * Normalises a vector to unit length.
 *
 * Parameters:
 *
 * vIn  - Vector to normalise.
 * vOut - Vector in which to store the result.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec4* ALQM_Vec4_Normalise(const ALQM_Vec4* vIn, ALQM_Vec4* vOut);

/**
 * Function: ALQM_Vec4_Negate
 *
 * Negates a vector, multiplying all its components by -1.
 *
 * Parameters:
 *
 * vIn  - Vector to negate.
 * vOut - Vector in which to store the result.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec4* ALQM_Vec4_Negate(const ALQM_Vec4* vIn, ALQM_Vec4* vOut);

/**
 * Function: ALQM_Vec4_Scale
 *
 * Uniformly scales all components in a vector.
 *
 * Parameters:
 *
 * vIn  - Vector to scale.
 * vOut - Vector in which to store the result.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec4* ALQM_Vec4_Scale(const ALQM_Vec4* vIn, ALQM_Scalar scale, ALQM_Vec4* vOut);

/**
 * Group: Non-Chainable Modifier Functions
 * These functions modify the input vector, but are not chainable.
 */

/**
 * Function: ALQM_Vec4_NormaliseAndGetLength
 *
 * Normalises the input vector, and returns its original length before normalisation.
 *
 * Parameters:
 *
 * vIn  - Input vector to normalise.
 * vOut - Vector in which to store the result of the normalisation.
 *
 * Returns:
 *
 * The length of vIn before it was normalised.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec4_NormaliseAndGetLength(const ALQM_Vec4* vIn, ALQM_Vec4* vOut);

/**
 * Group: Constant Functions
 * These functions do not modify the vectors they operate on.
 */

/**
 * Function: ALQM_Vec4_DotProduct
 *
 * Calculates the dot product (sometimes called the scalar product) of two vectors.
 *
 * Parameters:
 *
 * vLHS - Left hand side of the operation.
 * vRHS - Right hand side of the operation.
 *
 * Returns:
 *
 * Result of the dot product calculation.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec4_DotProduct(const ALQM_Vec4* vLHS, const ALQM_Vec4* vRHS);

/**
 * Function: ALQM_Vec4_ExactlyEqual
 *
 * Returns whether two vectors are exactly equal.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Vec4_ApproximatelyEqual>.
 *
 * Parameters:
 *
 * vLHS - Left hand side of the comparison.
 * vRHS - Right hand side of the comparison.
 *
 * Returns:
 *
 * True if the vectors are exactly equal, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Vec4_ExactlyEqual(const ALQM_Vec4* vLHS, const ALQM_Vec4* vRHS);

/**
 * Function: ALQM_Vec4_ApproximatelyEqual
 *
 * Returns whether two vectors are approximately equal.
 *
 * This is essentially a componentwise comparison which calls <ALQM_ScalarsApproximatelyEqual>.
 *
 * Parameters:
 *
 * vLHS - Left hand side of the comparison.
 * vRHS - Right hand side of the comparison.
 *
 * Returns:
 *
 * True if the vectors are approximately equal, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Vec4_ApproximatelyEqual(const ALQM_Vec4* vLHS, const ALQM_Vec4* vRHS);

/**
 * Function: ALQM_Vec4_ExactlyZero
 *
 * Returns whether all the vector's components are exactly zero.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Vec4_ApproximatelyZero>.
 *
 * Parameters:
 *
 * v - Vector whose components are compared against zero.
 *
 * Returns:
 *
 * True if all the vector's components are exactly zero, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Vec4_ExactlyZero(const ALQM_Vec4* v);

/**
 * Function: ALQM_Vec4_ApproximatelyZero
 *
 * Returns whether all the vector's components are approximately zero.
 *
 * Parameters:
 *
 * v - Vector whose components are compared against zero.
 *
 * Returns:
 *
 * True if all the vector's components are approximately zero, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Vec4_ApproximatelyZero(const ALQM_Vec4* v);

/**
 * Function: ALQM_Vec4_Length
 *
 * Returns the length of the vector.
 *
 * Parameters:
 *
 * v - Vector to calculate length of.
 *
 * Returns:
 *
 * Length of the input vector.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec4_Length(const ALQM_Vec4* v);

/**
 * Function: ALQM_Vec4_LengthSquared
 *
 * Returns the square of the length of the vector. This can be used as
 * an optimisation in the case where the exact length is not required,
 * and so a square root operation can be avoided.
 *
 * Parameters:
 *
 * v - Vector to calculate squared length of.
 *
 * Returns:
 *
 * Square of length of the vector.
 */
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec4_LengthSquared(const ALQM_Vec4* v);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_VEC4_H
