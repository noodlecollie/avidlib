#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_CLib/Ptr.h"
#include "AVIDLib_CLib/Check.h"

const ALQM_Vec3 ALQM_Vec3_Origin = { 0, 0, 0 };

float* ALQM_Vec3_Data(ALQM_Vec3* v)
{
	return ALC_RET_VALID(v, &v->v[0], ALC_NULL);
}

const float* ALQM_Vec3_CData(ALQM_Vec3* v)
{
	return ALC_RET_VALID(v, &v->v[0], ALC_NULL);
}

ALQM_Vec3* ALQM_Vec3_Zero(ALQM_Vec3* vOut)
{
	ALC_IF_VALID( vOut )
	{
		vOut->v[0] = 0;
		vOut->v[1] = 0;
		vOut->v[2] = 0;
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Copy(const ALQM_Vec3* vIn, ALQM_Vec3* vOut)
{
	ALC_IF_VALID( vIn && vOut )
	{
		vOut->v[0] = vIn->v[0];
		vOut->v[1] = vIn->v[1];
		vOut->v[2] = vIn->v[2];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Add(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut)
{
	ALC_IF_VALID( vOut && vLHS && vRHS )
	{
		vOut->v[0] = vLHS->v[0] + vRHS->v[0];
		vOut->v[1] = vLHS->v[1] + vRHS->v[1];
		vOut->v[2] = vLHS->v[2] + vRHS->v[2];
	}

	return vOut;
}

ALQM_Vec3* ALQM_Vec3_Subtract(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut)
{
	ALC_IF_VALID( vOut && vLHS && vRHS )
	{
		vOut->v[0] = vLHS->v[0] - vRHS->v[0];
		vOut->v[1] = vLHS->v[1] - vRHS->v[1];
		vOut->v[2] = vLHS->v[2] - vRHS->v[2];
	}

	return vOut;
}

ALQM_Vec3* ALQM_CrossProduct(const ALQM_Vec3* vLHS, const ALQM_Vec3* vRHS, ALQM_Vec3* vOut)
{
	ALC_IF_VALID( vOut && vLHS && vRHS )
	{
		vOut->v[0] = (vLHS->v[1] * vRHS->v[2]) - (vLHS->v[2]*vRHS->v[1]);
		vOut->v[1] = (vLHS->v[2] * vRHS->v[0]) - (vLHS->v[0]*vRHS->v[2]);
		vOut->v[2] = (vLHS->v[0] * vRHS->v[1]) - (vLHS->v[1]*vRHS->v[0]);
	}

	return vOut;
}

ALQM_Scalar ALQM_Vec3_DotProduct(const ALQM_Vec3* v0, const ALQM_Vec3* v1)
{
	return ALC_RET_VALID(v0 && v1,
						 (v0->v[0] * v1->v[0]) + (v0->v[1] * v1->v[1]) + (v0->v[2] * v1->v[2]),
						 0);
}
