#include "AVIDLib_IO/MDLv10/Reader.h"
#include "AVIDLib_Internal_Util/Util.h"

ALIO_ReaderError ALIO_MDLv10_Read(const ALP_Byte* inData, ALP_Size inSize, ALIO_ReadResult* outResult, ALC_MDLv10_Model* outModel)
{
	// Set up default result.
	if ( outResult )
	{
		ALIO_ReadResult_Reset(outResult);
	}

	// TODO: Implement properly.
	// Return an unimplemented error for now.
	ALU_UNUSED(inData);
	ALU_UNUSED(inSize);
	ALU_UNUSED(outModel);
	const ALIO_ReaderError error = ALIO_READER_ERROR_UNIMPLEMENTED;

	if ( outResult )
	{
		outResult->readError = error;
	}

	return error;
}
