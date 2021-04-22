/*
	About: Vec3.h
	This file defines a 3D geometric vector.
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

/*
	Section: Vec3 Type
*/

/*
	Struct: ALQM_Vec3
	Defines a geometric point in 3D space.
*/
typedef struct _ALQM_Vec3
{
	/*
		Variable: v
		Contains X, Y, and Z components of the vector.
	*/
	ALQM_Scalar v[3];
} ALQM_Vec3;

/*
	Section: Constants
*/

/*
	Variable: ALQM_Vec3_Origin
	Zero vector representing a point at the 3D origin.
*/
API_AVIDLIB_QMATH extern const ALQM_Vec3 ALQM_Vec3_Origin;

/*
	Enum: ALQM_Vec3Axis
	ALQM_VECX - X component of an ALQM_Vec3.
	ALQM_VECY - Y component of an ALQM_Vec3.
	ALQM_VECZ - Z component of an ALQM_Vec3.
*/
typedef enum _ALQM_Vec3Axis
{
	ALQM_VECX = 0,
	ALQM_VECY = 1,
	ALQM_VECZ = 2
} ALQM_Vec3Axis;

/*
	Section: Operator Functions
	All functions below assume that their inputs are valid vectors.
	If this is not the case, undefined behaviour will result.
	Checking can be turned on using AVIDLIB_VALIDITY_CHECKS.
*/

/*
	Group: Data Accessors
	The following functions allow direct data access to the vector.
	They should be preferred when passing a raw ALQM_Scalar array is required.
*/

/*
	Function: ALQM_Vec3_Data

	Returns a mutable pointer to the beginning of the vector's data.
	There are 3 components.

	Parameters:

	v - Vector whose data should be returned.

	Returns:

	Mutable pointer to the vector's data.
*/
API_AVIDLIB_QMATH ALQM_Scalar* ALQM_Vec3_Data(ALQM_Vec3* v);

/*
	Function: ALQM_Vec3_CData

	Returns a const pointer to the beginning of the vector's data.
	There are 3 components.

	Parameters:

	v - Vector whose data should be returned.

	Returns:

	Const pointer to the vector's data.
*/
API_AVIDLIB_QMATH const ALQM_Scalar* ALQM_Vec3_CData(const ALQM_Vec3* v);

/*
	Group: Chainable Functions
	The following functions take a pointer to the vector that is modified,
	and also return this pointer. This allows function calls to be chained,
	where the output of one call can be passed into another.

	Function: ALQM_Vec3_Zero

	Sets all components of the vector to zero.

	Parameters:

	vOut - Vector to set to zero.

	Returns:

	vOut.
*/
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Zero(ALQM_Vec3* vOut);

/*
	Function: ALQM_Vec3_Copy

	Copies the values from vIn to vOut.

	Parameters:

	vIn  - Vector whose values are copied.
	vOut - Vector that receives these values.

	Returns:

	vOut.
*/
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Copy(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_SetValuesArray(const ALQM_Scalar* values, ALP_Size count, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Add(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Subtract(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_CrossProduct(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_MultiplyAdd(const ALQM_Vec3* vIn, ALQM_Scalar scale, const ALQM_Vec3* vScaledAdd, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Normalise(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Negate(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Scale(const ALQM_Vec3* vIn, ALQM_Scalar scale, ALQM_Vec3* vOut);

// These functions do not modify the vector
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec3_DotProduct(const ALQM_Vec3* v0, const ALQM_Vec3* v1);
API_AVIDLIB_QMATH ALP_Bool ALQM_Vec3_ExactlyEqual(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS);
API_AVIDLIB_QMATH ALP_Bool ALQM_Vec3_ApproximatelyEqual(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS);
API_AVIDLIB_QMATH ALP_Bool ALQM_Vec3_ExactlyZero(const ALQM_Vec3* v);
API_AVIDLIB_QMATH ALP_Bool ALQM_Vec3_ApproximatelyZero(const ALQM_Vec3* v);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec3_Length(const ALQM_Vec3* v);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec3_LengthSquared(const ALQM_Vec3* v);

// These functions modify the vector.
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec3_NormaliseAndGetLength(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_VEC3_H
