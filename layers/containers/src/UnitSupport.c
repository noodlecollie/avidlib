#include "AVIDLib_Containers/UnitSupport.h"

const ALP_Char* ALC_UnitName(ALC_UnitID id)
{
#define ALC_LIST_ITEM(value, name, supported) name,
	static ALP_Char* UNIT_NAMES[ALC_UNIT_ID__COUNT] =
	{
		ALC_UNIT_ID_LIST
	};
#undef ALC_LIST_ITEM

	const ALP_Size index = (ALP_Size)id;

	return index < ALC_UNIT_ID__COUNT
		? UNIT_NAMES[index]
		: "UNKNOWN";
}

const ALP_Bool* ALC_SupportedUnits(void)
{
#define ALC_LIST_ITEM(value, name, supported) (!!(supported)),
	static ALP_Bool SUPPORTED_UNITS[ALC_UNIT_ID__COUNT] =
	{
		ALC_UNIT_ID_LIST
	};
#undef ALC_LIST_ITEM

	return SUPPORTED_UNITS;
}
