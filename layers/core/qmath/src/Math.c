#include "AVIDLib_QMath/Math.h"
#include "AVIDLib_QMath/Constants.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Internal_Util/Check.h"

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <math.h>

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

void ALQM_SinCosRad(ALQM_Scalar rad, ALQM_Scalar* outSin, ALQM_Scalar* outCos)
{
	if ( ALU_CHECK_VALID(outSin || outCos) )
	{
		if ( outSin )
		{
			*outSin = ALQM_SinRad(rad);
		}

		if ( outCos )
		{
			*outCos = ALQM_CosRad(rad);
		}
	}
}

ALQM_Scalar ALQM_TanRad(ALQM_Scalar rad)
{
	return tanf(rad);
}

ALQM_Scalar ALQM_ASinRad(ALQM_Scalar val)
{
	return asinf(val);
}

ALQM_Scalar ALQM_ACosRad(ALQM_Scalar val)
{
	return acosf(val);
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

void ALQM_SinCosDeg(ALQM_Scalar deg, ALQM_Scalar* outSin, ALQM_Scalar* outCos)
{
	if ( ALU_CHECK_VALID(outSin || outCos) )
	{
		ALQM_SinCosRad(ALQM_DegToRad(deg), outSin, outCos);
	}
}

ALQM_Scalar ALQM_TanDeg(ALQM_Scalar deg)
{
	return tanf(ALQM_DegToRad(deg));
}

ALQM_Scalar ALQM_ASinDeg(ALQM_Scalar val)
{
	return ALQM_RadToDeg(ALQM_ASinRad(val));
}

ALQM_Scalar ALQM_ACosDeg(ALQM_Scalar val)
{
	return ALQM_RadToDeg(ALQM_ACosRad(val));
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

ALP_Bool ALQM_ScalarsExactlyEqual(ALQM_Scalar lhs, ALQM_Scalar rhs)
{
	return lhs == rhs;
}

ALP_Bool ALQM_ScalarExactlyZero(ALQM_Scalar val)
{
	return ALQM_ScalarsExactlyEqual(val, 0);
}

// This is built from the information on https://embeddeduse.com/2019/08/26/qt-compare-two-floats/
ALP_Bool ALQM_ScalarsApproximatelyEqual(ALQM_Scalar lhs, ALQM_Scalar rhs)
{
	// Comparison goes whack if either value is zero, so make sure they're not.

	if ( lhs == 0.0f )
	{
		lhs += 1.0f;
		rhs += 1.0f;

		// This may have caused rhs to be zero - check.
		if ( rhs == 0.0f )
		{
			lhs += 1.0f;
			rhs += 1.0f;
		}
	}

	if ( rhs == 0.0f )
	{
		lhs += 1.0f;
		rhs += 1.0f;

		// This may have caused lhs to be zero - check.
		if ( lhs == 0.0f )
		{
			lhs += 1.0f;
			rhs += 1.0f;
		}
	}

	const ALQM_Scalar absDiff = ALQM_Abs(rhs - lhs);

	if ( absDiff <= ALQM_SCALAR_EPSILON )
	{
		return ALP_TRUE;
	}

	const ALQM_Scalar absV0 = ALQM_Abs(rhs);
	const ALQM_Scalar absV1 = ALQM_Abs(rhs);

	return absDiff <= ALQM_SCALAR_EPSILON * ALU_MAX(absV0, absV1);
}

ALP_Bool ALQM_ScalarApproximatelyZero(ALQM_Scalar val)
{
	return ALQM_ScalarsApproximatelyEqual(val, 0);
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif // __GNUC__
