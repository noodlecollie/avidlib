/**
 * About: GenericOperations.h
 * Operations that can be applied to files without knowing the specific
 * unit which handles them.
 */

#ifndef AVIDLIB_IO_GENERICOPERATIONS_H
#define AVIDLIB_IO_GENERICOPERATIONS_H

#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_IO/UnitSupport.h"
#include "AVIDLib_IO/ReadContext.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Struct: ALIO_GenericContainer
 */
typedef struct _ALIO_GenericContainer
{
	/**
	 * Variable: unit
	 * ID of the unit that the following container
	 * data belongs to.
	 */
	ALIO_UnitID unit;

	/**
	 * Variable: container
	 * Opaque pointer to container data. This may
	 * be cast to the container type corresponding
	 * to the unit.
	 */
	ALP_OpaquePtr container;

	/**
	 * Variable: containerSizeBytes
	 * Used to sanity check the opaque container data.
	 * This should match the size of the container
	 * struct from the specified unit.
	 */
	ALP_Size containerSizeBytes;

} ALIO_GenericContainer;

/**
 * Function: ALIO_UnitForFile
 *
 * Given a read context, returns the ID of the IO unit that can read this file.
 *
 * If there is no IO unit present in the library that can read the file,
 * <ALIO_UNIT_ID__INVALID> is returned.
 *
 * Parameters:
 *
 * context - Read context representing the file that is waiting to be read.
 *
 * Return:
 *
 * <ALIO_UnitID> representing the unit that can read this file, or
 * <ALIO_UNIT_ID__INVALID> if no unit is available to read this file.
 */
API_AVIDLIB_IO ALIO_UnitID ALIO_UnitForFile(const ALIO_ReadContext* context);

/**
 * Function: ALIO_GenericContainer_Init
 *
 * Initialises a generic container from uninitialised memory.
 *
 * This function should always be paired with a later call to <ALIO_GenericContainer_Deinit>,
 * to clean up any internal data held by the container.
 *
 * *Do not* call this function on a container which has already been initialised,
 * or undefined behaviour will result.
 *
 * Parameters:
 *
 * container - Container to initialise.
 *
 * Returns:
 *
 * Input container.
 */
API_AVIDLIB_IO ALIO_GenericContainer* ALIO_GenericContainer_Init(ALIO_GenericContainer* container);

/**
 * Function: ALIO_GenericContainer_Deinit
 *
 * Deinitialises a previously initialised container.
 *
 * This function should *always* be paired with a previous call to <ALIO_GenericContainer_Init>,
 * to clean up any internal data held by the container.
 *
 * After the call, the container should not be reused without being initialised again.
 *
 * If the passed container was not previously initialised using <ALIO_GenericContainer_Init>,
 * undefined behaviour will result.
 *
 * Parameters:
 *
 * container - Container to deinitialise.
 */
API_AVIDLIB_IO ALIO_GenericContainer* ALIO_GenericContainer_Deinit(ALIO_GenericContainer* container);

/**
 * Function: ALIO_GenericRead
 *
 * Given a read context, interprets the input data corresponding to a specific
 * unit and places the output in the given container.
 *
 * If targetUnitID is <ALIO_UNIT_ID__INVALID>, a guess will be made to
 * determine the correct unit to use for reading the input data.
 * Otherwise, if targetUnitID specifies a supported unit, the contents
 * of the read context will be interpreted as a file format corresponding
 * to this unit.
 *
 * The return value of this function will be true if the input data could
 * be read by the chosen unit, or false if it could not. More specific
 * details about any errors will be set on the read context.
 *
 * Regardless of whether reading was successful, the <ALIO_GenericContainer::unitID>
 * member of outContainer will be set to the ID of the unit that was used
 * for reading. If targetUnitID was <ALIO_UNIT_ID__INVALID>, and no
 * supported unit could read the input data, the <ALIO_GenericContainer::unitID>
 * member will be set to <ALIO_UNIT_ID__INVALID>.
 *
 * If reading was successful, the <ALIO_GenericContainer::container> member
 * variable of the outContainer argument will point to a struct corresponding
 * to the container type for the chosen unit. This variable may be cast to
 * a specific container type later. If reading was not successful, the variable
 * will be set to null.
 *
 * Note that outContainer must be initialised before calling this
 * function, or behaviour is undefined. Note also that the container must be
 * deinitialised once its contents are no longer needed, in order to release memory.
 *
 * If outContainer already holds a valid container, this data will be freed
 * before reading is attempted.
 *
 * Parameters:
 *
 * context      - Contextual data for this read operation.
 * targetUnitID - ID of the unit to use to read the input data, or <ALIO_UNIT_ID__INVALID>
 *                if the unit to use should be inferred based on the input data.
 * outContainer - Generic container to hold the result of the read operation.
 *                *This is assumed to already have been initialised.* Any container data
 *                that already exists within outContainer will be freed before reading
 *                is attempted.
 *
 * Returns:
 *
 * True if the result of the read was <ALIO_READER_ERROR_NONE>,
 * or false if some read error occurred. The actual error code,
 * along with any other error details, is set on the context.
 */
API_AVIDLIB_IO ALP_Bool ALIO_GenericRead(ALIO_ReadContext* context, ALIO_UnitID targetUnitID, ALIO_GenericContainer* outContainer);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_IO_GENERICOPERATIONS_H
