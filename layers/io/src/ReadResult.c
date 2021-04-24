#include "AVIDLib_IO/ReadResult.h"
#include "AVIDLib_Internal_Util/Memory.h"
#include "AVIDLib_Internal_Util/Check.h"

void ALIO_ReadResult_Reset(ALIO_ReadResult* result)
{
	if ( ALU_SANITY_VALID(result) )
	{
		ALU_ZERO_STRUCT(result);
		result->readError = ALIO_READER_ERROR_NONE;
	}
}
