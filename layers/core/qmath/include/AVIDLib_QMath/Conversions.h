/**
 * About: Conversions.h
 * This file defines functions for conversions between different mathematical types.
 */

#ifndef AVIDLIB_QMATH_CONVERSIONS_H
#define AVIDLIB_QMATH_CONVERSIONS_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/EulerAngle.h"
#include "AVIDLib_QMath/Quat.h"
#include "AVIDLib_QMath/Mat3x4.h"

/**
 * Group: Conversions Producing Vectors
 */

/**
 * Function: ALQM_EulerAngleRadToVec3Fwd
 *
 * Given an Euler angle in radians, provides a vector corresponding to
 * the forward-facing direction of the angle.
 *
 * Parameters:
 *
 * inAngleRad - Input Euler angle, assumed to be specified in radians.
 * outVecFwd  - Output vector that corresponds to the direction that the angle is facing.
 *
 * Returns:
 *
 * outVecFwd.
 */
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_EulerAngleRadToVec3Fwd(const ALQM_EulerAngle* inAngleRad, ALQM_Vec3* outVecFwd);

/**
 * Function: ALQM_EulerAngleRadToVec3Basis
 *
 * Given an Euler angle in radians, provides three perpendicular vectors
 * corresponding to the forward, right, and up directions specified by the angle.
 *
 * Parameters:
 *
 * inAngleRad  - Input Euler angle, assumed to be specified in radians.
 * outVecFwd   - Output vector that corresponds to the direction that the angle is facing.
 * outVecRight - Output vector that corresponds to the right-hand direction, relative to the forward direction.
 * outVecUp    - Output vector that corresponds to the upward direction, relative to the forward and right directions.
 */
API_AVIDLIB_QMATH void ALQM_EulerAngleRadToVec3Basis(const ALQM_EulerAngle* inAngleRad, ALQM_Vec3* outVecFwd, ALQM_Vec3* outVecRight, ALQM_Vec3* outVecUp);

/**
 * Group: Conversions Producing Euler Angles
 */

/**
 * Function: ALQM_Vec3ToEulerAngleRad
 *
 * Given a vector direction, provides an Euler angle representation of this direction.
 * The Euler angle is specified in radians, and the roll component is always zero.
 *
 * Parameters:
 *
 * inVecFwd    - Input vector representing the direction that the angles should face.
 * outAngleRad - Output Euler angle representing this vector, in radians.
 *
 * Returns:
 *
 * outAngleRad.
 */
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_Vec3ToEulerAngleRad(const ALQM_Vec3* inVecFwd, ALQM_EulerAngle* outAngleRad);

/**
 * Function: ALQM_QuatToEulerAngleRad
 *
 * Given a quaternion rotation, provides an Euler angle representation of this rotation.
 * The Euler angle is specified in radians. The identity quaternion produces an Euler
 * angle where pitch, yaw, and roll are all zero.
 *
 * Parameters:
 *
 * inQuat    -   Input quaternion representing the rotation.
 * outAngleRad - Output Euler angle representing this quaternion rotation, in radians.
 *
 * Returns:
 *
 * outAngleRad.
 */
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_QuatToEulerAngleRad(const ALQM_Quat* inQuat, ALQM_EulerAngle* outAngleRad);

/**
 * Function: ALQM_Mat3x4ToEulerAngleRad
 *
 * Given a matrix, provides an Euler angle representation of the matrix's rotation.
 * The translation components of the matrix are ignored.
 * The Euler angle is specified in radians.
 *
 * Parameters:
 *
 * inMat       - Input matrix.
 * outAngleRad - Output Euler angle representing this matrix's rotation, in radians.
 *
 * Returns:
 *
 * outAngleRad.
 */
API_AVIDLIB_QMATH ALQM_EulerAngle* ALQM_Mat3x4ToEulerAngleRad(const ALQM_Mat3x4* inMat, ALQM_EulerAngle* outAngleRad);

/**
 * Group: Conversions Producing Matrices
 */

/**
 * Function: ALQM_Vec3AndQuatToMat3x4
 *
 * Given a vector representing the translation from the origin, and a quaternion representing
 * a rotation, produces a matrix representing these values.
 *
 * Parameters:
 *
 * inTranslation - Input ector representing the matrix's translation components.
 * inQuat        - Input quaternion representing the matrix's rotation components.
 * outMat        - Output matrix that is constructed from these values.
 *
 * Returns:
 *
 * outMat.
 */
API_AVIDLIB_QMATH ALQM_Mat3x4* ALQM_Vec3AndQuatToMat3x4(const ALQM_Vec3* inTranslation, const ALQM_Quat* inQuat, ALQM_Mat3x4* outMat);

/**
 * Group: Conversions Producing Quaternions
 */

/**
 * Function: ALQM_EulerAngleRadToQuat
 *
 * Given an input Euler angle in radians, produces a quaternion representation of this angle's values.
 *
 * Parameters:
 *
 * inAngleRad - Input Euler angle, in radians.
 * outQuat    - Output quaternion representing the Euler angle's rotation.
 *
 * Returns:
 *
 * outQuat.
 */
API_AVIDLIB_QMATH ALQM_Quat* ALQM_EulerAngleRadToQuat(const ALQM_EulerAngle* inAngleRad, ALQM_Quat* outQuat);

#endif // AVIDLIB_QMATH_CONVERSIONS_H
