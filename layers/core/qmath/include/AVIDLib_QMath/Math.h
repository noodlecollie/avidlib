#ifndef AVIDLIB_QMATH_MATH_H
#define AVIDLIB_QMATH_MATH_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Plat/Bool.h"

#ifdef __cplusplus
extern "C" {
#endif

API_AVIDLIB_QMATH ALQM_Scalar ALQM_Abs(ALQM_Scalar val);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Sqrt(ALQM_Scalar val);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_FMod(ALQM_Scalar val, ALQM_Scalar denom);

API_AVIDLIB_QMATH ALQM_Scalar ALQM_DegToRad(ALQM_Scalar deg);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_RadToDeg(ALQM_Scalar rad);

API_AVIDLIB_QMATH ALQM_Scalar ALQM_SinRad(ALQM_Scalar rad);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_CosRad(ALQM_Scalar rad);
API_AVIDLIB_QMATH void ALQM_SinCosRad(ALQM_Scalar rad, ALQM_Scalar* outSin, ALQM_Scalar* outCos);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_TanRad(ALQM_Scalar rad);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_ASinRad(ALQM_Scalar val);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_ACosRad(ALQM_Scalar val);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_ATan2Rad(ALQM_Scalar y, ALQM_Scalar x);

API_AVIDLIB_QMATH ALQM_Scalar ALQM_SinDeg(ALQM_Scalar deg);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_CosDeg(ALQM_Scalar deg);
API_AVIDLIB_QMATH void ALQM_SinCosDeg(ALQM_Scalar deg, ALQM_Scalar* outSin, ALQM_Scalar* outCos);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_TanDeg(ALQM_Scalar deg);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_ASinDeg(ALQM_Scalar val);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_ACosDeg(ALQM_Scalar val);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_ATan2Deg(ALQM_Scalar y, ALQM_Scalar x);

// Exact float comparisons are disallowed via compiler flag by default.
// If you want to check if two scalars are *exactly* equal, use these functions.
// Note, however, that most of the time you should be doing an approximate comparison.
API_AVIDLIB_QMATH ALP_Bool ALQM_ScalarsExactlyEqual(ALQM_Scalar val0, ALQM_Scalar val1);
API_AVIDLIB_QMATH ALP_Bool ALQM_ScalarExactlyZero(ALQM_Scalar val);

API_AVIDLIB_QMATH ALP_Bool ALQM_ScalarsApproximatelyEqual(ALQM_Scalar val0, ALQM_Scalar val1);
API_AVIDLIB_QMATH ALP_Bool ALQM_ScalarApproximatelyZero(ALQM_Scalar val);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_MATH_H
