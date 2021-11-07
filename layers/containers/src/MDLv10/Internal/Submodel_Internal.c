#include "MDLv10/Internal/Submodel_Internal.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Containers/MDLv10/Submodel.h"

void SubmodelInternal_GenericInit(void* submodel, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_Submodel_Init((ALC_MDLv10_Submodel*)submodel);
}

void SubmodelInternal_GenericDeinit(void* submodel, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_Submodel_Deinit((ALC_MDLv10_Submodel*)submodel);
}
