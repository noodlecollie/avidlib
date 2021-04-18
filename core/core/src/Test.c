#include "AVIDLib_Core/Test.h"
#include "AVIDLib_QMath/Vec3.h"

ALQM_Scalar ALC_Test()
{
	ALQM_Vec3 v0;

	ALQM_Vec3_Zero(&v0);
	v0.v[1] = 12;

	const ALQM_Vec3 v1 = {{ 1, 2, 3 }};

	return ALQM_Vec3_DotProduct(&v0, &v1);
}
