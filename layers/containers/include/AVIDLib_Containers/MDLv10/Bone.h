/**
 * About: Bone.h
 * Defines an MDLv10 bone.
 */

#ifndef AVIDLIB_CONTAINERS_MDLV10_BONE_H
#define AVIDLIB_CONTAINERS_MDLV10_BONE_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Containers/MDLv10/ContainerDefinitions.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_QMath/Vec3.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _ALC_MDLv10_BoneController;

/**
 * Struct: ALC_MDLv10_Bone
 * Defines an MDLv10 bone.
 *
 * Bones create a hierarchy, to which individual transformations
 * are applied to create poses and animations.
 *
 * In addition to being controlled by animations, bones can also
 * be controlled programmatically using bone controllers.
 */
typedef struct _ALC_MDLv10_Bone
{
	/**
	 * Variable: name
	 * Name of this bone. Should be unique within the model.
	 */
	ALP_Char name[ALC_MDLV10_BONE_NAME_LENGTH];

	/**
	 * Variable: refParentBone
	 * Pointer to parent bone, or null if this is a root bone.
	 */
	struct _ALC_MDLv10_Bone* refParentBone;

	/**
	 * Variable: refControllers
	 * Controllers for each motion type, or null for no controller.
	 */
	struct _ALC_MDLv10_BoneController* refControllers[ALC_MDLV10_NUM_MOTION_TYPES];

	/**
	 * Variable: defaultPosition
	 * Default position of this bone in the reference pose.
	 */
	ALQM_Vec3 defaultPosition;

	/**
	 * Variable: defaultRotation
	 * Default rotation of this bone in the reference pose.
	 */
	ALQM_Vec3 defaultRotation;

	/**
	 * Variable: positionScale
	 * Scale for this bone's position, in X, Y, and Z.
	 */
	ALQM_Vec3 positionScale;

	/**
	 * Variable: rotationScale
	 * Scale for this bone's rotation in pitch, yaw, and roll.
	 */
	ALQM_Vec3 rotationScale;
} ALC_MDLv10_Bone;

/**
 * Function: ALC_MDLv10_Bone_Init
 *
 * Initialises a bone from uninitialised memory.
 *
 * This function should always be paired with a later call to <ALC_MDLv10_Bone_Deinit>,
 * to clean up any internal data held by the bone.
 *
 * *Do not* call this function on a bone which has already been initialised,
 * or undefined behaviour will result.
 *
 * Parameters:
 *
 * bone - Bone to initialise.
 *
 * Returns:
 *
 * Input bone.
 */
API_AVIDLIB_CONTAINERS ALC_MDLv10_Bone* ALC_MDLv10_Bone_Init(ALC_MDLv10_Bone* bone);

/**
 * Function: ALC_MDLv10_Bone_Deinit
 *
 * Deinitialises a previously initialised bone.
 *
 * This function should *always* be paired with a previous call to <ALC_MDLv10_Bone_Init>,
 * to clean up any internal data held by the bone.
 *
 * After the call, the bone should not be reused without being initialised again.
 *
 * If the passed bone was not previously initialised using <ALC_MDLv10_Bone_Init>,
 * undefined behaviour will result.
 *
 * Parameters:
 *
 * bone - Bone to deinitialise.
 */
API_AVIDLIB_CONTAINERS void ALC_MDLv10_Bone_Deinit(ALC_MDLv10_Bone* bone);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CONTAINERS_MDLV10_BONE_H
