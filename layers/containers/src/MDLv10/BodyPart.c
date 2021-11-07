#include "AVIDLib_Containers/MDLv10/BodyPart.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Memory.h"

ALC_MDLv10_BodyPart* ALC_MDLv10_BodyPart_Init(ALC_MDLv10_BodyPart* bodyPart)
{
	if ( ALU_SANITY_VALID(bodyPart) )
	{
		ALU_ZERO_STRUCT(bodyPart);
	}

	return bodyPart;
}

void ALC_MDLv10_BodyPart_Deinit(ALC_MDLv10_BodyPart* bodyPart)
{
	// TODO: Deinit all submodels.
	(void)bodyPart;
}
