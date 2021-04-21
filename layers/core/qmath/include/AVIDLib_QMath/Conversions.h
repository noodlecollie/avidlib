#ifndef AVIDLIB_QMATH_CONVERSIONS_H
#define AVIDLIB_QMATH_CONVERSIONS_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/EulerAngle.h"
#include "AVIDLib_QMath/Quat.h"
#include "AVIDLib_QMath/Mat3x4.h"

// For producing vectors:
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_EulerAngleRadToVec3Fwd(const ALQM_EulerAngle* inAngleRad, ALQM_Vec3* outVecFwd);
API_AVIDLIB_QMATH void ALQM_EulerAngleRadToVec3Basis(const ALQM_EulerAngle* inAngleRad, ALQM_Vec3* outVecFwd, ALQM_Vec3* outVecRight, ALQM_Vec3* outVecUp);

// For producing angles:
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_Vec3ToEulerAngleRad(const ALQM_Vec3* inVecFwd, ALQM_EulerAngle* outAngleRad);
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_QuatToEulerAngleRad(const ALQM_Quat* inQuat, ALQM_EulerAngle* outAngleRad);
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_Mat3x4ToEulerAngleRad(const ALQM_Mat3x4* inMat, ALQM_EulerAngle* outAngleRad);

// For producing matrices:
API_AVIDLIB_QMATH ALQM_Mat3x4* ALQM_Vec3AndQuatToMat3x4(const ALQM_Vec3* inOrigin, const ALQM_Quat* inQuat, ALQM_Mat3x4* outMat);

// For producing quaternions:
API_AVIDLIB_QMATH ALQM_Quat* ALQM_EulerAngleRadToQuat(const ALQM_EulerAngle* inAngleRad, ALQM_Quat* outQuat);

#endif // AVIDLIB_QMATH_CONVERSIONS_H
