#include "AVIDLib_QMath/Math.h"
#include "AVIDLib_QMath/Constants.h"
#include "AVIDLib_CLib/Util.h"

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <math.h>

#define FLOAT_APPROX_EPSILON (1.0e-5f)

ALQM_Scalar ALQM_Abs(ALQM_Scalar val)
{
	return fabsf(val);
}

ALQM_Scalar ALQM_Sqrt(ALQM_Scalar val)
{
	return sqrtf(val);
}

// The only place we're allowed to do this:
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif // __GNUC__

ALC_Bool ALQM_ScalarsExactlyEqual(ALQM_Scalar val0, ALQM_Scalar val1)
{
	return val0 == val1;
}

// This is built from the information on https://embeddeduse.com/2019/08/26/qt-compare-two-floats/
ALC_Bool ALQM_ScalarsApproximatelyEqual(ALQM_Scalar val0, ALQM_Scalar val1)
{
	// Comparison goes whack if either value is zero, so make sure they're not.

	if ( val0 == 0.0f )
	{
		val0 += 1.0f;
		val1 += 1.0f;

		// This may have caused val1 to be zero - check.
		if ( val1 == 0.0f )
		{
			val0 += 1.0f;
			val1 += 1.0f;
		}
	}

	if ( val1 == 0.0f )
	{
		val0 += 1.0f;
		val1 += 1.0f;

		// This may have caused val0 to be zero - check.
		if ( val0 == 0.0f )
		{
			val0 += 1.0f;
			val1 += 1.0f;
		}
	}

	const ALQM_Scalar absDiff = ALQM_Abs(val1 - val0);

	if ( absDiff <= FLOAT_APPROX_EPSILON )
	{
		return ALC_TRUE;
	}

	const float absV0 = ALQM_Abs(val0);
	const float absV1 = ALQM_Abs(val1);

	return absDiff <= FLOAT_APPROX_EPSILON * ALC_MAX(absV0, absV1);
}

ALC_Bool ALQM_ScalarApproximatelyZero(ALQM_Scalar val)
{
	return ALQM_ScalarsApproximatelyEqual(val, 0);
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif // __GNUC__
