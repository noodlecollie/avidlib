#include "AVIDLib_IO/GenericOperations.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Memory.h"
#include "UnitSupportDefs.h"
#include "GenericUnitInterface.h"

typedef struct _GenericOperationsRecord
{
	ALIO_UnitID unitID;
	const ALIO_GenericUnitInterface* interface;
} GenericOperationsRecord;

#define ALIO_GENERIC_OPERATIONS_LIST \
	ALIO_LIST_ITEM(ALIO_UNIT_MDLV10, IO_MDLV10_GENERIC_UNIT_INTERFACE)

#define ALIO_LIST_ITEM(id, identify) { id, identify },
static const GenericOperationsRecord GENERIC_OPERATIONS_TABLE[] =
{
	ALIO_GENERIC_OPERATIONS_LIST

	// This must be last
	{ ALIO_UNIT_ID__INVALID, ALP_NULL }
};
#undef ALIO_LIST_ITEM

static inline void ResetContainer(ALIO_GenericContainer* container)
{
	ALU_ZERO_STRUCT(container);
	container->unit = ALIO_UNIT_ID__INVALID;
}

static inline const ALIO_GenericUnitInterface* GetUnitInterface(ALIO_UnitID unitID)
{
	for ( const GenericOperationsRecord* record = GENERIC_OPERATIONS_TABLE;
	      record->unitID != ALIO_UNIT_ID__INVALID;
	      ++record )
	{
		if ( record->unitID == unitID && record->interface )
		{
			return record->interface;
		}
	}

	return ALP_NULL;
}

static ALP_Bool GenericDeinit(ALIO_GenericContainer* container)
{
	const ALIO_GenericUnitInterface* ifc;

	ifc = GetUnitInterface(container->unit);

	// Do some sanity checks:

	if ( !ifc )
	{
		return ALP_FALSE;
	}

	if ( !ifc->containerSizeInBytes ||
	     !ifc->genericDeinit )
	{
		return ALP_FALSE;
	}

	// If the number of bytes specified is > 0, it must match the expected
	// number of bytes, and there must be data.
	if ( container->containerSizeBytes > 0 &&
	     (ifc->containerSizeInBytes() != container->containerSizeBytes || !container->container) )
	{
		return ALP_FALSE;
	}

	// If the number of bytes specified is 0, there must be no data.
	if ( container->containerSizeBytes < 1 && container->container )
	{
		return ALP_FALSE;
	}

	if ( container->container )
	{
		ifc->genericDeinit(container->container);
		ALP_Free(container->container);
	}

	ResetContainer(container);
	return ALP_TRUE;
}

ALIO_UnitID ALIO_UnitForFile(const ALIO_ReadContext* context)
{
	if ( ALU_SANITY_VALID(context) )
	{
		for ( const GenericOperationsRecord* record = GENERIC_OPERATIONS_TABLE;
			  record->unitID != ALIO_UNIT_ID__INVALID;
			  ++record )
		{
			if ( record->interface &&
				 record->interface->identify &&
				 record->interface->identify(context) )
			{
				return record->unitID;
			}
		}
	}

	return ALIO_UNIT_ID__INVALID;
}

ALIO_GenericContainer* ALIO_GenericContainer_Init(ALIO_GenericContainer* container)
{
	if ( ALU_SANITY_VALID(container) )
	{
		ResetContainer(container);
	}

	return container;
}

ALIO_GenericContainer* ALIO_GenericContainer_Deinit(ALIO_GenericContainer* container)
{
	if ( ALU_SANITY_VALID(container) )
	{
		// If there is container data, the unit ID must not be ALIO_UNIT_ID__INVALID.
		ALU_ASSERT_VALID((!container->container && container->containerSizeBytes < 1) ||
		                 container->unit != ALIO_UNIT_ID__INVALID);

		if ( container->unit != ALIO_UNIT_ID__INVALID )
		{
			// If this fails, it's a programmer error, or something's gone badly wrong.
			ALU_ASSERT_ALWAYS(GenericDeinit(container));
		}
	}

	return container;
}

ALP_Bool ALIO_GenericRead(ALIO_ReadContext* context, ALIO_UnitID targetUnitID, ALIO_GenericContainer* outContainer)
{
	bool success = false;

	if ( ALU_SANITY_VALID(context) )
	{
		const ALIO_GenericUnitInterface* ifc = ALP_NULL;
		bool wasInitialised = false;

		do
		{
			size_t containerSize = 0;

			if ( !ALU_SANITY_VALID(outContainer) )
			{
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_EMPTY_OUTPUT, ALP_NULL);
				break;
			}

			// Ensure any existing data is freed.
			ALIO_GenericContainer_Deinit(outContainer);
			ALIO_GenericContainer_Init(outContainer);

			if ( targetUnitID == ALIO_UNIT_ID__INVALID )
			{
				targetUnitID = ALIO_UnitForFile(context);
			}

			// Record the unit we are going to attempt to read for.
			outContainer->unit = targetUnitID;

			// If we failed to deduce a unit, exit here.
			if ( outContainer->unit == ALIO_UNIT_ID__INVALID )
			{
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_UNKNOWN_MAGIC, "No available unit could read the provided file.");
				break;
			}

			ifc = GetUnitInterface(outContainer->unit);

			if ( !ALU_SANITY_VALID(ifc) )
			{
				// Should never happen.
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_UNIMPLEMENTED, "The requested unit was not set up correctly.");
				break;
			}

			containerSize = ifc->containerSizeInBytes ? ifc->containerSizeInBytes() : 0;

			if ( !ALU_SANITY_VALID(containerSize > 0) )
			{
				// Should never happen, but checking just in case.
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_INTERNAL, "Unit container size was reported as zero.");
				break;
			}

			outContainer->container = ALP_Malloc(containerSize);

			if ( !outContainer->container )
			{
				// Could not allocate memory.
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_INSUFFICIENT_MEMORY, ALP_NULL);
				break;
			}

			outContainer->containerSizeBytes = containerSize;

			// Sanity:
			if ( !ALU_SANITY_VALID(ifc->genericInit && ifc->genericDeinit) )
			{
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_INTERNAL, "Init/Deinit functions were not available.");
				break;
			}

			ifc->genericInit(outContainer->container);
			wasInitialised = true;

			// We now have a unit-specific container. Attempt to read the file.

			if ( !ALU_SANITY_VALID(ifc->genericRead) )
			{
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_INTERNAL, "Read function was not available.");
				break;
			}

			if ( !ifc->genericRead(context, outContainer->container) )
			{
				// Could not read. The error should already be set on the context.
				break;
			}

			// The read was successful, so we're all done.
			success = true;
		}
		while ( false );

		if ( !success && outContainer && ifc )
		{
			// Something went wrong after we acquired a unit interface.
			// Make sure everything is cleaned up.

			if ( wasInitialised )
			{
				ifc->genericDeinit(outContainer->container);
			}

			if ( outContainer->container )
			{
				ALP_Free(outContainer->container);
			}

			outContainer->container = ALP_NULL;
			outContainer->containerSizeBytes = 0;
		}
	}

	return success;
}
