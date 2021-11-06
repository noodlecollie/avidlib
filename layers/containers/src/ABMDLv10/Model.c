#include "AVIDLib_Containers/ABMDLv10/Model.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Memory.h"
#include "AVIDLib_Internal_Util/ItemInitialisation.h"
#include "AVIDLib_Plat/Ptr.h"

ALC_ABMDLv10_Model* ALC_ABMDLv10_Model_Init(ALC_ABMDLv10_Model* model)
{
	if ( ALU_SANITY_VALID(model) )
	{
		ALU_ZERO_STRUCT(model);
	}

	return model;
}

void ALC_ABMDLv10_Model_Deinit(ALC_ABMDLv10_Model* model)
{
	// TODO
	(void)model;
}
