#include "AVIDLib_IO/ParseErrors.h"
#include "AVIDLib_Plat/Int.h"

const char* ALIO_ParseError_Description(ALIO_ParseError error)
{
#define ALIO_LIST_ITEM(value, description) description,
	static const char* PARSE_ERROR_STRINGS[ALIO_PARSE_ERROR__COUNT] =
	{
		ALIO_PARSE_ERROR_LIST
	};
#undef ALIO_LIST_ITEM

	const ALP_Int32 index = (int)error;

	return index >= 0 && index < ALIO_PARSE_ERROR__COUNT
		? PARSE_ERROR_STRINGS[index]
		: "UNKNOWN";
}
