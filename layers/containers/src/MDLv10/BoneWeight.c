#include "AVIDLib_Containers/MDLv10/BoneWeight.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Plat/Ptr.h"

ALC_MDLv10_BoneWeight* ALC_MDLv10_BoneWeight_Reset(ALC_MDLv10_BoneWeight* boneWeight)
{
	if ( ALU_SANITY_VALID(boneWeight) )
	{
		boneWeight->refBone = ALP_NULL;
		boneWeight->weight = 0.0f;
	}

	return boneWeight;
}
