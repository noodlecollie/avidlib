#include "AVIDLib_Containers/MDLv10/Submodel.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Memory.h"
#include "AVIDLib_Internal_Util/Util.h"

ALC_MDLv10_Submodel* ALC_MDLv10_Submodel_Init(ALC_MDLv10_Submodel* submodel)
{
	if ( ALU_SANITY_VALID(submodel) )
	{
		ALU_ZERO_STRUCT(submodel);
	}

	return submodel;
}

void ALC_MDLv10_Submodel_Deinit(ALC_MDLv10_Submodel* submodel)
{
	// TODO
	ALU_UNUSED(submodel);
}
