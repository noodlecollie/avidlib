#include "AVIDLib_QMath/Conversions.h"
#include "AVIDLib_Core/Check.h"
#include "AVIDLib_QMath/Math.h"

void EulerAngleToVec3(const ALQM_EulerAngle* angle, ALQM_Vec3* vecFwd, ALQM_Vec3* vecRight, ALQM_Vec3* vecUp)
{
	if ( ALC_SANITY_VALID(angle) && ALC_CHECK_VALID(vecFwd || vecRight || vecUp) )
	{
		float sinPitch = 0;
		float cosPitch = 0;
		float sinYaw = 0;
		float cosYaw = 0;
		float sinRoll = 0;
		float cosRoll = 0;

		{
			const float angleRad = ALQM_DegToRad(angle->v[ALQM_PITCH]);
			sinPitch = ALQM_SinRad(angleRad);
			cosPitch = ALQM_CosRad(angleRad);
		}

		{
			const float angleRad = ALQM_DegToRad(angle->v[ALQM_YAW]);
			sinYaw = ALQM_SinRad(angleRad);
			cosYaw = ALQM_CosRad(angleRad);
		}

		{
			const float angleRad = ALQM_DegToRad(angle->v[ALQM_ROLL]);
			sinRoll = ALQM_SinRad(angleRad);
			cosRoll = ALQM_CosRad(angleRad);
		}

		if ( vecFwd )
		{
			vecFwd->v[ALQM_XAXIS] = cosPitch * cosYaw;
			vecFwd->v[ALQM_YAXIS] = cosPitch * sinYaw;
			vecFwd->v[ALQM_ZAXIS] = -sinPitch;
		}

		if ( vecRight )
		{
			vecRight->v[ALQM_XAXIS] = (-1 * sinRoll * sinPitch * cosYaw) + (-1 * cosRoll * -sinYaw);
			vecRight->v[ALQM_YAXIS] = (-1 * sinRoll * sinPitch * sinYaw) + (-1 * cosRoll * cosYaw);
			vecRight->v[ALQM_ZAXIS] = -1 * sinRoll * cosPitch;
		}

		if ( vecUp )
		{
			vecUp->v[ALQM_XAXIS] = (cosRoll * sinPitch * cosYaw) + (-sinRoll * -sinYaw);
			vecUp->v[ALQM_YAXIS] = (cosRoll * sinPitch * sinYaw) + (-sinRoll * cosYaw);
			vecUp->v[ALQM_ZAXIS] = cosRoll * cosPitch;
		}
	}
}

void Vec3ToEulerAngle(const ALQM_Vec3* vecFwd, ALQM_EulerAngle* angle)
{
	if ( ALC_SANITY_VALID(vecFwd && angle) )
	{
		float pitch = 0;
		float yaw = 0;

		if ( ALQM_ScalarApproximatelyZero(vecFwd->v[ALQM_YAXIS]) && ALQM_ScalarApproximatelyZero(vecFwd->v[ALQM_XAXIS]) )
		{
			yaw = 0;
			pitch = vecFwd->v[ALQM_ZAXIS] > 0 ? 270.0f : 90.0f;
		}
		else
		{
			yaw = ALQM_ATan2Deg(vecFwd->v[ALQM_YAXIS], vecFwd->v[ALQM_XAXIS]);

			if ( yaw < 0 )
			{
				yaw += 360;
			}

			const float tmp = ALQM_Sqrt((vecFwd->v[ALQM_XAXIS] * vecFwd->v[ALQM_XAXIS]) + (vecFwd->v[ALQM_YAXIS] * vecFwd->v[ALQM_YAXIS]));
			pitch = ALQM_ATan2Deg(-vecFwd->v[ALQM_ZAXIS], tmp);

			if ( pitch < 0 )
			{
				pitch += 360;
			}
		}

		angle->v[ALQM_PITCH] = pitch;
		angle->v[ALQM_YAW] = yaw;
		angle->v[ALQM_ROLL] = 0;
	}
}
