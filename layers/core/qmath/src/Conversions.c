#include "AVIDLib_QMath/Conversions.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_QMath/Math.h"

ALQM_Vec3* ALQM_EulerAngleRadToVec3Fwd(const ALQM_EulerAngle* inAngleRad, ALQM_Vec3* outVecFwd)
{
	if ( ALU_SANITY_VALID(inAngleRad && outVecFwd) )
	{
		ALQM_EulerAngleRadToVec3Basis(inAngleRad, outVecFwd, ALP_NULL, ALP_NULL);
	}

	return outVecFwd;
}

void ALQM_EulerAngleRadToVec3Basis(const ALQM_EulerAngle* inAngleRad, ALQM_Vec3* outVecFwd, ALQM_Vec3* outVecRight, ALQM_Vec3* outVecUp)
{
	if ( ALU_SANITY_VALID(inAngleRad) && ALU_CHECK_VALID(outVecFwd || outVecRight || outVecUp) )
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
			outVecFwd->v[ALQM_VEC3X] = cosPitch * cosYaw;
			outVecFwd->v[ALQM_VEC3Y] = cosPitch * sinYaw;
			outVecFwd->v[ALQM_VEC3Z] = -sinPitch;
		}

		if ( outVecRight )
		{
			outVecRight->v[ALQM_VEC3X] = (-1 * sinRoll * sinPitch * cosYaw) + (-1 * cosRoll * -sinYaw);
			outVecRight->v[ALQM_VEC3Y] = (-1 * sinRoll * sinPitch * sinYaw) + (-1 * cosRoll * cosYaw);
			outVecRight->v[ALQM_VEC3Z] = -1 * sinRoll * cosPitch;
		}

		if ( outVecUp )
		{
			outVecUp->v[ALQM_VEC3X] = (cosRoll * sinPitch * cosYaw) + (-sinRoll * -sinYaw);
			outVecUp->v[ALQM_VEC3Y] = (cosRoll * sinPitch * sinYaw) + (-sinRoll * cosYaw);
			outVecUp->v[ALQM_VEC3Z] = cosRoll * cosPitch;
		}
	}
}

ALQM_EulerAngle* ALQM_Vec3ToEulerAngleRad(const ALQM_Vec3* inVecFwd, ALQM_EulerAngle* outAngleRad)
{
	if ( ALU_SANITY_VALID(inVecFwd && outAngleRad) )
	{
		ALQM_Scalar pitch = 0;
		ALQM_Scalar yaw = 0;

		if ( ALQM_ScalarApproximatelyZero(inVecFwd->v[ALQM_VEC3Y]) && ALQM_ScalarApproximatelyZero(inVecFwd->v[ALQM_VEC3X]) )
		{
			yaw = 0;
			pitch = inVecFwd->v[ALQM_VEC3Z] > 0 ? 270.0f : 90.0f;
		}
		else
		{
			yaw = ALQM_ATan2Rad(inVecFwd->v[ALQM_VEC3Y], inVecFwd->v[ALQM_VEC3X]);

			if ( yaw < 0 )
			{
				yaw += 360;
			}

			const ALQM_Scalar tmp = ALQM_Sqrt((inVecFwd->v[ALQM_VEC3X] * inVecFwd->v[ALQM_VEC3X]) + (inVecFwd->v[ALQM_VEC3Y] * inVecFwd->v[ALQM_VEC3Y]));
			pitch = ALQM_ATan2Rad(-inVecFwd->v[ALQM_VEC3Z], tmp);

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

ALQM_EulerAngle* ALQM_QuatToEulerAngleRad(const ALQM_Quat* inQuat, ALQM_EulerAngle* outAngleRad)
{
	if ( ALU_SANITY_VALID(inQuat && outAngleRad) )
	{
		// TODO: This isn't ideal because it seems like a lot of effort to construct
		// a matrix just to do this. However, Xash3D uses this method and I know that
		// it works, so I guess we'll use it too for now.
		ALQM_Mat3x4 matrix;
		ALQM_Vec3AndQuatToMat3x4(&ALQM_Vec3_Origin, inQuat, &matrix);
		ALQM_Mat3x4ToEulerAngleRad(&matrix, outAngleRad);
	}

	return outAngleRad;
}

ALQM_EulerAngle* ALQM_Mat3x4ToEulerAngleRad(const ALQM_Mat3x4* inMat, ALQM_EulerAngle* outAngleRad)
{
	if ( ALU_SANITY_VALID(inMat && outAngleRad) )
	{
		const ALQM_Scalar xyDist = ALQM_Sqrt((inMat->v[0][0] * inMat->v[0][0]) + (inMat->v[1][0] * inMat->v[1][0]));

		if ( !ALQM_ScalarApproximatelyZero(xyDist) )
		{
			outAngleRad->v[ALQM_PITCH] = ALQM_ATan2Rad(-inMat->v[2][0], xyDist);
			outAngleRad->v[ALQM_YAW] = ALQM_ATan2Rad(inMat->v[1][0], inMat->v[0][0]);
			outAngleRad->v[ALQM_ROLL] = ALQM_ATan2Rad(inMat->v[2][1], inMat->v[2][2]);
		}
		else
		{
			// Forward is mostly Z, gimbal lock.
			outAngleRad->v[ALQM_PITCH] = ALQM_ATan2Rad(-inMat->v[2][0], xyDist);
			outAngleRad->v[ALQM_YAW] = ALQM_ATan2Rad(-inMat->v[0][1], inMat->v[1][1]);
			outAngleRad->v[ALQM_ROLL] = 0;
		}
	}

	return outAngleRad;
}

ALQM_Mat3x4* ALQM_Vec3AndQuatToMat3x4(const ALQM_Vec3* inTranslation, const ALQM_Quat* inQuat, ALQM_Mat3x4* outMat)
{
	if ( ALU_SANITY_VALID(inTranslation && inQuat && outMat) )
	{
		outMat->v[0][0] = 1 - (2 * inQuat->v[ALQM_QUATY] * inQuat->v[ALQM_QUATY]) - (2 * inQuat->v[ALQM_QUATZ] * inQuat->v[ALQM_QUATZ]);
		outMat->v[1][0] = (2 * inQuat->v[ALQM_QUATX] * inQuat->v[ALQM_QUATY]) + (2 * inQuat->v[ALQM_QUATW] * inQuat->v[ALQM_QUATZ]);
		outMat->v[2][0] = (2 * inQuat->v[ALQM_QUATX] * inQuat->v[ALQM_QUATZ]) - (2 * inQuat->v[ALQM_QUATW] * inQuat->v[ALQM_QUATY]);

		outMat->v[0][1] = (2 * inQuat->v[ALQM_QUATX] * inQuat->v[ALQM_QUATY]) - (2 * inQuat->v[ALQM_QUATW] * inQuat->v[ALQM_QUATZ]);
		outMat->v[1][1] = 1 - (2 * inQuat->v[ALQM_QUATX] * inQuat->v[ALQM_QUATX]) - (2 * inQuat->v[ALQM_QUATZ] * inQuat->v[ALQM_QUATZ]);
		outMat->v[2][1] = (2 * inQuat->v[ALQM_QUATY] * inQuat->v[ALQM_QUATZ]) + (2 * inQuat->v[ALQM_QUATW] * inQuat->v[ALQM_QUATX]);

		outMat->v[0][2] = (2 * inQuat->v[ALQM_QUATX] * inQuat->v[ALQM_QUATZ]) + (2 * inQuat->v[ALQM_QUATW] * inQuat->v[ALQM_QUATY]);
		outMat->v[1][2] = (2 * inQuat->v[ALQM_QUATY] * inQuat->v[ALQM_QUATZ]) - (2 * inQuat->v[ALQM_QUATW] * inQuat->v[ALQM_QUATX]);
		outMat->v[2][2] = 1 - (2 * inQuat->v[ALQM_QUATX] * inQuat->v[ALQM_QUATX]) - (2 * inQuat->v[ALQM_QUATY] * inQuat->v[ALQM_QUATY]);

		outMat->v[0][3] = inTranslation->v[ALQM_VEC3X];
		outMat->v[1][3] = inTranslation->v[ALQM_VEC3Y];
		outMat->v[2][3] = inTranslation->v[ALQM_VEC3Z];
	}

	return outMat;
}

ALQM_Quat* ALQM_EulerAngleRadToQuat(const ALQM_EulerAngle* inAngleRad, ALQM_Quat* outQuat)
{
	if ( ALU_SANITY_VALID(inAngleRad && outQuat) )
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
