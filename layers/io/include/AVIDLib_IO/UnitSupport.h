/**
 * About: UnitSupport.h
 * Allows runtime querying of which units are supported in
 * the library, depending on the compile settings used.
 */

#ifndef AVIDLIB_IO_UNITSUPPORT_H
#define AVIDLIB_IO_UNITSUPPORT_H

#include "AVIDLib_IO/LibExport.h"
#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_Plat/Int.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Macro: ALIO_UNIT_ID_LIST
 * "XMACRO" list tying unit ID values to their readable names.
 * See <ALIO_UnitID> and <ALIO_UnitName>.
 */
#define ALIO_UNIT_ID_LIST \
	ALIO_LIST_ITEM(ALIO_UNIT_MDLV10 = 0, "MDLv10 IO", IO_MDLV10_AVAILABLE)

#define ALIO_LIST_ITEM(value, name, supported) value,

/**
 * Enum: ALIO_UnitID
 * ALIO_UNIT_MDLV10 - Version 10 MDL IO unit.
 */
typedef enum _ALIO_UnitID
{
	ALIO_UNIT_ID_LIST

	ALIO_UNIT_ID__COUNT
} ALIO_UnitID;

#undef ALIO_LIST_ITEM

/**
 * Function: ALIO_UnitName
 *
 * Returns the readable name for the given unit ID.
 *
 * Parameters:
 *
 * id - ID of the unit.
 *
 * Returns:
 *
 * Name corresponding to this ID.
 */
API_AVIDLIB_IO const ALP_Char* ALIO_UnitName(ALIO_UnitID id);

/**
 * Function: ALIO_SupportedUnits
 *
 * Returns a list of booleans describing which units are supported
 * by the library. The support depends on the settings that were used
 * to build the library.
 *
 * The list is <ALIO_UNIT_ID__COUNT> elements long, where each element
 * corresponds to a <ALIO_UnitID>. If the element indexed by the ID
 * is true then the unit is supported; if it is false, the unit
 * is not supported.
 *
 * The returned pointer is guaranteed to be valid.
 *
 * Returns:
 *
 * List of booleans specifying support for different units.
 */
API_AVIDLIB_IO const ALP_Bool* ALIO_SupportedUnits(void);

#ifdef __cplusplus
} // extern "C"
#endif


#endif // AVIDLIB_IO_UNITSUPPORT_H
