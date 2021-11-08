#include "MDLv10/Helpers/BoneController_Helpers.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Containers/MDLv10/BoneController.h"

void BoneControllerHelpers_GenericInit(void* controller, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_BoneController_Init((ALC_MDLv10_BoneController*)controller);
}

void BoneControllerHelpers_GenericDeinit(void* controller, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_BoneController_Deinit((ALC_MDLv10_BoneController*)controller);
}
