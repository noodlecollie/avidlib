/**
 * About: Vec3.h
 * This file defines a 3D geometric vector.
 */

#ifndef AVIDLIB_QMATH_VEC3_H
#define AVIDLIB_QMATH_VEC3_H

#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Plat/Int.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Struct: ALQM_Vec3
 * Defines a geometric point in 3D space.
 */
typedef struct _ALQM_Vec3
{
	/**
	 * Variable: v
	 * Contains X, Y, and Z components of the vector.
	 */
	ALQM_Scalar v[3];
} ALQM_Vec3;

/**
 * Section: Constants
 */

/**
 * Variable: ALQM_Vec3_Origin
 * Zero vector representing a point at the 3D origin.
 */
API_AVIDLIB_QMATH extern const ALQM_Vec3 ALQM_Vec3_Origin;

/**
 * Enum: ALQM_Vec3Axis
 * ALQM_VECX - X component of an <ALQM_Vec3>.
 * ALQM_VECY - Y component of an <ALQM_Vec3>.
 * ALQM_VECZ - Z component of an <ALQM_Vec3>.
 */
typedef enum _ALQM_Vec3Axis
{
	ALQM_VECX = 0,
	ALQM_VECY = 1,
	ALQM_VECZ = 2
} ALQM_Vec3Axis;

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
 * They should be preferred when passing a raw ALQM_Scalar array is required.
 */

/**
 * Function: ALQM_Vec3_Data
 *
 * Returns a mutable pointer to the beginning of the vector's data.
 * There are 3 components.
 *
 * Parameters:
 *
 * v - Vector whose data should be returned.
 *
 * Returns:
 *
 * Mutable pointer to the vector's data.
 */
API_AVIDLIB_QMATH ALQM_Scalar* ALQM_Vec3_Data(ALQM_Vec3* v);

/**
 * Function: ALQM_Vec3_CData
 *
 * Returns a const pointer to the beginning of the vector's data.
 * There are 3 components.
 *
 * Parameters:
 *
 * v - Vector whose data should be returned.
 *
 * Returns:
 *
 * Const pointer to the vector's data.
 */
API_AVIDLIB_QMATH const ALQM_Scalar* ALQM_Vec3_CData(const ALQM_Vec3* v);

/**
 * Group: Chainable Modifier Functions
 * The following functions take a pointer to the vector that is modified,
 * and also return this pointer. This allows function calls to be chained,
 * where the output of one call can be passed into another.
 */

/**
 * Function: ALQM_Vec3_Zero
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
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Zero(ALQM_Vec3* vOut);

/**
 * Function: ALQM_Vec3_Copy
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
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Copy(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);

/**
 * Function: ALQM_Vec3_SetValuesArray
 *
 * Sets values in the vector using a raw ALQM_Scalar array.
 * The count must be at least 3.
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
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_SetValuesArray(const ALQM_Scalar* values, ALP_Size count, ALQM_Vec3* vOut);

/**
 * Function: ALQM_Vec3_Add
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
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Add(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut);

/**
 * Function: ALQM_Vec3_Subtract
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
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Subtract(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut);

/**
 * Function: ALQM_Vec3_CrossProduct
 *
 * Calculates the cross product (sometimes called the vector product) of two vectors.
 * The resulting vector will be perpendicular to the two inputs.
 *
 * Parameters:
 *
 * vLHS - Left hand side of the operation.
 * vRHS - Right hand side of the operation.
 * vOut - Vector in which to store the result.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_CrossProduct(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut);

/**
 * Function: ALQM_Vec3_MultiplyAdd
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
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_MultiplyAdd(const ALQM_Vec3* vIn, ALQM_Scalar scale, const ALQM_Vec3* vScaledAdd, ALQM_Vec3* vOut);

/**
 * Function: ALQM_Vec3_Normalise
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
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Normalise(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);

/**
 * Function: ALQM_Vec3_Negate
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
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Negate(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);

/**
 * Function: ALQM_Vec3_Scale
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
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Scale(const ALQM_Vec3* vIn, ALQM_Scalar scale, ALQM_Vec3* vOut);

/**
 * Group: Non-Chainable Modifier Functions
 * These functions modify the input vector, but are not chainable.
 */

/**
 * Function: ALQM_Vec3_NormaliseAndGetLength
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
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec3_NormaliseAndGetLength(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);

/**
 * Group: Constant Functions
 * These functions do not modify the vectors they operate on.
 */

/**
 * Function: ALQM_Vec3_DotProduct
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
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec3_DotProduct(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS);

/**
 * Function: ALQM_Vec3_ExactlyEqual
 *
 * Returns whether two vectors are exactly equal.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Vec3_ApproximatelyEqual>.
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
API_AVIDLIB_QMATH ALP_Bool ALQM_Vec3_ExactlyEqual(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS);

/**
 * Function: ALQM_Vec3_ApproximatelyEqual
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
API_AVIDLIB_QMATH ALP_Bool ALQM_Vec3_ApproximatelyEqual(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS);

/**
 * Function: ALQM_Vec3_ExactlyZero
 *
 * Returns whether all the vector's components are exactly zero.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Vec3_ApproximatelyZero>.
 *
 * Parameters:
 *
 * v - Vector whose components are compared against zero.
 *
 * Returns:
 *
 * True if all the vector's components are exactly zero, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Vec3_ExactlyZero(const ALQM_Vec3* v);

/**
 * Function: ALQM_Vec3_ApproximatelyZero
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
API_AVIDLIB_QMATH ALP_Bool ALQM_Vec3_ApproximatelyZero(const ALQM_Vec3* v);

/**
 * Function: ALQM_Vec3_Length
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
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec3_Length(const ALQM_Vec3* v);

/**
 * Function: ALQM_Vec3_LengthSquared
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
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec3_LengthSquared(const ALQM_Vec3* v);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_VEC3_H
