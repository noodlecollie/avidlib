#ifndef AVIDLIB_QMATH_MATH_H
#define AVIDLIB_QMATH_MATH_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Core/Bool.h"

#ifdef __cplusplus
extern "C" {
#endif

API_AVIDLIB_QMATH ALQM_Scalar ALQM_Abs(ALQM_Scalar val);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Sqrt(ALQM_Scalar val);

// If you want to check if two scalars are *exactly* equal, use this function.
// Note, however, that most of the time you should be doing an approximate comparison.
API_AVIDLIB_QMATH ALC_Bool ALQM_ScalarsExactlyEqual(ALQM_Scalar val0, ALQM_Scalar val1);

API_AVIDLIB_QMATH ALC_Bool ALQM_ScalarsApproximatelyEqual(ALQM_Scalar val0, ALQM_Scalar val1);
API_AVIDLIB_QMATH ALC_Bool ALQM_ScalarApproximatelyZero(ALQM_Scalar val);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_MATH_H
