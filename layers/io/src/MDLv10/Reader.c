#include "AVIDLib_IO/MDLv10/Reader.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_Plat/Ptr.h"

ALP_Bool ALIO_MDLv10_Read(ALIO_ReadContext* context, ALC_MDLv10_Model* outModel)
{
	if ( ALU_SANITY_VALID(context && outModel) )
	{
		// TODO: Implement properly.
		// Return an unimplemented error for now.
		ALU_UNUSED(outModel);

		ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_UNIMPLEMENTED, ALP_NULL);
		return ALP_FALSE;
	}

	return ALP_FALSE;
}
