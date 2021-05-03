#include "AVIDLib_Containers/MDLv10/BoneController.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Memory.h"

ALC_MDLv10_BoneController* ALC_MDLv10_BoneController_Init(ALC_MDLv10_BoneController* controller)
{
	if ( ALU_SANITY_VALID(controller) )
	{
		ALU_ZERO_STRUCT(controller);
	}

	return controller;
}

void ALC_MDLv10_BoneController_Deinit(ALC_MDLv10_BoneController* controller)
{
	// Nothing to do.
	ALU_UNUSED(controller);
}
