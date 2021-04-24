#include "AVIDLib_Containers/MDLv10/Bone.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Internal_Util/ItemInitialisation.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Memory.h"
#include "Internal/Bone_Internal.h"

ALC_MDLv10_Bone* ALC_MDLv10_Bone_Init(ALC_MDLv10_Bone* bone)
{
	if ( ALU_SANITY_VALID(bone) )
	{
		ALU_ZERO_STRUCT(bone);
	}

	return bone;
}

void ALC_MDLv10_Bone_Deinit(ALC_MDLv10_Bone* bone)
{
	// Nothing to do.
	ALU_UNUSED(bone);
}
