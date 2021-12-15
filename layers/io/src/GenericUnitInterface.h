#ifndef AVIDLIB_IO_GENERICUNITINTERFACE_H
#define AVIDLIB_IO_GENERICUNITINTERFACE_H

#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_IO/ReadContext.h"

typedef struct _ALIO_GenericUnitInterface
{
	ALP_Size (*containerSizeInBytes)(void);
	ALP_Bool (*identify)(const ALIO_ReadContext* context);

	void (*genericInit)(ALP_OpaquePtr container);
	void (*genericDeinit)(ALP_OpaquePtr container);
	ALP_Bool (*genericRead)(ALIO_ReadContext* context, ALP_OpaquePtr container);
} ALIO_GenericUnitInterface;

#endif // AVIDLIB_IO_GENERICUNITINTERFACE_H
