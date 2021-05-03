#include "AVIDLib_Containers/MDLv10/Model.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Memory.h"
#include "AVIDLib_Internal_Util/ItemInitialisation.h"
#include "AVIDLib_Plat/Ptr.h"
#include "MDLv10/Internal/Bone_Internal.h"
#include "MDLv10/Internal/BoneController_Internal.h"

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
	}
}

ALC_MDLv10_Bone* ALC_MDLv10_Model_AllocateBones(ALC_MDLv10_Model* model, ALP_Size numBones)
{
	return ALU_TSANITY_VALID(
		model,
		(ALC_MDLv10_Bone*)ALU_SetArrayOfItems(
			(void**)&model->bones,
			&model->numBones,
			numBones,
			sizeof(*model->bones),
			&BoneInternal_GenericInit,
			ALP_NULL,
			&BoneInternal_GenericDeinit,
			ALP_NULL),
		ALP_NULL);
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
	return ALU_TSANITY_VALID(
		model,
		(ALC_MDLv10_BoneController*)ALU_SetArrayOfItems(
			(void**)&model->boneControllers,
			&model->numBoneControllers,
			numBoneControllers,
			sizeof(*model->boneControllers),
			&BoneControllerInternal_GenericInit,
			ALP_NULL,
			&BoneControllerInternal_GenericDeinit,
			ALP_NULL),
		ALP_NULL);
}

void ALC_MDLv10_Model_FreeBoneControllers(ALC_MDLv10_Model* model)
{
	if ( ALU_SANITY_VALID(model) )
	{
		ALC_MDLv10_Model_AllocateBoneControllers(model, 0);
	}
}
