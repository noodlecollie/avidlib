#ifndef AVIDLIB_CONTAINERS_MDLV10_MDLFILE_H
#define AVIDLIB_CONTAINERS_MDLV10_MDLFILE_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Containers/MDLv10/Definitions.h"
#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/BBox.h"
#include "AVIDLib_Containers/MDLv10/Bone.h"

typedef struct _ALC_MDLv10_ModelFile
{
	/// Internally recorded name for this model.
	/// May not exactly match the name of the file it was loaded from.
	ALP_Char name[ALC_MDLV10_MODEL_NAME_LENGTH];

	/// Format-specific model flags.
	ALP_UInt32 flags;

	/// Position of this model's eyes.
	ALQM_Vec3 eyePosition;

	/// Hull used for testing movement collisions.
	ALQM_BBox movementHull;

	/// Hull used for testing visibility. (?)
	ALQM_BBox clippingHull;

	/// Number of bones in this model.
	ALP_Size numBones;

	/// Array of bones for this model.
	ALC_MDLv10_Bone* bones;
} ALC_MDLv10_ModelFile;

API_AVIDLIB_CONTAINERS void ALC_MDLv10_ModelFile_Init(ALC_MDLv10_ModelFile* modelFile);
API_AVIDLIB_CONTAINERS void ALC_MDLv10_ModelFile_Deinit(ALC_MDLv10_ModelFile* modelFile);

#endif // AVIDLIB_CONTAINERS_MDLV10_MDLFILE_H
