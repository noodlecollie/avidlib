#include "MDLv10/GenericUnitInterface_MDLv10.h"
#include "AVIDLib_IO/MDLv10/Reader/Reader.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Containers/MDLv10/Model.h"
#include "AVIDLib_Internal_Util/Check.h"

static ALP_Size ContainerSizeInBytes(void)
{
	return sizeof(ALC_MDLv10_Model);
}

static void GenericInit(ALP_Opaque* container)
{
	ALC_MDLv10_Model_Init((ALC_MDLv10_Model*)container);
}

static void GenericDeinit(ALP_Opaque* container)
{
	ALC_MDLv10_Model_Deinit((ALC_MDLv10_Model*)container);
}

static ALP_Bool GenericRead(ALIO_ReadContext* context, ALP_Opaque* container)
{
	return ALIO_MDLv10_Read(context, (ALC_MDLv10_Model*)container);
}

const ALIO_GenericUnitInterface ALIO_MDLv10_GenericUnitInterface =
{
	&ContainerSizeInBytes,
	&ALIO_MDLv10_Identify,

	&GenericInit,
	&GenericDeinit,
	&GenericRead
};
