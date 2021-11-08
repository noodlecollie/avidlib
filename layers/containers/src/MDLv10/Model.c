#include "AVIDLib_Containers/MDLv10/Model.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Memory.h"
#include "AVIDLib_Internal_Util/ItemInitialisation.h"
#include "AVIDLib_Plat/Ptr.h"
#include "MDLv10/Helpers/Bone_Helpers.h"
#include "MDLv10/Helpers/BoneController_Helpers.h"
#include "MDLv10/Helpers/BodyPart_Helpers.h"

ALC_MDLv10_Model* ALC_MDLv10_Model_Init(ALC_MDLv10_Model* model)
{
	if ( ALU_SANITY_VALID(model) )
	{
		ALU_ZERO_STRUCT(model);
	}

	return model;
}

void ALC_MDLv10_Model_Deinit(ALC_MDLv10_Model* model)
{
	if ( ALU_SANITY_VALID(model) )
	{
		ALC_MDLv10_Model_FreeBones(model);
		ALC_MDLv10_Model_FreeBoneControllers(model);
		ALC_MDLv10_Model_FreeBodyParts(model);
	}
}

ALC_MDLv10_Bone* ALC_MDLv10_Model_AllocateBones(ALC_MDLv10_Model* model, ALP_Size numBones)
{
	ALC_MDLv10_Bone* out = ALP_NULL;

	if ( ALU_SANITY_VALID(model) )
	{
		out = (ALC_MDLv10_Bone*)ALU_SetArrayOfItems(
			(void**)&model->bones,
			&model->numBones,
			numBones,
			sizeof(*model->bones),
			&BoneHelpers_GenericInit,
			ALP_NULL,
			&BoneHelpers_GenericDeinit,
			ALP_NULL);
	}

	return out;
}

void ALC_MDLv10_Model_FreeBones(ALC_MDLv10_Model* model)
{
	if ( ALU_SANITY_VALID(model) )
	{
		ALC_MDLv10_Model_AllocateBones(model, 0);
	}
}

ALC_MDLv10_BoneController* ALC_MDLv10_Model_AllocateBoneControllers(ALC_MDLv10_Model* model, ALP_Size numBoneControllers)
{
	ALC_MDLv10_BoneController* out = ALP_NULL;

	if ( ALU_SANITY_VALID(model) )
	{
		out = (ALC_MDLv10_BoneController*)ALU_SetArrayOfItems(
			(void**)&model->boneControllers,
			&model->numBoneControllers,
			numBoneControllers,
			sizeof(*model->boneControllers),
			&BoneControllerHelpers_GenericInit,
			ALP_NULL,
			&BoneControllerHelpers_GenericDeinit,
			ALP_NULL);
	}

	return out;
}

void ALC_MDLv10_Model_FreeBoneControllers(ALC_MDLv10_Model* model)
{
	if ( ALU_SANITY_VALID(model) )
	{
		ALC_MDLv10_Model_AllocateBoneControllers(model, 0);
	}
}

ALC_MDLv10_BodyPart* ALC_MDLv10_Model_AllocateBodyParts(ALC_MDLv10_Model* model, ALP_Size numBodyParts)
{
	ALC_MDLv10_BodyPart* out = ALP_NULL;

	if ( ALU_SANITY_VALID(model) )
	{
		out = (ALC_MDLv10_BodyPart*)ALU_SetArrayOfItems(
			(void**)&model->bodyParts,
			&model->numBodyParts,
			numBodyParts,
			sizeof(*model->bodyParts),
			&BodyPartHelpers_GenericInit,
			ALP_NULL,
			&BodyPartHelpers_GenericDeinit,
			ALP_NULL);
	}

	return out;
}

void ALC_MDLv10_Model_FreeBodyParts(ALC_MDLv10_Model* model)
{
	if ( ALU_SANITY_VALID(model) )
	{
		ALC_MDLv10_Model_AllocateBodyParts(model, 0);
	}
}
