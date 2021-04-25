#ifndef AVIDLIB_IO_VALIDATION_H
#define AVIDLIB_IO_VALIDATION_H

#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_Plat/Int.h"
#include "FormatCommon/FileElementHelpers.h"

#define ALIO_VALIDATION_RESULT_LIST \
	ALIO_LIST_ITEM(ALIO_VALIDATION_VALID = 0, "Validation was successful.") \
	ALIO_LIST_ITEM(ALIO_VALIDATION_INVALID_CHUNK, "The provided chunk description was not valid.") \
	ALIO_LIST_ITEM(ALIO_VALIDATION_CHUNK_STARTED_OUT_OF_RANGE, "The chunk was out of range of the data.") \
	ALIO_LIST_ITEM(ALIO_VALIDATION_CHUNK_ENDED_OUT_OF_RANGE, "The data was too short to contain the chunk.")

#define ALIO_LIST_ITEM(value, description) value,
typedef enum _ALIO_ValidationResult
{
	ALIO_VALIDATION_RESULT_LIST

	ALIO_VALIDATION_RESULT__COUNT
} ALIO_ValidationResult;
#undef ALIO_LIST_ITEM

const ALP_Char* ALIO_ValidationResult_Description(ALIO_ValidationResult result);

ALIO_ValidationResult ALIO_Validation_ValidateFileChunk(ALP_Size dataLength,
														const ALIO_CountOffsetPair* chunk,
														ALP_Size itemSize);

#endif // AVIDLIB_IO_VALIDATION_H
