#ifndef AVIDLIB_QMATH_VEC3_H
#define AVIDLIB_QMATH_VEC3_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ALQM_Vec3
{
	ALQM_Scalar v[3];
} ALQM_Vec3;

// Constants:
API_AVIDLIB_QMATH extern const ALQM_Vec3 ALQM_Vec3_Origin;

// Returns the raw float values of the vector.
API_AVIDLIB_QMATH float* ALQM_Vec3_Data(ALQM_Vec3* v);
API_AVIDLIB_QMATH const float* ALQM_Vec3_CData(ALQM_Vec3* v);

// Chainable functions, where vOut is returned:
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Zero(ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Copy(const ALQM_Vec3* vIn, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Add(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Vec3_Subtract(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut);
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_CrossProduct(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut);

API_AVIDLIB_QMATH ALQM_Scalar ALQM_Vec3_DotProduct(const ALQM_Vec3* v0, const ALQM_Vec3* v1);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_VEC3_H
