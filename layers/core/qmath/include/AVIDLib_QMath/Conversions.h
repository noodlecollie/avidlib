#ifndef AVIDLIB_QMATH_CONVERSIONS_H
#define AVIDLIB_QMATH_CONVERSIONS_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/EulerAngle.h"

API_AVIDLIB_QMATH void EulerAngleToVec3(const ALQM_EulerAngle* angle, ALQM_Vec3* vecFwd, ALQM_Vec3* vecRight, ALQM_Vec3* vecUp);
API_AVIDLIB_QMATH void Vec3ToEulerAngle(const ALQM_Vec3* vecFwd, ALQM_EulerAngle* angle);

#endif // AVIDLIB_QMATH_CONVERSIONS_H
