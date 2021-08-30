#include "AVIDLib_IO/UnitSupport.h"

const ALP_Char* ALIO_UnitName(ALIO_UnitID id)
{
#define ALIO_LIST_ITEM(value, name, supported) name,
	static ALP_Char* UNIT_NAMES[ALIO_UNIT_ID__COUNT] =
	{
		ALIO_UNIT_ID_LIST
	};
#undef ALIO_LIST_ITEM

	if ( id == ALIO_UNIT_ID__INVALID )
	{
		return "INVALID";
	}

	return (ALP_Size)id < ALIO_UNIT_ID__COUNT
		? UNIT_NAMES[(ALP_Size)id]
		: "UNKNOWN";
}

const ALP_Bool* ALIO_SupportedUnits(void)
{
#define ALIO_LIST_ITEM(value, name, supported) (!!(supported)),
	static ALP_Bool SUPPORTED_UNITS[ALIO_UNIT_ID__COUNT] =
	{
		ALIO_UNIT_ID_LIST
	};
#undef ALIO_LIST_ITEM

	return SUPPORTED_UNITS;
}
