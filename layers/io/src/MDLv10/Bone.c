#include "MDLv10/Bone.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Plat/String.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_IO/ReadContext.h"
#include "MDLv10/Header.h"

ALP_Bool ALIO_MDLv10_Bone_Validate(const struct _ALIO_MDLv10_Header* header, const ALIO_MDLv10_Bone* bone, ALP_Char* errorString, ALP_Size errorStringSize)
{
	if ( ALU_SANITY_VALID(header && bone && errorString && errorStringSize > 0) )
	{
		if ( bone->parentBoneIndex >= 0 && (ALP_UInt32)bone->parentBoneIndex >= header->bones.count )
		{
			ALP_StrCpy(errorString, errorStringSize, "Parent bone index was out of range.");
			return ALP_FALSE;
		}

		for ( ALP_Size index = 0; index < ALIO_MDLV10_NUM_MOTION_TYPES; ++index )
		{
			if ( bone->boneController[index] >= 0 && (ALP_UInt32)bone->boneController[index] >= header->boneControllers.count )
			{
				ALP_StrCpy(errorString, errorStringSize, "Bone controller index was out of range.");
				return ALP_FALSE;
			}
		}

		return ALP_TRUE;
	}

	return ALP_FALSE;
}

void ALIO_MDLv10_Bone_ToContainerElement(const ALIO_MDLv10_Bone* inBone, ALC_MDLv10_Bone* outBone, ALC_MDLv10_Model* outModel)
{
	if ( ALU_SANITY_VALID(inBone && outBone && outModel) )
	{
		ALP_StrCpy(outBone->name, sizeof(outBone->name), inBone->name);

		outBone->refParentBone = inBone->parentBoneIndex >= 0
			? &outModel->bones[inBone->parentBoneIndex]
			: ALP_NULL;

		// TODO: Add bone controller links once we set them up.

		outBone->defaultPosition.v[ALQM_VECX] = inBone->values[0];
		outBone->defaultPosition.v[ALQM_VECY] = inBone->values[1];
		outBone->defaultPosition.v[ALQM_VECZ] = inBone->values[2];

		outBone->defaultRotation.v[ALQM_VECX] = inBone->values[3];
		outBone->defaultRotation.v[ALQM_VECY] = inBone->values[4];
		outBone->defaultRotation.v[ALQM_VECZ] = inBone->values[5];

		outBone->positionScale.v[ALQM_VECX] = inBone->scales[0];
		outBone->positionScale.v[ALQM_VECY] = inBone->scales[1];
		outBone->positionScale.v[ALQM_VECZ] = inBone->scales[2];

		outBone->rotationScale.v[ALQM_VECX] = inBone->scales[3];
		outBone->rotationScale.v[ALQM_VECY] = inBone->scales[4];
		outBone->rotationScale.v[ALQM_VECZ] = inBone->scales[5];
	}
}