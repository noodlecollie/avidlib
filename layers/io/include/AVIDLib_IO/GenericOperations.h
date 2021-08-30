/**
 * About: GenericOperations.h
 * Operations that can be applied to files without knowing the specific
 * unit which handles them.
 */

#ifndef AVIDLIB_IO_GENERICOPERATIONS_H
#define AVIDLIB_IO_GENERICOPERATIONS_H

#include "AVIDLib_IO/UnitSupport.h"
#include "AVIDLib_IO/ReadContext.h"

#ifdef __cplusplus
extern "C" {
#endif

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
ALIO_UnitID ALIO_UnitForFile(ALIO_ReadContext* context);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_IO_GENERICOPERATIONS_H
