#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Plat/String.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Containers/MDLv10/BoneController.h"
#include "AVIDLib_Containers/MDLv10/Model.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "MDLv10/IODefinitions.h"
#include "MDLv10/BoneController.h"
#include "MDLv10/Header.h"

ALP_Bool ALIO_MDLv10_BoneController_Validate(const struct _ALIO_MDLv10_Header* header,
                                             ALP_Size fileSize,
                                             const ALIO_MDLv10_BoneController* boneController,
                                             ALP_Char* errorString,
                                             ALP_Size errorStringSize)
{
	ALU_UNUSED(fileSize);

	if ( ALU_SANITY_VALID(header && boneController && errorString && errorStringSize > 0) )
	{
		if ( boneController->boneIndex >= (ALP_UInt32)header->bones.count )
		{
			ALP_StrCpy(errorString, errorStringSize, "Bone index was out of range.");
			return ALP_FALSE;
		}

		if ( boneController->channel >= ALIO_MDLV10_NUM_CONTROLLER_CHANNELS )
		{
			ALP_StrCpy(errorString, errorStringSize, "Channel index was out of range.");
			return ALP_FALSE;
		}

		return ALP_TRUE;
	}

	return ALP_FALSE;
}

ALP_Bool ALIO_MDLv10_BoneController_ValidateGeneric(const struct _ALIO_MDLv10_Header* header,
                                                    ALP_Size fileSize,
                                                    const void* boneController,
                                                    ALP_Char* errorString,
                                                    ALP_Size errorStringSize)
{
	return ALIO_MDLv10_BoneController_Validate(header,
	                                           fileSize,
	                                           (const ALIO_MDLv10_BoneController*)boneController,
	                                           errorString,
	                                           errorStringSize);
}

void ALIO_MDLv10_BoneController_ToContainerElement(const ALIO_MDLv10_BoneController* inController,
                                                   struct _ALC_MDLv10_BoneController* outController,
                                                   struct _ALC_MDLv10_Model* outModel)
{
	if ( ALU_SANITY_VALID(inController && outController && outModel) )
	{
		outController->refBone = &outModel->bones[inController->boneIndex];
		outController->motionType = inController->motionType;
		outController->start = inController->start;
		outController->end = inController->end;

		outController->channel = inController->channel < ALC_MDLV10_NUM_CONTROLLER_CHANNELS
			? inController->channel
			: 0;
	}
}
