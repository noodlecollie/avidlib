#ifndef AVIDLIB_QMATH_EULERANGLE_H
#define AVIDLIB_QMATH_EULERANGLE_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Plat/Bool.h"

#ifdef __cplusplus
extern "C" {
#endif

// Maximum deviation from zero that pitch is allowed to be for a normalised angle.
// This avoids gimbal lock at the poles.
#define ALQM_EULERANGLE_MAX_PITCH_DELTA 89

typedef enum _ALQM_EulerAxis
{
	ALQM_PITCH = 0,
	ALQM_YAW = 1,
	ALQM_ROLL = 2
} ALQM_EulerAxis;

// Pitch, yaw and roll, specified in degrees.
typedef struct _ALQM_EulerAngle
{
	ALQM_Scalar v[3];
} ALQM_EulerAngle;

// Returns the raw scalar values of the angle.
API_AVIDLIB_QMATH ALQM_Scalar* ALQM_EulerAngle_Data(ALQM_EulerAngle* a);
API_AVIDLIB_QMATH const ALQM_Scalar* ALQM_EulerAngle_CData(const ALQM_EulerAngle* a);

// Chainable functions, where aOut is returned:
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_EulerAngle_Zero(ALQM_EulerAngle* aOut);
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_EulerAngle_Copy(const ALQM_EulerAngle* aIn, ALQM_EulerAngle* aOut);
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_EulerAngle_DegToRad(const ALQM_EulerAngle* aIn, ALQM_EulerAngle* aOut);
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_EulerAngle_RadToDeg(const ALQM_EulerAngle* aIn, ALQM_EulerAngle* aOut);

// Normalised angles are in the form:
// - Pitch: (-90 90)
// - Yaw: [0 360)
// - Roll: [-180 180)
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_EulerAngle_Normalise(const ALQM_EulerAngle* aIn, ALQM_EulerAngle* aOut);

API_AVIDLIB_QMATH ALP_Bool ALQM_EulerAngle_ExactlyEqual(const ALQM_EulerAngle* aLHS, const ALQM_EulerAngle* aRHS);
API_AVIDLIB_QMATH ALP_Bool ALQM_EulerAngle_ApproximatelyEqual(const ALQM_EulerAngle* aLHS, const ALQM_EulerAngle* aRHS);
API_AVIDLIB_QMATH ALP_Bool ALQM_EulerAngle_ExactlyZero(const ALQM_EulerAngle* a);
API_AVIDLIB_QMATH ALP_Bool ALQM_EulerAngle_ApproximatelyZero(const ALQM_EulerAngle* a);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_EULERANGLE_H
