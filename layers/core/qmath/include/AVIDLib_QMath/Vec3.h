#ifndef AVIDLIB_QMATH_VEC3_H
#define AVIDLIB_QMATH_VEC3_H

#include "AVIDLib_Core/Bool.h"
#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Core/Int.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _ALQM_Vec3Axis
{
	ALQM_XAXIS = 0,
	ALQM_YAXIS = 1,
	ALQM_ZAXIS = 2
} ALQM_Vec3Axis;

typedef struct _ALQM_Vec3
{
	ALQM_Scalar v[3];
} ALQM_Vec3;

// Constants:
API_AVIDLIB_QMATH extern const ALQM_Vec3 ALQM_Vec3_Origin;

// All functions below assume that their inputs are valid vectors.
// If this is not the case, undefined behaviour will result.
// Checking can be turned on using AVIDLIB_VALIDITY_CHECKS.

// Returns the raw float values of the vector.
API_AVIDLIB_QMATH float* ALQM_Vec3_Data(ALQM_Vec3* v);
API_AVIDLIB_QMATH const float* ALQM_Vec3_CData(const ALQM_Vec3* v);

// Chainable functions, where vOut is returned:
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Zero(ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Copy(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Set(const float* values, ALC_Size count, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Add(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Subtract(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_CrossProduct(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_MultiplyAdd(const ALQM_Vec3* vIn, ALQM_Scalar scale, const ALQM_Vec3* vScaledAdd, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Normalise(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Negate(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Scale(const ALQM_Vec3* vIn, ALQM_Scalar scale, ALQM_Vec3* vOut);

// These functions do not modify the vector
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec3_DotProduct(const ALQM_Vec3* v0, const ALQM_Vec3* v1);
API_AVIDLIB_QMATH ALC_Bool ALQM_Vec3_ExactlyEqual(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS);
API_AVIDLIB_QMATH ALC_Bool ALQM_Vec3_ApproximatelyEqual(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS);
API_AVIDLIB_QMATH ALC_Bool ALQM_Vec3_ExactlyZero(const ALQM_Vec3* v);
API_AVIDLIB_QMATH ALC_Bool ALQM_Vec3_ApproximatelyZero(const ALQM_Vec3* v);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec3_Length(const ALQM_Vec3* v);

// These functions modify the vector.
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec3_NormaliseAndGetLength(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_VEC3_H
