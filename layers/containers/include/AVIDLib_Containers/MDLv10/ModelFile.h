/**
 * About: ModelFile.h
 * Defines the overall container for an MDLv10 model.
 */

#ifndef AVIDLIB_CONTAINERS_MDLV10_MDLFILE_H
#define AVIDLIB_CONTAINERS_MDLV10_MDLFILE_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Containers/MDLv10/Definitions.h"
#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/BBox.h"
#include "AVIDLib_Containers/MDLv10/Bone.h"

/**
 * Struct: ALC_MDLv10_ModelFile
 * Represents an overall MDLv10 file, and contains all its relevant components.
 */
typedef struct _ALC_MDLv10_ModelFile
{
	/**
	 * Variable: name
	 * Internally recorded name for this model.
	 * May not exactly match the name of the file it was loaded from.
	 */
	ALP_Char name[ALC_MDLV10_MODEL_NAME_LENGTH];

	/**
	 * Variable: flags
	 * Holds flags that apply to the model as a whole.
	 */
	ALP_UInt32 flags;

	/**
	 * Variable: eyePosition
	 * Position of this model's eyes.
	 */
	ALQM_Vec3 eyePosition;

	/**
	 * Variable: movementHull
	 * Hull used for testing movement collisions.
	 */
	ALQM_BBox movementHull;

	/**
	 * Variable: clippingHull
	 * Hull used for testing visibility. (?)
	 */
	ALQM_BBox clippingHull;

	/**
	 * Variable: numBones
	 * Number of bones in this model.
	 */
	ALP_Size numBones;

	/**
	 * Variable: bones
	 * Array of bones for this model.
	 */
	ALC_MDLv10_Bone* bones;
} ALC_MDLv10_ModelFile;

/**
 * Section: Operator Functions
 */

/**
 * Group: Construction and Destruction
 */

/**
 * Function: ALC_MDLv10_ModelFile_Init
 *
 * Initialises a model file from uninitialised memory.
 *
 * *Do not* call this function on a model file which has already
 * been initialised, or memory leaks will result.
 *
 * Parameters:
 *
 * modelFile - Model file to initialise.
 *
 * Returns:
 *
 * modelFile.
 *
 */
API_AVIDLIB_CONTAINERS ALC_MDLv10_ModelFile* ALC_MDLv10_ModelFile_Init(ALC_MDLv10_ModelFile* modelFile);

/**
 * Function: ALC_MDLv10_ModelFile_Deinit
 *
 * De-initialises a model file previously initialised by <ALC_MDLv10_ModelFile_Init>.
 * This frees any memory that was in use.
 * After the call, the model file should not be reused without being initialised again.
 *
 * If the passed model file was not previously initialised, undefined behaviour
 * will result.
 *
 * Parameters:
 *
 * modelFile - Model file to de-initialise.
 */
API_AVIDLIB_CONTAINERS void ALC_MDLv10_ModelFile_Deinit(ALC_MDLv10_ModelFile* modelFile);

#endif // AVIDLIB_CONTAINERS_MDLV10_MDLFILE_H
