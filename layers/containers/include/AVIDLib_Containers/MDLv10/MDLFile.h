#ifndef AVIDLIB_CONTAINERS_MDLV10_MDLFILE_H
#define AVIDLIB_CONTAINERS_MDLV10_MDLFILE_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Containers/MDLv10/Definitions.h"
#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/BBox.h"

typedef struct _ALC_MDLv10_ModelFile
{
	ALP_Char name[ALC_MDLV10_MODEL_NAME_LENGTH];
	ALP_UInt32 flags;

	ALQM_Vec3 eyePosition;
	ALQM_BBox movementHull;
	ALQM_BBox clippingHull;
} ALC_MDLv10_ModelFile;

// REMOVE ME
API_AVIDLIB_CONTAINERS void ALC_MDLv10_Test();

#endif // AVIDLIB_CONTAINERS_MDLV10_MDLFILE_H
