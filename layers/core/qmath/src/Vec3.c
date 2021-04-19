#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/Math.h"
#include "AVIDLib_Core/Ptr.h"
#include "AVIDLib_Core/Check.h"
#include "AVIDLib_Core/Util.h"

const ALQM_Vec3 ALQM_Vec3_Origin = {{ 0, 0, 0 }};

float* ALQM_Vec3_Data(ALQM_Vec3* v)
{
	return ALC_TSANITY_VALID(v, &v->v[0], ALC_NULL);
}

const float* ALQM_Vec3_CData(const ALQM_Vec3* v)
{
	return ALC_TSANITY_VALID(v, &v->v[0], ALC_NULL);
}

ALQM_Vec3* ALQM_Vec3_Zero(ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vOut) )
	{
		vOut->v[ALQM_XAXIS] = 0;
		vOut->v[ALQM_YAXIS] = 0;
		vOut->v[ALQM_ZAXIS] = 0;
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Copy(const ALQM_Vec3* vIn, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vIn && vOut) && vIn != vOut )
	{
		vOut->v[ALQM_XAXIS] = vIn->v[ALQM_XAXIS];
		vOut->v[ALQM_YAXIS] = vIn->v[ALQM_YAXIS];
		vOut->v[ALQM_ZAXIS] = vIn->v[ALQM_ZAXIS];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Set(const float* values, ALC_Size count, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(values && count >= 3 && vOut) )
	{
		vOut->v[ALQM_XAXIS] = values[0];
		vOut->v[ALQM_YAXIS] = values[1];
		vOut->v[ALQM_ZAXIS] = values[2];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Add(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vLHS && vRHS && vOut) )
	{
		vOut->v[ALQM_XAXIS] = vLHS->v[ALQM_XAXIS] + vRHS->v[ALQM_XAXIS];
		vOut->v[ALQM_YAXIS] = vLHS->v[ALQM_YAXIS] + vRHS->v[ALQM_YAXIS];
		vOut->v[ALQM_ZAXIS] = vLHS->v[ALQM_ZAXIS] + vRHS->v[ALQM_ZAXIS];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Subtract(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vLHS && vRHS && vOut) )
	{
		vOut->v[ALQM_XAXIS] = vLHS->v[ALQM_XAXIS] - vRHS->v[ALQM_XAXIS];
		vOut->v[ALQM_YAXIS] = vLHS->v[ALQM_YAXIS] - vRHS->v[ALQM_YAXIS];
		vOut->v[ALQM_ZAXIS] = vLHS->v[ALQM_ZAXIS] - vRHS->v[ALQM_ZAXIS];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_CrossProduct(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vLHS && vRHS && vOut) )
	{
		vOut->v[ALQM_XAXIS] = (vLHS->v[ALQM_YAXIS] * vRHS->v[ALQM_ZAXIS]) - (vLHS->v[ALQM_ZAXIS] * vRHS->v[ALQM_YAXIS]);
		vOut->v[ALQM_YAXIS] = (vLHS->v[ALQM_ZAXIS] * vRHS->v[ALQM_XAXIS]) - (vLHS->v[ALQM_XAXIS] * vRHS->v[ALQM_ZAXIS]);
		vOut->v[ALQM_ZAXIS] = (vLHS->v[ALQM_XAXIS] * vRHS->v[ALQM_YAXIS]) - (vLHS->v[ALQM_YAXIS] * vRHS->v[ALQM_XAXIS]);
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_MultiplyAdd(const ALQM_Vec3* vIn, ALQM_Scalar scale, const ALQM_Vec3* vScaledAdd, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vIn && vScaledAdd && vOut) )
	{
		vOut->v[ALQM_XAXIS] = vIn->v[ALQM_XAXIS] + (scale * vScaledAdd->v[ALQM_XAXIS]);
		vOut->v[ALQM_YAXIS] = vIn->v[ALQM_YAXIS] + (scale * vScaledAdd->v[ALQM_YAXIS]);
		vOut->v[ALQM_ZAXIS] = vIn->v[ALQM_ZAXIS] + (scale * vScaledAdd->v[ALQM_ZAXIS]);
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Normalise(const ALQM_Vec3* vIn, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vIn && vOut) )
	{
		ALQM_Vec3_NormaliseAndGetLength(vIn, vOut);
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Negate(const ALQM_Vec3* vIn, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vIn && vOut) )
	{
		ALQM_Vec3_Scale(vIn, -1, vOut);
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Scale(const ALQM_Vec3* vIn, ALQM_Scalar scale, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vIn && vOut) )
	{
		vOut->v[ALQM_XAXIS] = vIn->v[ALQM_XAXIS] * scale;
		vOut->v[ALQM_YAXIS] = vIn->v[ALQM_YAXIS] * scale;
		vOut->v[ALQM_ZAXIS] = vIn->v[ALQM_ZAXIS] * scale;
	}

	return vOut;
}

ALQM_Scalar ALQM_Vec3_DotProduct(const ALQM_Vec3* v0, const ALQM_Vec3* v1)
{
	return ALC_TSANITY_VALID(v0 && v1,
							 (v0->v[ALQM_XAXIS] * v1->v[ALQM_XAXIS]) + (v0->v[ALQM_YAXIS] * v1->v[ALQM_YAXIS]) + (v0->v[ALQM_ZAXIS] * v1->v[ALQM_ZAXIS]),
							 0);
}

ALC_Bool ALQM_Vec3_ExactlyEqual(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS)
{
	return ALC_TSANITY_VALID(vLHS && vRHS,
							 ALQM_ScalarsExactlyEqual(vLHS->v[ALQM_XAXIS], vRHS->v[ALQM_XAXIS]) &&
							 ALQM_ScalarsExactlyEqual(vLHS->v[ALQM_YAXIS], vRHS->v[ALQM_YAXIS]) &&
							 ALQM_ScalarsExactlyEqual(vLHS->v[ALQM_ZAXIS], vRHS->v[ALQM_ZAXIS]),
							 ALC_FALSE);
}

ALC_Bool ALQM_Vec3_ApproximatelyEqual(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS)
{
	return ALC_TSANITY_VALID(vLHS && vRHS,
							 ALQM_ScalarsApproximatelyEqual(vLHS->v[ALQM_XAXIS], vRHS->v[ALQM_XAXIS]) &&
							 ALQM_ScalarsApproximatelyEqual(vLHS->v[ALQM_YAXIS], vRHS->v[ALQM_YAXIS]) &&
							 ALQM_ScalarsApproximatelyEqual(vLHS->v[ALQM_ZAXIS], vRHS->v[ALQM_ZAXIS]),
							 ALC_FALSE);
}

ALC_Bool ALQM_Vec3_ExactlyZero(const ALQM_Vec3* v)
{
	return ALC_TSANITY_VALID(v,
							 ALQM_Vec3_ExactlyEqual(v, &ALQM_Vec3_Origin),
							 ALC_FALSE);
}

ALC_Bool ALQM_Vec3_ApproximatelyZero(const ALQM_Vec3* v)
{
	return ALC_TSANITY_VALID(v,
							 ALQM_Vec3_ApproximatelyEqual(v, &ALQM_Vec3_Origin),
							 ALC_FALSE);
}

ALQM_Scalar ALQM_Vec3_Length(const ALQM_Vec3* v)
{
	return ALC_TSANITY_VALID(v,
							 ALQM_Sqrt(ALQM_Vec3_DotProduct(v, v)),
							 0.0f);
}

ALQM_Scalar ALQM_Vec3_NormaliseAndGetLength(const ALQM_Vec3* vIn, ALQM_Vec3* vOut)
{
	ALQM_Scalar length = 0.0f;

	if ( ALC_SANITY_VALID(vIn && vOut) )
	{
		length = ALQM_Vec3_Length(vIn);

		if ( !ALQM_ScalarApproximatelyZero(length) )
		{
			const ALQM_Scalar invLength = 1.0f / length;

			vOut->v[ALQM_XAXIS] = vIn->v[ALQM_XAXIS] * invLength;
			vOut->v[ALQM_YAXIS] = vIn->v[ALQM_YAXIS] * invLength;
			vOut->v[ALQM_ZAXIS] = vIn->v[ALQM_ZAXIS] * invLength;
		}
	}

	return length;
}
