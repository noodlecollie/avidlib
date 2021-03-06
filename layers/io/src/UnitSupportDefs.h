#ifndef AVIDLIB_IO_UNITSUPPORTDEFS_H
#define AVIDLIB_IO_UNITSUPPORTDEFS_H

#include "AVIDLib_Plat/Ptr.h"

#if IO_MDLV10_AVAILABLE != 0
#include "MDLv10/GenericUnitInterface_MDLv10.h"
#define IO_MDLV10_GENERIC_UNIT_INTERFACE (&ALIO_MDLv10_GenericUnitInterface)
#else
#define IO_MDLV10_GENERIC_UNIT_INTERFACE ALP_NULL
#endif

#endif // AVIDLIB_IO_UNITSUPPORTDEFS_H
