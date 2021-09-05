#include "AVIDLib_QMath/Vec4.h"
#include "AVIDLib_QMath/Math.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Util.h"

const ALQM_Vec4 ALQM_Vec4_Origin = {{ 0, 0, 0, 0 }};

ALQM_Scalar* ALQM_Vec4_Data(ALQM_Vec4* v)
{
	return ALU_TSANITY_VALID(v, &v->v[0], ALP_NULL);
}

const ALQM_Scalar* ALQM_Vec4_CData(const ALQM_Vec4* v)
{
	return ALU_TSANITY_VALID(v, &v->v[0], ALP_NULL);
}

ALQM_Vec4* ALQM_Vec4_Zero(ALQM_Vec4* vOut)
{
	if ( ALU_SANITY_VALID(vOut) )
	{
		vOut->v[ALQM_VEC4X] = 0;
		vOut->v[ALQM_VEC4Y] = 0;
		vOut->v[ALQM_VEC4Z] = 0;
		vOut->v[ALQM_VEC4W] = 0;
	}

	return vOut;
}

ALQM_Vec4* ALQM_Vec4_Copy(const ALQM_Vec4* vIn, ALQM_Vec4* vOut)
{
	if ( ALU_SANITY_VALID(vIn && vOut) && vIn != vOut )
	{
		vOut->v[ALQM_VEC4X] = vIn->v[ALQM_VEC4X];
		vOut->v[ALQM_VEC4Y] = vIn->v[ALQM_VEC4Y];
		vOut->v[ALQM_VEC4Z] = vIn->v[ALQM_VEC4Z];
		vOut->v[ALQM_VEC4W] = vIn->v[ALQM_VEC4W];
	}

	return vOut;
}

ALQM_Vec4* ALQM_Vec4_SetValuesArray(const ALQM_Scalar* values, ALP_Size count, ALQM_Vec4* vOut)
{
	if ( ALU_SANITY_VALID(values && count >= 4 && vOut) )
	{
		vOut->v[ALQM_VEC4X] = values[0];
		vOut->v[ALQM_VEC4Y] = values[1];
		vOut->v[ALQM_VEC4Z] = values[2];
		vOut->v[ALQM_VEC4W] = values[3];
	}

	return vOut;
}

ALQM_Vec4* ALQM_Vec4_Add(const ALQM_Vec4* vLHS, const ALQM_Vec4* vRHS, ALQM_Vec4* vOut)
{
	if ( ALU_SANITY_VALID(vLHS && vRHS && vOut) )
	{
		vOut->v[ALQM_VEC4X] = vLHS->v[ALQM_VEC4X] + vRHS->v[ALQM_VEC4X];
		vOut->v[ALQM_VEC4Y] = vLHS->v[ALQM_VEC4Y] + vRHS->v[ALQM_VEC4Y];
		vOut->v[ALQM_VEC4Z] = vLHS->v[ALQM_VEC4Z] + vRHS->v[ALQM_VEC4Z];
		vOut->v[ALQM_VEC4W] = vLHS->v[ALQM_VEC4W] + vRHS->v[ALQM_VEC4W];
	}

	return vOut;
}

ALQM_Vec4* ALQM_Vec4_Subtract(const ALQM_Vec4* vLHS, const ALQM_Vec4* vRHS, ALQM_Vec4* vOut)
{
	if ( ALU_SANITY_VALID(vLHS && vRHS && vOut) )
	{
		vOut->v[ALQM_VEC4X] = vLHS->v[ALQM_VEC4X] - vRHS->v[ALQM_VEC4X];
		vOut->v[ALQM_VEC4Y] = vLHS->v[ALQM_VEC4Y] - vRHS->v[ALQM_VEC4Y];
		vOut->v[ALQM_VEC4Z] = vLHS->v[ALQM_VEC4Z] - vRHS->v[ALQM_VEC4Z];
		vOut->v[ALQM_VEC4W] = vLHS->v[ALQM_VEC4W] - vRHS->v[ALQM_VEC4W];
	}

	return vOut;
}

ALQM_Vec4* ALQM_Vec4_MultiplyAdd(const ALQM_Vec4* vIn, ALQM_Scalar scale, const ALQM_Vec4* vScaledAdd, ALQM_Vec4* vOut)
{
	if ( ALU_SANITY_VALID(vIn && vScaledAdd && vOut) )
	{
		vOut->v[ALQM_VEC4X] = vIn->v[ALQM_VEC4X] + (scale * vScaledAdd->v[ALQM_VEC4X]);
		vOut->v[ALQM_VEC4Y] = vIn->v[ALQM_VEC4Y] + (scale * vScaledAdd->v[ALQM_VEC4Y]);
		vOut->v[ALQM_VEC4Z] = vIn->v[ALQM_VEC4Z] + (scale * vScaledAdd->v[ALQM_VEC4Z]);
		vOut->v[ALQM_VEC4W] = vIn->v[ALQM_VEC4W] + (scale * vScaledAdd->v[ALQM_VEC4W]);
	}

	return vOut;
}

ALQM_Vec4* ALQM_Vec4_Normalise(const ALQM_Vec4* vIn, ALQM_Vec4* vOut)
{
	if ( ALU_SANITY_VALID(vIn && vOut) )
	{
		ALQM_Vec4_NormaliseAndGetLength(vIn, vOut);
	}

	return vOut;
}

ALQM_Vec4* ALQM_Vec4_Negate(const ALQM_Vec4* vIn, ALQM_Vec4* vOut)
{
	if ( ALU_SANITY_VALID(vIn && vOut) )
	{
		ALQM_Vec4_Scale(vIn, -1, vOut);
	}

	return vOut;
}

ALQM_Vec4* ALQM_Vec4_Scale(const ALQM_Vec4* vIn, ALQM_Scalar scale, ALQM_Vec4* vOut)
{
	if ( ALU_SANITY_VALID(vIn && vOut) )
	{
		vOut->v[ALQM_VEC4X] = vIn->v[ALQM_VEC4X] * scale;
		vOut->v[ALQM_VEC4Y] = vIn->v[ALQM_VEC4Y] * scale;
		vOut->v[ALQM_VEC4Z] = vIn->v[ALQM_VEC4Z] * scale;
		vOut->v[ALQM_VEC4W] = vIn->v[ALQM_VEC4W] * scale;
	}

	return vOut;
}

ALQM_Scalar ALQM_Vec4_DotProduct(const ALQM_Vec4* vLHS, const ALQM_Vec4* vRHS)
{
	return ALU_TSANITY_VALID(vLHS && vRHS,
							 (vLHS->v[ALQM_VEC4X] * vRHS->v[ALQM_VEC4X]) +
							 (vLHS->v[ALQM_VEC4Y] * vRHS->v[ALQM_VEC4Y]) +
							 (vLHS->v[ALQM_VEC4Z] * vRHS->v[ALQM_VEC4Z]) +
							 (vLHS->v[ALQM_VEC4W] * vRHS->v[ALQM_VEC4W]),
							 0);
}

ALP_Bool ALQM_Vec4_ExactlyEqual(const ALQM_Vec4* vLHS, const ALQM_Vec4* vRHS)
{
	return ALU_TSANITY_VALID(vLHS && vRHS,
							 ALQM_ScalarsExactlyEqual(vLHS->v[ALQM_VEC4X], vRHS->v[ALQM_VEC4X]) &&
							 ALQM_ScalarsExactlyEqual(vLHS->v[ALQM_VEC4Y], vRHS->v[ALQM_VEC4Y]) &&
							 ALQM_ScalarsExactlyEqual(vLHS->v[ALQM_VEC4Z], vRHS->v[ALQM_VEC4Z]) &&
							 ALQM_ScalarsExactlyEqual(vLHS->v[ALQM_VEC4W], vRHS->v[ALQM_VEC4W]),
							 ALP_FALSE);
}

ALP_Bool ALQM_Vec4_ApproximatelyEqual(const ALQM_Vec4* vLHS, const ALQM_Vec4* vRHS)
{
	return ALU_TSANITY_VALID(vLHS && vRHS,
							 ALQM_ScalarsApproximatelyEqual(vLHS->v[ALQM_VEC4X], vRHS->v[ALQM_VEC4X]) &&
							 ALQM_ScalarsApproximatelyEqual(vLHS->v[ALQM_VEC4Y], vRHS->v[ALQM_VEC4Y]) &&
							 ALQM_ScalarsApproximatelyEqual(vLHS->v[ALQM_VEC4Z], vRHS->v[ALQM_VEC4Z]) &&
							 ALQM_ScalarsApproximatelyEqual(vLHS->v[ALQM_VEC4W], vRHS->v[ALQM_VEC4W]),
							 ALP_FALSE);
}

ALP_Bool ALQM_Vec4_ExactlyZero(const ALQM_Vec4* v)
{
	return ALU_TSANITY_VALID(v,
							 ALQM_Vec4_ExactlyEqual(v, &ALQM_Vec4_Origin),
							 ALP_FALSE);
}

ALP_Bool ALQM_Vec4_ApproximatelyZero(const ALQM_Vec4* v)
{
	return ALU_TSANITY_VALID(v,
							 ALQM_Vec4_ApproximatelyEqual(v, &ALQM_Vec4_Origin),
							 ALP_FALSE);
}

ALQM_Scalar ALQM_Vec4_Length(const ALQM_Vec4* v)
{
	return ALU_TSANITY_VALID(v,
							 ALQM_Sqrt(ALQM_Vec4_LengthSquared(v)),
							 0.0f);
}

ALQM_Scalar ALQM_Vec4_LengthSquared(const ALQM_Vec4* v)
{
	return ALU_TSANITY_VALID(v,
							 ALQM_Vec4_DotProduct(v, v),
							 0.0f);
}

ALQM_Scalar ALQM_Vec4_NormaliseAndGetLength(const ALQM_Vec4* vIn, ALQM_Vec4* vOut)
{
	ALQM_Scalar length = 0.0f;

	if ( ALU_SANITY_VALID(vIn && vOut) )
	{
		length = ALQM_Vec4_Length(vIn);

		if ( !ALQM_ScalarApproximatelyZero(length) )
		{
			const ALQM_Scalar invLength = 1.0f / length;

			vOut->v[ALQM_VEC4X] = vIn->v[ALQM_VEC4X] * invLength;
			vOut->v[ALQM_VEC4Y] = vIn->v[ALQM_VEC4Y] * invLength;
			vOut->v[ALQM_VEC4Z] = vIn->v[ALQM_VEC4Z] * invLength;
			vOut->v[ALQM_VEC4W] = vIn->v[ALQM_VEC4W] * invLength;
		}
		else
		{
			vOut->v[ALQM_VEC4X] = 0;
			vOut->v[ALQM_VEC4Y] = 0;
			vOut->v[ALQM_VEC4Z] = 0;
			vOut->v[ALQM_VEC4W] = 0;
		}
	}

	return length;
}
