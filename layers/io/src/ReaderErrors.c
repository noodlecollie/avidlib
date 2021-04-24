#include "AVIDLib_IO/ReaderErrors.h"
#include "AVIDLib_Plat/Int.h"

const char* ALIO_ReaderError_Description(ALIO_ReaderError error)
{
#define ALIO_LIST_ITEM(value, description) description,
	static const char* READER_ERROR_STRINGS[ALIO_READER_ERROR__COUNT] =
	{
		ALIO_READER_ERROR_LIST
	};
#undef ALIO_LIST_ITEM

	const ALP_Int32 index = (int)error;

	return index >= 0 && index < ALIO_READER_ERROR__COUNT
		? READER_ERROR_STRINGS[index]
		: "UNKNOWN";
}
