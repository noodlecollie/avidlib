/**
 * About: UnitSupport.h
 * Allows runtime querying of which units are supported in
 * the library, depending on the compile settings used.
 */

#ifndef AVIDLIB_CONTAINERS_UNITSUPPORT_H
#define AVIDLIB_CONTAINERS_UNITSUPPORT_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_Plat/Int.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Macro: ALC_UNIT_ID_LIST
 * "XMACRO" list tying unit ID values to their readable names.
 * See <ALC_UnitID> and <ALC_UnitName>.
 */
#define ALC_UNIT_ID_LIST \
	ALC_LIST_ITEM(ALC_UNIT_MDLV10 = 0, "MDLv10 Container", CONTAINERS_MDLV10_AVAILABLE)

#define ALC_LIST_ITEM(value, name, supported) value,

/**
 * Enum: ALC_UnitID
 * ALC_UNIT_MDLV10 - Version 10 MDL container unit.
 * ALC_UNIT_ID__COUNT   - Total number of IDs. Do not use.
 * ALC_UNIT_ID__INVALID - Invalid unit ID. Do not use.
 */
typedef enum _ALC_UnitID
{
	ALC_UNIT_ID_LIST

	ALC_UNIT_ID__COUNT,
	ALC_UNIT_ID__INVALID = -1
} ALC_UnitID;

#undef ALC_LIST_ITEM

/**
 * Function: ALC_UnitName
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
API_AVIDLIB_CONTAINERS const ALP_Char* ALC_UnitName(ALC_UnitID id);

/**
 * Function: ALC_SupportedUnits
 *
 * Returns a list of booleans describing which units are supported
 * by the library. The support depends on the settings that were used
 * to build the library.
 *
 * The list is <ALC_UNIT_ID__COUNT> elements long, where each element
 * corresponds to a <ALC_UnitID>. If the element indexed by the ID
 * is true then the unit is supported; if it is false, the unit
 * is not supported.
 *
 * The returned pointer is guaranteed to be valid.
 *
 * Returns:
 *
 * List of booleans specifying support for different units.
 */
API_AVIDLIB_CONTAINERS const ALP_Bool* ALC_SupportedUnits(void);

#ifdef __cplusplus
} // extern "C"
#endif


#endif // AVIDLIB_CONTAINERS_UNITSUPPORT_H
