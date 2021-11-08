#include "AVIDLib_Containers/MDLv10/BoneWeightedVec3.h"
#include "AVIDLib_Containers/MDLv10/BoneWeight.h"
#include "AVIDLib_Internal_Util/Check.h"

ALC_MDLv10_BoneWeightedVec3* ALC_MDLv10_BoneWeightedVec3_Reset(ALC_MDLv10_BoneWeightedVec3* vec)
{
	if ( ALU_SANITY_VALID(vec) )
	{
		ALQM_Vec3_Zero(&vec->vec);

		for ( ALP_Size index = 0; index < ALC_MDLV10_MAX_VERT_BONE_WEIGHTS; ++index )
		{
			ALC_MDLv10_BoneWeight_Reset(&vec->boneWeights[index]);
		}
	}

	return vec;
}
