#include "MDLv10/Internal/BoneController_Internal.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Containers/MDLv10/BoneController.h"

void BoneControllerInternal_GenericInit(void* controller, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_BoneController_Init((ALC_MDLv10_BoneController*)controller);
}

void BoneControllerInternal_GenericDeinit(void* controller, void* data )
{
	ALU_UNUSED(data);
	ALC_MDLv10_BoneController_Deinit((ALC_MDLv10_BoneController*)controller);
}
