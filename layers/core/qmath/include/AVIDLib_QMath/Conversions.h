#ifndef AVIDLIB_QMATH_CONVERSIONS_H
#define AVIDLIB_QMATH_CONVERSIONS_H

#include "AVIDLib_QMath/LibExport.h"

typedef struct _ALQM_EulerAngle ALQM_EulerAngle;
typedef struct _ALQM_Vec3 ALQM_Vec3;
typedef struct _ALQM_Quat ALQM_Quat;

API_AVIDLIB_QMATH void ALQM_EulerAngleRadToVec3(const ALQM_EulerAngle* inAngleRad, ALQM_Vec3* outVecFwd, ALQM_Vec3* outVecRight, ALQM_Vec3* outVecUp);
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_Vec3ToEulerAngleRad(const ALQM_Vec3* inVecFwd, ALQM_EulerAngle* outAngleRad);
API_AVIDLIB_QMATH ALQM_Quat* ALQM_EulerAngleRadToQuat(const ALQM_EulerAngle* inAngleRad, ALQM_Quat* outQuat);
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_QuatToEulerAngleRad(const ALQM_Quat* inQuat, ALQM_EulerAngle* outAngleRad);

#endif // AVIDLIB_QMATH_CONVERSIONS_H
