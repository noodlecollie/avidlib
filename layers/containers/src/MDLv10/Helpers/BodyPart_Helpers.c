#include "MDLv10/Helpers/BodyPart_Helpers.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Containers/MDLv10/BodyPart.h"

void BodyPartHelpers_GenericInit(void* bodyPart, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_BodyPart_Init((ALC_MDLv10_BodyPart*)bodyPart);
}

void BodyPartHelpers_GenericDeinit(void* bodyPart, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_BodyPart_Deinit((ALC_MDLv10_BodyPart*)bodyPart);
}
