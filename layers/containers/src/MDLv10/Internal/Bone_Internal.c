#include "MDLv10/Internal/Bone_Internal.h"
#include "AVIDLib_Internal_Util/Util.h"

void BoneInternal_GenericInit(void* bone, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_Bone_Init((ALC_MDLv10_Bone*)bone);
}

void BoneInternal_GenericDeinit(void* bone, void* data )
{
	ALU_UNUSED(data);
	ALC_MDLv10_Bone_Deinit((ALC_MDLv10_Bone*)bone);
}
