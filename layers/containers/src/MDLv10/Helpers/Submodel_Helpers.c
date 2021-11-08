#include "MDLv10/Helpers/Submodel_Helpers.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Containers/MDLv10/Submodel.h"

void SubmodelHelpers_GenericInit(void* submodel, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_Submodel_Init((ALC_MDLv10_Submodel*)submodel);
}

void SubmodelHelpers_GenericDeinit(void* submodel, void* data)
{
	ALU_UNUSED(data);
	ALC_MDLv10_Submodel_Deinit((ALC_MDLv10_Submodel*)submodel);
}
