#include "AVIDLib_IO/GenericOperations.h"
#include "UnitSupportDefs.h"

typedef ALP_Bool (*IdentifyFunc)(const ALIO_ReadContext*);

typedef struct _GenericOperationsRecord
{
	ALIO_UnitID unitID;
	IdentifyFunc identify;
} GenericOperationsRecord;

#define ALIO_GENERIC_OPERATIONS_LIST \
	ALIO_LIST_ITEM(ALIO_UNIT_MDLV10, IO_MDLV10_IDENTIFY_FUNC)

#define ALIO_LIST_ITEM(id, identify) { id, identify },
static const GenericOperationsRecord GENERIC_OPERATIONS_TABLE[] =
{
	ALIO_GENERIC_OPERATIONS_LIST

	// This must be last
	{ ALIO_UNIT_ID__INVALID, ALP_NULL }
};
#undef ALIO_LIST_ITEM

ALIO_UnitID ALIO_UnitForFile(const ALIO_ReadContext* context)
{
	for ( const GenericOperationsRecord* record = GENERIC_OPERATIONS_TABLE; record->unitID != ALIO_UNIT_ID__INVALID; ++record )
	{
		if ( record->identify && record->identify(context) )
		{
			return record->unitID;
		}
	}

	return ALIO_UNIT_ID__INVALID;
}
