#ifndef AVIDLIB_QMATH_QUATERNION_H
#define AVIDLIB_QMATH_QUATERNION_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Plat/Bool.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _ALQM_QuatComponent
{
	ALQM_QUATX = 0,
	ALQM_QUATY = 1,
	ALQM_QUATZ = 2,
	ALQM_QUATW = 3
} ALQM_QuatComponent;

typedef struct _ALQM_Quat
{
	ALQM_Scalar v[4];
} ALQM_Quat;

// Constants:
API_AVIDLIB_QMATH extern const ALQM_Quat ALQM_Quat_Identity;

// Returns the raw scalar values of the quaternion.
API_AVIDLIB_QMATH ALQM_Scalar* ALQM_Quat_Data(ALQM_Quat* q);
API_AVIDLIB_QMATH const ALQM_Scalar* ALQM_Quat_CData(const ALQM_Quat* q);

// Chainable functions, where qOut is returned:
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_SetIdentity(ALQM_Quat* qOut);
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Zero(ALQM_Quat* qOut);
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Copy(const ALQM_Quat* qIn, ALQM_Quat* qOut);
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Set(const ALQM_Scalar* values, ALP_Size count, ALQM_Quat* qOut);
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Multiply(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS, ALQM_Quat* qOut);
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Normalise(const ALQM_Quat* qIn, ALQM_Quat* qOut);
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Add(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS, ALQM_Quat* qOut);
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Subtract(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS, ALQM_Quat* qOut);
API_AVIDLIB_QMATH ALQM_Quat* ALQM_Quat_Scale(const ALQM_Quat* qIn, ALQM_Scalar scale, ALQM_Quat* qOut);

// These functions do not modify the quaternion.
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Quat_DotProduct(const ALQM_Quat* q0, const ALQM_Quat* q1);
API_AVIDLIB_QMATH ALP_Bool ALQM_Quat_ExactlyEqual(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS);
API_AVIDLIB_QMATH ALP_Bool ALQM_Quat_ApproximatelyEqual(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS);
API_AVIDLIB_QMATH ALP_Bool ALQM_Quat_ExactlyZero(const ALQM_Quat* q);
API_AVIDLIB_QMATH ALP_Bool ALQM_Quat_ApproximatelyZero(const ALQM_Quat* q);
API_AVIDLIB_QMATH ALP_Bool ALQM_Quat_ExactlyIdentity(const ALQM_Quat* q);
API_AVIDLIB_QMATH ALP_Bool ALQM_Quat_ApproximatelyIdentity(const ALQM_Quat* q);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Quat_Length(const ALQM_Quat* q);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Quat_LengthSquared(const ALQM_Quat* q);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_QUATERNION_H
