#include "Validation.h"

const ALP_Char* ALIO_ValidationResult_Description(ALIO_ValidationResult result)
{
#define ALIO_LIST_ITEM(value, description) description,
	static const ALP_Char* VALIDATION_RESULT_STRINGS[ALIO_VALIDATION_RESULT__COUNT] =
	{
		ALIO_VALIDATION_RESULT_LIST
	};
#undef ALIO_LIST_ITEM

	const ALP_Int32 index = (int)result;

	return index >= 0 && index < ALIO_VALIDATION_RESULT__COUNT
		? VALIDATION_RESULT_STRINGS[index]
		: "UNKNOWN";
}

ALIO_ValidationResult ALIO_Validation_ValidateFileChunk(ALP_Size length,
														const ALIO_CountOffsetPair* chunk,
														ALP_Size itemSize)
{
	if ( !chunk || itemSize < 1 )
	{
		return ALIO_VALIDATION_INVALID_CHUNK;
	}

	if ( chunk->count < 1 )
	{
		// Always valid, no matter the size of input.
		return ALIO_VALIDATION_VALID;
	}

	if ( chunk->offset >= length )
	{
		return ALIO_VALIDATION_CHUNK_STARTED_OUT_OF_RANGE;
	}

	if ( chunk->offset + (chunk->count * itemSize) > length )
	{
		return ALIO_VALIDATION_CHUNK_ENDED_OUT_OF_RANGE;
	}

	return ALIO_VALIDATION_VALID;
}
