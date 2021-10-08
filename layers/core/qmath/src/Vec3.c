#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/Math.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Util.h"

API_AVIDLIB_QMATH const ALQM_Vec3 ALQM_Vec3_Origin = {{ 0, 0, 0 }};

ALQM_Scalar* ALQM_Vec3_Data(ALQM_Vec3* v)
{
	return ALU_TSANITY_VALID(v, &v->v[0], ALP_NULL);
}

const ALQM_Scalar* ALQM_Vec3_CData(const ALQM_Vec3* v)
{
	return ALU_TSANITY_VALID(v, &v->v[0], ALP_NULL);
}

ALQM_Vec3* ALQM_Vec3_Zero(ALQM_Vec3* vOut)
{
	if ( ALU_SANITY_VALID(vOut) )
	{
		vOut->v[ALQM_VEC3X] = 0;
		vOut->v[ALQM_VEC3Y] = 0;
		vOut->v[ALQM_VEC3Z] = 0;
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Copy(const ALQM_Vec3* vIn, ALQM_Vec3* vOut)
{
	if ( ALU_SANITY_VALID(vIn && vOut) && vIn != vOut )
	{
		vOut->v[ALQM_VEC3X] = vIn->v[ALQM_VEC3X];
		vOut->v[ALQM_VEC3Y] = vIn->v[ALQM_VEC3Y];
		vOut->v[ALQM_VEC3Z] = vIn->v[ALQM_VEC3Z];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_SetValuesArray(const ALQM_Scalar* values, ALP_Size count, ALQM_Vec3* vOut)
{
	if ( ALU_SANITY_VALID(values && count >= 3 && vOut) )
	{
		vOut->v[ALQM_VEC3X] = values[0];
		vOut->v[ALQM_VEC3Y] = values[1];
		vOut->v[ALQM_VEC3Z] = values[2];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Add(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut)
{
	if ( ALU_SANITY_VALID(vLHS && vRHS && vOut) )
	{
		vOut->v[ALQM_VEC3X] = vLHS->v[ALQM_VEC3X] + vRHS->v[ALQM_VEC3X];
		vOut->v[ALQM_VEC3Y] = vLHS->v[ALQM_VEC3Y] + vRHS->v[ALQM_VEC3Y];
		vOut->v[ALQM_VEC3Z] = vLHS->v[ALQM_VEC3Z] + vRHS->v[ALQM_VEC3Z];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Subtract(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut)
{
	if ( ALU_SANITY_VALID(vLHS && vRHS && vOut) )
	{
		vOut->v[ALQM_VEC3X] = vLHS->v[ALQM_VEC3X] - vRHS->v[ALQM_VEC3X];
		vOut->v[ALQM_VEC3Y] = vLHS->v[ALQM_VEC3Y] - vRHS->v[ALQM_VEC3Y];
		vOut->v[ALQM_VEC3Z] = vLHS->v[ALQM_VEC3Z] - vRHS->v[ALQM_VEC3Z];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_CrossProduct(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut)
{
	if ( ALU_SANITY_VALID(vLHS && vRHS && vOut) )
	{
		vOut->v[ALQM_VEC3X] = (vLHS->v[ALQM_VEC3Y] * vRHS->v[ALQM_VEC3Z]) - (vLHS->v[ALQM_VEC3Z] * vRHS->v[ALQM_VEC3Y]);
		vOut->v[ALQM_VEC3Y] = (vLHS->v[ALQM_VEC3Z] * vRHS->v[ALQM_VEC3X]) - (vLHS->v[ALQM_VEC3X] * vRHS->v[ALQM_VEC3Z]);
		vOut->v[ALQM_VEC3Z] = (vLHS->v[ALQM_VEC3X] * vRHS->v[ALQM_VEC3Y]) - (vLHS->v[ALQM_VEC3Y] * vRHS->v[ALQM_VEC3X]);
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_MultiplyAdd(const ALQM_Vec3* vIn, ALQM_Scalar scale, const ALQM_Vec3* vScaledAdd, ALQM_Vec3* vOut)
{
	if ( ALU_SANITY_VALID(vIn && vScaledAdd && vOut) )
	{
		vOut->v[ALQM_VEC3X] = vIn->v[ALQM_VEC3X] + (scale * vScaledAdd->v[ALQM_VEC3X]);
		vOut->v[ALQM_VEC3Y] = vIn->v[ALQM_VEC3Y] + (scale * vScaledAdd->v[ALQM_VEC3Y]);
		vOut->v[ALQM_VEC3Z] = vIn->v[ALQM_VEC3Z] + (scale * vScaledAdd->v[ALQM_VEC3Z]);
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Normalise(const ALQM_Vec3* vIn, ALQM_Vec3* vOut)
{
	if ( ALU_SANITY_VALID(vIn && vOut) )
	{
		ALQM_Vec3_NormaliseAndGetLength(vIn, vOut);
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Negate(const ALQM_Vec3* vIn, ALQM_Vec3* vOut)
{
	if ( ALU_SANITY_VALID(vIn && vOut) )
	{
		ALQM_Vec3_Scale(vIn, -1, vOut);
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Scale(const ALQM_Vec3* vIn, ALQM_Scalar scale, ALQM_Vec3* vOut)
{
	if ( ALU_SANITY_VALID(vIn && vOut) )
	{
		vOut->v[ALQM_VEC3X] = vIn->v[ALQM_VEC3X] * scale;
		vOut->v[ALQM_VEC3Y] = vIn->v[ALQM_VEC3Y] * scale;
		vOut->v[ALQM_VEC3Z] = vIn->v[ALQM_VEC3Z] * scale;
	}

	return vOut;
}

ALQM_Scalar ALQM_Vec3_DotProduct(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS)
{
	return ALU_TSANITY_VALID(vLHS && vRHS,
							 (vLHS->v[ALQM_VEC3X] * vRHS->v[ALQM_VEC3X]) +
							 (vLHS->v[ALQM_VEC3Y] * vRHS->v[ALQM_VEC3Y]) +
							 (vLHS->v[ALQM_VEC3Z] * vRHS->v[ALQM_VEC3Z]),
							 0);
}

ALP_Bool ALQM_Vec3_ExactlyEqual(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS)
{
	return ALU_TSANITY_VALID(vLHS && vRHS,
							 ALQM_ScalarsExactlyEqual(vLHS->v[ALQM_VEC3X], vRHS->v[ALQM_VEC3X]) &&
							 ALQM_ScalarsExactlyEqual(vLHS->v[ALQM_VEC3Y], vRHS->v[ALQM_VEC3Y]) &&
							 ALQM_ScalarsExactlyEqual(vLHS->v[ALQM_VEC3Z], vRHS->v[ALQM_VEC3Z]),
							 ALP_FALSE);
}

ALP_Bool ALQM_Vec3_ApproximatelyEqual(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS)
{
	return ALU_TSANITY_VALID(vLHS && vRHS,
							 ALQM_ScalarsApproximatelyEqual(vLHS->v[ALQM_VEC3X], vRHS->v[ALQM_VEC3X]) &&
							 ALQM_ScalarsApproximatelyEqual(vLHS->v[ALQM_VEC3Y], vRHS->v[ALQM_VEC3Y]) &&
							 ALQM_ScalarsApproximatelyEqual(vLHS->v[ALQM_VEC3Z], vRHS->v[ALQM_VEC3Z]),
							 ALP_FALSE);
}

ALP_Bool ALQM_Vec3_ExactlyZero(const ALQM_Vec3* v)
{
	return ALU_TSANITY_VALID(v,
							 ALQM_Vec3_ExactlyEqual(v, &ALQM_Vec3_Origin),
							 ALP_FALSE);
}

ALP_Bool ALQM_Vec3_ApproximatelyZero(const ALQM_Vec3* v)
{
	return ALU_TSANITY_VALID(v,
							 ALQM_Vec3_ApproximatelyEqual(v, &ALQM_Vec3_Origin),
							 ALP_FALSE);
}

ALQM_Scalar ALQM_Vec3_Length(const ALQM_Vec3* v)
{
	return ALU_TSANITY_VALID(v,
							 ALQM_Sqrt(ALQM_Vec3_LengthSquared(v)),
							 0.0f);
}

ALQM_Scalar ALQM_Vec3_LengthSquared(const ALQM_Vec3* v)
{
	return ALU_TSANITY_VALID(v,
							 ALQM_Vec3_DotProduct(v, v),
							 0.0f);
}

ALQM_Scalar ALQM_Vec3_NormaliseAndGetLength(const ALQM_Vec3* vIn, ALQM_Vec3* vOut)
{
	ALQM_Scalar length = 0.0f;

	if ( ALU_SANITY_VALID(vIn && vOut) )
	{
		length = ALQM_Vec3_Length(vIn);

		if ( !ALQM_ScalarApproximatelyZero(length) )
		{
			const ALQM_Scalar invLength = 1.0f / length;

			vOut->v[ALQM_VEC3X] = vIn->v[ALQM_VEC3X] * invLength;
			vOut->v[ALQM_VEC3Y] = vIn->v[ALQM_VEC3Y] * invLength;
			vOut->v[ALQM_VEC3Z] = vIn->v[ALQM_VEC3Z] * invLength;
		}
		else
		{
			vOut->v[ALQM_VEC3X] = 0;
			vOut->v[ALQM_VEC3Y] = 0;
			vOut->v[ALQM_VEC3Z] = 0;
		}
	}

	return length;
}
