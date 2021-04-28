/**
 * About: Bone.h
 * Defines an MDLv10 file bone.
 */

#ifndef AVIDLIB_IO_MDLV10_BONE_H
#define AVIDLIB_IO_MDLV10_BONE_H

#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_QMath/Types.h"
#include "MDLv10/IODefinitions.h"
#include "AVIDLib_Containers/MDLv10/Bone.h"
#include "AVIDLib_Containers/MDLv10/Model.h"

struct _ALIO_MDLv10_Header;

#pragma pack(push, 1)

/**
 * Struct: ALIO_MDLv10_Bone
 * Defines the representation of a bone with an MDLv10 model file.
 */
typedef struct _ALIO_MDLv10_Bone
{
	/**
	 * Variable: name
	 * Name of the bone. Should be unique within the model.
	 */
	ALP_Char name[ALIO_MDLV10_ELEMENT_NAME_LENGTH];

	/**
	 * Variable: parentBoneIndex
	 * Index of the parent bone in the bones chunk,
	 * or -1 if this bone has no parent.
	 */
	ALP_Int32 parentBoneIndex;

	/**
	 * Variable: unused
	 * This was "flags" in the original MDL bone struct,
	 * but appears to be unused.
	 */
	ALP_UInt32 unused;

	/**
	 * Variable: boneControllerIndices
	 * Indices of controllers for this bone's motion types.
	 * -1 indicates that there is no bone controller assigned.
	 */
	ALP_Int32 boneController[ALIO_MDLV10_NUM_MOTION_TYPES];

	/**
	 * Variable: values
	 * Default position and rotation values for this bone, in the following order:
	 *
	 * - X position
	 * - Y position
	 * - Z position
	 * - X rotation
	 * - Y rotation
	 * - Z rotation
	 */
	ALP_Float32 values[ALIO_MDLV10_NUM_MOTION_TYPES];

	/**
	 * Variable: scales
	 * Scale factors for motion that is applied to this bone via animations.
	 * Values are in the following order:
	 *
	 * - X position scale
	 * - Y position scale
	 * - Z position scale
	 * - X rotation scale
	 * - Y rotation scale
	 * - Z rotation scale
	 */
	ALP_Float32 scales[ALIO_MDLV10_NUM_MOTION_TYPES];
} ALIO_MDLv10_Bone;

#pragma pack(pop)

ALP_Bool ALIO_MDLv10_Bone_Validate(const struct _ALIO_MDLv10_Header* header, const ALIO_MDLv10_Bone* bone, ALP_Char* errorString, ALP_Size errorStringSize);
void ALIO_MDLv10_Bone_ToContainerElement(const ALIO_MDLv10_Bone* inBone, ALC_MDLv10_Bone* outBone, ALC_MDLv10_Model* outModel);

static ALP_Bool ALIO_MDLv10_Bone_ValidateGeneric(const struct _ALIO_MDLv10_Header* header, const void* bone, ALP_Char* errorString, ALP_Size errorStringSize)
{
	return ALIO_MDLv10_Bone_Validate(header, (const ALIO_MDLv10_Bone*)bone, errorString, errorStringSize);
}

#endif // AVIDLIB_IO_MDLV10_BONE_H
