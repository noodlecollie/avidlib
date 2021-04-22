#include "AVIDLib_QMath/EulerAngle.h"
#include "AVIDLib_QMath/Math.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Util.h"

static inline ALQM_Scalar ReflectPitch(ALQM_Scalar in, ALQM_Scalar limit)
{
	return in - (2 * (in - limit));
}

ALQM_Scalar* ALQM_EulerAngle_Data(ALQM_EulerAngle* a)
{
	return ALU_TSANITY_VALID(a, &a->v[0], ALP_NULL);
}

const ALQM_Scalar* ALQM_EulerAngle_CData(const ALQM_EulerAngle* a)
{
	return ALU_TSANITY_VALID(a, &a->v[0], ALP_NULL);
}

ALQM_EulerAngle* ALQM_EulerAngle_Zero(ALQM_EulerAngle* aOut)
{
	if ( ALU_SANITY_VALID(aOut) )
	{
		aOut->v[ALQM_PITCH] = 0;
		aOut->v[ALQM_YAW] = 0;
		aOut->v[ALQM_ROLL] = 0;
	}

	return aOut;
}

ALQM_EulerAngle* ALQM_EulerAngle_Copy(const ALQM_EulerAngle* aIn, ALQM_EulerAngle* aOut)
{
	if ( ALU_SANITY_VALID(aIn && aOut) && aIn != aOut )
	{
		aOut->v[ALQM_PITCH] = aIn->v[ALQM_PITCH];
		aOut->v[ALQM_YAW] = aIn->v[ALQM_YAW];
		aOut->v[ALQM_ROLL] = aIn->v[ALQM_ROLL];
	}

	return aOut;
}

ALQM_EulerAngle* ALQM_EulerAngle_DegToRad(const ALQM_EulerAngle* aIn, ALQM_EulerAngle* aOut)
{
	if ( ALU_SANITY_VALID(aIn && aOut) )
	{
		aOut->v[ALQM_PITCH] = ALQM_DegToRad(aIn->v[ALQM_PITCH]);
		aOut->v[ALQM_YAW] = ALQM_DegToRad(aIn->v[ALQM_YAW]);
		aOut->v[ALQM_ROLL] = ALQM_DegToRad(aIn->v[ALQM_ROLL]);
	}

	return aOut;
}

ALQM_EulerAngle* ALQM_EulerAngle_RadToDeg(const ALQM_EulerAngle* aIn, ALQM_EulerAngle* aOut)
{
	if ( ALU_SANITY_VALID(aIn && aOut) )
	{
		aOut->v[ALQM_PITCH] = ALQM_RadToDeg(aIn->v[ALQM_PITCH]);
		aOut->v[ALQM_YAW] = ALQM_RadToDeg(aIn->v[ALQM_YAW]);
		aOut->v[ALQM_ROLL] = ALQM_RadToDeg(aIn->v[ALQM_ROLL]);
	}

	return aOut;
}

ALQM_EulerAngle* ALQM_EulerAngle_Normalise(const ALQM_EulerAngle* aIn, ALQM_EulerAngle* aOut)
{
	if ( ALU_SANITY_VALID(aIn && aOut) )
	{
		aOut->v[ALQM_PITCH] = aIn->v[ALQM_PITCH];
		aOut->v[ALQM_YAW] = aIn->v[ALQM_YAW];
		aOut->v[ALQM_ROLL] = aIn->v[ALQM_ROLL];

		// Make sure pitch is in required range.
		aOut->v[ALQM_PITCH] = ALQM_FMod(aOut->v[ALQM_PITCH] + 180, 360) - 180;

		// If pitch is not facing forward, fix it and invert the yaw.
		if ( aOut->v[ALQM_PITCH] < -90 )
		{
			aOut->v[ALQM_PITCH] = ReflectPitch(aOut->v[ALQM_PITCH], -90);
			aOut->v[ALQM_YAW] += 180;
		}
		else if ( aOut->v[ALQM_PITCH] > 90 )
		{
			aOut->v[ALQM_PITCH] = ReflectPitch(aOut->v[ALQM_PITCH], 90);
			aOut->v[ALQM_YAW] += 180;
		}

		// Clamp pitch to valid range to avoid poles.
		if ( aOut->v[ALQM_PITCH] < -ALQM_EULERANGLE_MAX_PITCH_DELTA )
		{
			aOut->v[ALQM_PITCH] = -ALQM_EULERANGLE_MAX_PITCH_DELTA;
		}
		else if ( aOut->v[ALQM_PITCH] > ALQM_EULERANGLE_MAX_PITCH_DELTA )
		{
			aOut->v[ALQM_PITCH] = ALQM_EULERANGLE_MAX_PITCH_DELTA;
		}

		// Make sure yaw is in required range.
		aOut->v[ALQM_YAW] = ALQM_FMod(aOut->v[ALQM_YAW], 360);

		// Make sure roll is in required range.
		aOut->v[ALQM_ROLL] = ALQM_FMod(aOut->v[ALQM_YAW] + 180, 360) - 180;
	}

	return aOut;
}

ALP_Bool ALQM_EulerAngle_ExactlyEqual(const ALQM_EulerAngle* aLHS, const ALQM_EulerAngle* aRHS)
{
	return ALU_TSANITY_VALID(aLHS && aRHS,
							 ALQM_ScalarsExactlyEqual(aLHS->v[ALQM_PITCH], aRHS->v[ALQM_PITCH]) &&
							 ALQM_ScalarsExactlyEqual(aLHS->v[ALQM_YAW], aRHS->v[ALQM_YAW]) &&
							 ALQM_ScalarsExactlyEqual(aLHS->v[ALQM_ROLL], aRHS->v[ALQM_ROLL]),
							 ALP_FALSE);
}

ALP_Bool ALQM_EulerAngle_ApproximatelyEqual(const ALQM_EulerAngle* aLHS, const ALQM_EulerAngle* aRHS)
{
	return ALU_TSANITY_VALID(aLHS && aRHS,
							 ALQM_ScalarsApproximatelyEqual(aLHS->v[ALQM_PITCH], aRHS->v[ALQM_PITCH]) &&
							 ALQM_ScalarsApproximatelyEqual(aLHS->v[ALQM_YAW], aRHS->v[ALQM_YAW]) &&
							 ALQM_ScalarsApproximatelyEqual(aLHS->v[ALQM_ROLL], aRHS->v[ALQM_ROLL]),
							 ALP_FALSE);
}

ALP_Bool ALQM_EulerAngle_ExactlyZero(const ALQM_EulerAngle* a)
{
	return ALU_TSANITY_VALID(a,
							 ALQM_ScalarExactlyZero(a->v[ALQM_PITCH]) &&
							 ALQM_ScalarExactlyZero(a->v[ALQM_YAW]) &&
							 ALQM_ScalarExactlyZero(a->v[ALQM_ROLL]),
							 ALP_FALSE);
}

ALP_Bool ALQM_EulerAngle_ApproximatelyZero(const ALQM_EulerAngle* a)
{
	return ALU_TSANITY_VALID(a,
							 ALQM_ScalarApproximatelyZero(a->v[ALQM_PITCH]) &&
							 ALQM_ScalarApproximatelyZero(a->v[ALQM_YAW]) &&
							 ALQM_ScalarApproximatelyZero(a->v[ALQM_ROLL]),
							 ALP_FALSE);
}
