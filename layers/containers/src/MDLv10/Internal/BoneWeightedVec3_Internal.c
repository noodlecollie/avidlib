#include "MDLv10/Internal/BoneWeightedVec3_Internal.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Containers/MDLv10/BoneWeightedVec3.h"

void BoneWeightedVec3Internal_GenericInit(void* vec, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_BoneWeightedVec3_Reset((ALC_MDLv10_BoneWeightedVec3*)vec);
}
