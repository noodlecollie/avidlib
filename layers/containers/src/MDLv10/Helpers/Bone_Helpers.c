#include "MDLv10/Helpers/Bone_Helpers.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Containers/MDLv10/Bone.h"

void BoneHelpers_GenericInit(void* bone, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_Bone_Init((ALC_MDLv10_Bone*)bone);
}

void BoneHelpers_GenericDeinit(void* bone, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_Bone_Deinit((ALC_MDLv10_Bone*)bone);
}
