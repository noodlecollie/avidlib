#include "AVIDLib_QMath/Math.h"
#include "AVIDLib_QMath/Constants.h"
#include "AVIDLib_Plat/Util.h"

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

ALQM_Scalar ALQM_FMod(ALQM_Scalar val, ALQM_Scalar denom)
{
	return fmodf(val, denom);
}

ALQM_Scalar ALQM_DegToRad(ALQM_Scalar deg)
{
	return (deg * ALQM_PI) / 180.0f;
}

ALQM_Scalar ALQM_RadToDeg(ALQM_Scalar rad)
{
	return (rad * 180.0f) / ALQM_PI;
}

ALQM_Scalar ALQM_SinRad(ALQM_Scalar rad)
{
	return sinf(rad);
}

ALQM_Scalar ALQM_CosRad(ALQM_Scalar rad)
{
	return cosf(rad);
}

ALQM_Scalar ALQM_ATan2Rad(ALQM_Scalar y, ALQM_Scalar x)
{
	return atan2f(y, x);
}

ALQM_Scalar ALQM_SinDeg(ALQM_Scalar deg)
{
	return sinf(ALQM_DegToRad(deg));
}

ALQM_Scalar ALQM_CosDeg(ALQM_Scalar deg)
{
	return cosf(ALQM_DegToRad(deg));
}

ALQM_Scalar ALQM_ATan2Deg(ALQM_Scalar y, ALQM_Scalar x)
{
	return ALQM_RadToDeg(atan2f(y, x));
}

// The only place we're allowed to do this:
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif // __GNUC__

ALP_Bool ALQM_ScalarsExactlyEqual(ALQM_Scalar val0, ALQM_Scalar val1)
{
	return val0 == val1;
}

// This is built from the information on https://embeddeduse.com/2019/08/26/qt-compare-two-floats/
ALP_Bool ALQM_ScalarsApproximatelyEqual(ALQM_Scalar val0, ALQM_Scalar val1)
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
		return ALP_TRUE;
	}

	const float absV0 = ALQM_Abs(val0);
	const float absV1 = ALQM_Abs(val1);

	return absDiff <= FLOAT_APPROX_EPSILON * ALP_MAX(absV0, absV1);
}

ALP_Bool ALQM_ScalarApproximatelyZero(ALQM_Scalar val)
{
	return ALQM_ScalarsApproximatelyEqual(val, 0);
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif // __GNUC__
