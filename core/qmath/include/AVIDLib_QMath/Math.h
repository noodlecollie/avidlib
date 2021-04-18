#ifndef AVIDLIB_QMATH_MATH_H
#define AVIDLIB_QMATH_MATH_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_CLib/Bool.h"

#ifdef __cplusplus
extern "C" {
#endif

API_AVIDLIB_QMATH ALQM_Scalar ALQM_Abs(ALQM_Scalar val);
API_AVIDLIB_QMATH ALQM_Scalar ALQM_Sqrt(ALQM_Scalar val);

API_AVIDLIB_QMATH ALC_Bool ALQM_ApproxEqual(ALQM_Scalar val0, ALQM_Scalar val1);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_MATH_H
