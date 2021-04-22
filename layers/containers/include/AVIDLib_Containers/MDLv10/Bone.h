#ifndef AVIDLIB_CONTAINERS_MDLV10_BONE_H
#define AVIDLIB_CONTAINERS_MDLV10_BONE_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Containers/MDLv10/Definitions.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_QMath/Vec3.h"

struct _ALC_MDLv10_BoneController;

typedef struct _ALC_MDLv10_Bone
{
	/// Name of this bone. Should be unique within the model.
	ALP_Char name[ALC_MDLV10_ELEMENT_NAME_LENGTH];

	/// Pointer to parent bone, or null if this is a root bone.
	struct _ALC_MDLv10_Bone* parentBone;

	/// Controllers for each motion type, or null for no controller.
	struct _ALC_MDLv10_BoneController* controllers[ALC_MDLV10_NUM_MOTION_TYPES];

	/// Default position of this bone in the reference pose.
	ALQM_Vec3 defaultPosition;

	/// Default rotation of this bone in the reference pose.
	ALQM_Vec3 defaultRotation;

	/// Scale for this bone's position, in X, Y, and Z.
	ALQM_Vec3 positionScale;

	// Scale for this bone's rotation in pitch, yaw, and roll.
	ALQM_Vec3 rotationScale;
} ALC_MDLv10_Bone;

#endif // AVIDLIB_CONTAINERS_MDLV10_BONE_H
