#include "MDLv10/Internal/BodyPart_Internal.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Containers/MDLv10/BodyPart.h"

void BodyPartInternal_GenericInit(void* bodyPart, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_BodyPart_Init((ALC_MDLv10_BodyPart*)bodyPart);
}

void BodyPartInternal_GenericDeinit(void* bodyPart, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_BodyPart_Deinit((ALC_MDLv10_BodyPart*)bodyPart);
}
