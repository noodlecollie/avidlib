#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/Math.h"
#include "AVIDLib_CLib/Ptr.h"
#include "AVIDLib_CLib/Check.h"

const ALQM_Vec3 ALQM_Vec3_Origin = { 0, 0, 0 };

float* ALQM_Vec3_Data(ALQM_Vec3* v)
{
	return ALC_TSANITY_VALID(v, &v->v[0], ALC_NULL);
}

const float* ALQM_Vec3_CData(ALQM_Vec3* v)
{
	return ALC_TSANITY_VALID(v, &v->v[0], ALC_NULL);
}

ALQM_Vec3* ALQM_Vec3_Zero(ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vOut) )
	{
		vOut->v[0] = 0;
		vOut->v[1] = 0;
		vOut->v[2] = 0;
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Copy(const ALQM_Vec3* vIn, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vIn && vOut) )
	{
		vOut->v[0] = vIn->v[0];
		vOut->v[1] = vIn->v[1];
		vOut->v[2] = vIn->v[2];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Add(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vLHS && vRHS && vOut) )
	{
		vOut->v[0] = vLHS->v[0] + vRHS->v[0];
		vOut->v[1] = vLHS->v[1] + vRHS->v[1];
		vOut->v[2] = vLHS->v[2] + vRHS->v[2];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Subtract(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vLHS && vRHS && vOut) )
	{
		vOut->v[0] = vLHS->v[0] - vRHS->v[0];
		vOut->v[1] = vLHS->v[1] - vRHS->v[1];
		vOut->v[2] = vLHS->v[2] - vRHS->v[2];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_CrossProduct(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vLHS && vRHS && vOut) )
	{
		vOut->v[0] = (vLHS->v[1] * vRHS->v[2]) - (vLHS->v[2] * vRHS->v[1]);
		vOut->v[1] = (vLHS->v[2] * vRHS->v[0]) - (vLHS->v[0] * vRHS->v[2]);
		vOut->v[2] = (vLHS->v[0] * vRHS->v[1]) - (vLHS->v[1] * vRHS->v[0]);
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_MultiplyAdd(const ALQM_Vec3* vIn, ALQM_Scalar scale, const ALQM_Vec3* vScaledAdd, ALQM_Vec3* vOut)
{
	if ( ALC_SANITY_VALID(vIn && vScaledAdd && vOut) )
	{
		vOut->v[0] = vIn->v[0] + (scale * vScaledAdd->v[0]);
		vOut->v[1] = vIn->v[1] + (scale * vScaledAdd->v[1]);
		vOut->v[2] = vIn->v[2] + (scale * vScaledAdd->v[2]);
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
		vOut->v[0] = vIn->v[0] * scale;
		vOut->v[1] = vIn->v[1] * scale;
		vOut->v[2] = vIn->v[2] * scale;
	}

	return vOut;
}

ALQM_Scalar ALQM_Vec3_DotProduct(const ALQM_Vec3* v0, const ALQM_Vec3* v1)
{
	return ALC_TSANITY_VALID(v0 && v1,
							 (v0->v[0] * v1->v[0]) + (v0->v[1] * v1->v[1]) + (v0->v[2] * v1->v[2]),
							 0);
}

ALC_Bool ALQM_Vec3_ExactlyEqual(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS)
{
	return ALC_TSANITY_VALID(vLHS && vRHS,
							 vLHS->v[0] == vRHS->v[0] &&
							 vLHS->v[1] == vRHS->v[1] &&
							 vLHS->v[2] == vRHS->v[2],
							 ALC_FALSE);
}

ALC_Bool ALQM_Vec3_ApproximatelyEqual(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS)
{
	return ALC_TSANITY_VALID(vLHS && vRHS,
							 ALQM_ApproxEqual(vLHS->v[0], vRHS->v[0]) &&
							 ALQM_ApproxEqual(vLHS->v[1], vRHS->v[1]) &&
							 ALQM_ApproxEqual(vLHS->v[2], vRHS->v[2]),
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
							 ALQM_Sqrt((v->v[0] * v->v[0]) + (v->v[1] * v->v[1]) + (v->v[2] * v->v[2])),
							 0.0f);
}

ALQM_Scalar ALQM_Vec3_NormaliseAndGetLength(const ALQM_Vec3* vIn, ALQM_Vec3* vOut)
{
	ALQM_Scalar length = 0.0f;

	if ( ALC_SANITY_VALID(vIn && vOut) )
	{
		length = ALQM_Vec3_Length(vIn);

		if ( length != 0.0f )
		{
			const ALQM_Scalar invLength = 1.0f / length;

			vOut->v[0] = vIn->v[0] * invLength;
			vOut->v[1] = vIn->v[1] * invLength;
			vOut->v[2] = vIn->v[2] * invLength;
		}
	}

	return length;
}
