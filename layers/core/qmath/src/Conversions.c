#include "AVIDLib_QMath/Conversions.h"
#include "AVIDLib_Plat/Check.h"
#include "AVIDLib_QMath/Math.h"
#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/EulerAngle.h"
#include "AVIDLib_QMath/Quat.h"

void ALQM_EulerAngleRadToVec3(const ALQM_EulerAngle* inAngleRad, ALQM_Vec3* outVecFwd, ALQM_Vec3* outVecRight, ALQM_Vec3* outVecUp)
{
	if ( ALP_SANITY_VALID(inAngleRad) && ALP_CHECK_VALID(outVecFwd || outVecRight || outVecUp) )
	{
		ALQM_Scalar sinPitch = 0;
		ALQM_Scalar cosPitch = 0;
		ALQM_Scalar sinYaw = 0;
		ALQM_Scalar cosYaw = 0;
		ALQM_Scalar sinRoll = 0;
		ALQM_Scalar cosRoll = 0;

		ALQM_SinCosRad(inAngleRad->v[ALQM_PITCH], &sinPitch, &cosPitch);
		ALQM_SinCosRad(inAngleRad->v[ALQM_YAW], &sinYaw, &cosYaw);
		ALQM_SinCosRad(inAngleRad->v[ALQM_ROLL], &sinRoll, &cosRoll);

		if ( outVecFwd )
		{
			outVecFwd->v[ALQM_VECX] = cosPitch * cosYaw;
			outVecFwd->v[ALQM_VECY] = cosPitch * sinYaw;
			outVecFwd->v[ALQM_VECZ] = -sinPitch;
		}

		if ( outVecRight )
		{
			outVecRight->v[ALQM_VECX] = (-1 * sinRoll * sinPitch * cosYaw) + (-1 * cosRoll * -sinYaw);
			outVecRight->v[ALQM_VECY] = (-1 * sinRoll * sinPitch * sinYaw) + (-1 * cosRoll * cosYaw);
			outVecRight->v[ALQM_VECZ] = -1 * sinRoll * cosPitch;
		}

		if ( outVecUp )
		{
			outVecUp->v[ALQM_VECX] = (cosRoll * sinPitch * cosYaw) + (-sinRoll * -sinYaw);
			outVecUp->v[ALQM_VECY] = (cosRoll * sinPitch * sinYaw) + (-sinRoll * cosYaw);
			outVecUp->v[ALQM_VECZ] = cosRoll * cosPitch;
		}
	}
}

ALQM_EulerAngle* ALQM_Vec3ToEulerAngleRad(const ALQM_Vec3* inVecFwd, ALQM_EulerAngle* outAngleRad)
{
	if ( ALP_SANITY_VALID(inVecFwd && outAngleRad) )
	{
		ALQM_Scalar pitch = 0;
		ALQM_Scalar yaw = 0;

		if ( ALQM_ScalarApproximatelyZero(inVecFwd->v[ALQM_VECY]) && ALQM_ScalarApproximatelyZero(inVecFwd->v[ALQM_VECX]) )
		{
			yaw = 0;
			pitch = inVecFwd->v[ALQM_VECZ] > 0 ? 270.0f : 90.0f;
		}
		else
		{
			yaw = ALQM_ATan2Rad(inVecFwd->v[ALQM_VECY], inVecFwd->v[ALQM_VECX]);

			if ( yaw < 0 )
			{
				yaw += 360;
			}

			const ALQM_Scalar tmp = ALQM_Sqrt((inVecFwd->v[ALQM_VECX] * inVecFwd->v[ALQM_VECX]) + (inVecFwd->v[ALQM_VECY] * inVecFwd->v[ALQM_VECY]));
			pitch = ALQM_ATan2Rad(-inVecFwd->v[ALQM_VECZ], tmp);

			if ( pitch < 0 )
			{
				pitch += 360;
			}
		}

		outAngleRad->v[ALQM_PITCH] = pitch;
		outAngleRad->v[ALQM_YAW] = yaw;
		outAngleRad->v[ALQM_ROLL] = 0;
	}

	return outAngleRad;
}

ALQM_Quat* ALQM_EulerAngleRadToQuat(const ALQM_EulerAngle* inAngleRad, ALQM_Quat* outQuat)
{
	if ( ALP_SANITY_VALID(inAngleRad && outQuat) )
	{
		ALQM_Scalar sinPitch = 0;
		ALQM_Scalar cosPitch = 0;
		ALQM_Scalar sinYaw = 0;
		ALQM_Scalar cosYaw = 0;
		ALQM_Scalar sinRoll = 0;
		ALQM_Scalar cosRoll = 0;

		ALQM_SinCosRad(inAngleRad->v[ALQM_PITCH], &sinPitch, &cosPitch);
		ALQM_SinCosRad(inAngleRad->v[ALQM_YAW], &sinYaw, &cosYaw);
		ALQM_SinCosRad(inAngleRad->v[ALQM_ROLL], &sinRoll, &cosRoll);

		outQuat->v[ALQM_QUATX] = (sinRoll * cosPitch * cosYaw) - (cosRoll * sinPitch * sinYaw);
		outQuat->v[ALQM_QUATY] = (cosRoll * sinPitch * cosYaw) + (sinRoll * cosPitch * sinYaw);
		outQuat->v[ALQM_QUATZ] = (cosRoll * cosPitch * sinYaw) - (sinRoll * sinPitch * cosYaw);
		outQuat->v[ALQM_QUATW] = (cosRoll * cosPitch * cosYaw) + (sinRoll * sinPitch * sinYaw);
	}

	return outQuat;
}

ALQM_EulerAngle* ALQM_QuatToEulerAngleRad(const ALQM_Quat* inQuat, ALQM_EulerAngle* outAngleRad)
{
	if ( ALP_SANITY_VALID(inQuat && outAngleRad) )
	{
		outAngleRad->v[ALQM_PITCH] = ALQM_ATan2Rad(2 * ((inQuat->v[ALQM_QUATY] * inQuat->v[ALQM_QUATZ]) + (inQuat->v[ALQM_QUATW] * inQuat->v[ALQM_QUATX])),
												   (inQuat->v[ALQM_QUATW] * inQuat->v[ALQM_QUATW]) -
												   (inQuat->v[ALQM_QUATX] * inQuat->v[ALQM_QUATX]) -
												   (inQuat->v[ALQM_QUATY] * inQuat->v[ALQM_QUATY]) +
												   (inQuat->v[ALQM_QUATZ] * inQuat->v[ALQM_QUATZ]));

		outAngleRad->v[ALQM_YAW] = ALQM_ASinRad(-2 * ((inQuat->v[ALQM_QUATX] * inQuat->v[ALQM_QUATZ]) - (inQuat->v[ALQM_QUATW] * inQuat->v[ALQM_QUATY])));

		outAngleRad->v[ALQM_ROLL] = ALQM_ATan2Rad(2 * ((inQuat->v[ALQM_QUATX] * inQuat->v[ALQM_QUATY]) + (inQuat->v[ALQM_QUATW] * inQuat->v[ALQM_QUATZ])),
												  (inQuat->v[ALQM_QUATW] * inQuat->v[ALQM_QUATW]) +
												  (inQuat->v[ALQM_QUATX] * inQuat->v[ALQM_QUATX]) -
												  (inQuat->v[ALQM_QUATY] * inQuat->v[ALQM_QUATY]) -
												  (inQuat->v[ALQM_QUATZ] * inQuat->v[ALQM_QUATZ]));
	}

	return outAngleRad;
}
