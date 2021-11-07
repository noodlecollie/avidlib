#include "AVIDLib_Containers/MDLv10/BodyPart.h"
#include "AVIDLib_Containers/MDLv10/Submodel.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Memory.h"
#include "AVIDLib_Internal_Util/ItemInitialisation.h"
#include "AVIDLib_Plat/Ptr.h"
#include "Internal/Submodel_Internal.h"

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
	if ( ALU_SANITY_VALID(bodyPart) )
	{
		ALC_MDLv10_BodyPart_FreeSubmodels(bodyPart);
	}
}

ALC_MDLv10_Submodel* ALC_MDLv10_BodyPart_AllocateSubmodels(ALC_MDLv10_BodyPart* bodyPart, ALP_Size numSubmodels)
{
	ALC_MDLv10_Submodel* out = ALP_NULL;

	if ( ALU_SANITY_VALID(bodyPart) )
	{
		out = (ALC_MDLv10_Submodel*)ALU_SetArrayOfItems(
			(void**)&bodyPart->submodels,
			&bodyPart->numSubmodels,
			numSubmodels,
			sizeof(*bodyPart->submodels),
			&SubmodelInternal_GenericInit,
			ALP_NULL,
			&SubmodelInternal_GenericDeinit,
			ALP_NULL);
	}

	return out;
}

void ALC_MDLv10_BodyPart_FreeSubmodels(ALC_MDLv10_BodyPart* bodyPart)
{
	if ( ALU_SANITY_VALID(bodyPart) )
	{
		ALC_MDLv10_BodyPart_AllocateSubmodels(bodyPart, 0);
	}
}
