#ifndef AVIDLIB_IO_PARSEERRORS_H
#define AVIDLIB_IO_PARSEERRORS_H

#include "AVIDLib_IO/LibExport.h"

#define ALIO_PARSE_ERROR_LIST \
	ALIO_LIST_ITEM(ALIO_PARSE_NO_ERROR = 0, "No parse error.")

#define ALIO_LIST_ITEM(value, description) value,
typedef enum _ALIO_ParseError
{
	ALIO_PARSE_ERROR_LIST

	ALIO_PARSE_ERROR__COUNT
} ALIO_ParseError;
#undef ALIO_LIST_ITEM

API_AVIDLIB_IO const char* ALIO_ParseError_Description(ALIO_ParseError error);

#endif // AVIDLIB_IO_PARSEERRORS_H
