/**
 * About: Model.h
 * Defines the overall container for an MDLv10 model.
 */

#ifndef AVIDLIB_CONTAINERS_MDLV10_MODEL_H
#define AVIDLIB_CONTAINERS_MDLV10_MODEL_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Containers/MDLv10/Definitions.h"
#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/BBox.h"
#include "AVIDLib_Containers/MDLv10/Bone.h"

/**
 * Struct: ALC_MDLv10_Model
 * Represents an overall MDLv10 model, and contains all its relevant components.
 */
typedef struct _ALC_MDLv10_Model
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
} ALC_MDLv10_Model;

/**
 * Section: Operator Functions
 * All functions below assume that their inputs are valid.
 * If this is not the case, undefined behaviour will result.
 *
 * Checking can be turned on by enabling the *PERFORM_VALIDITY_CHECKS*
 * CMake option. If this is turned on and invalid inputs are provided
 * to any of the functions below, an assertion failure will result.
 */

/**
 * Group: Construction and Destruction
 */

/**
 * Function: ALC_MDLv10_Model_Init
 *
 * Initialises a model from uninitialised memory.
 *
 * This function should always be paired with a later call to <ALC_MDLv10_Model_Deinit>,
 * to clean up any internal data held by the model.
 *
 * *Do not* call this function on a model which has already been initialised,
 * or undefined behaviour will result.
 *
 * Parameters:
 *
 * model - Model to initialise.
 *
 * Returns:
 *
 * Input model.
 */
API_AVIDLIB_CONTAINERS ALC_MDLv10_Model* ALC_MDLv10_Model_Init(ALC_MDLv10_Model* model);

/**
 * Function: ALC_MDLv10_Model_Deinit
 *
 * Deinitialises a previously initialised model.
 *
 * This function should *always* be paired with a previous call to <ALC_MDLv10_Model_Init>,
 * to clean up any internal data held by the model.
 *
 * After the call, the model should not be reused without being initialised again.
 *
 * If the passed model was not previously initialised using <ALC_MDLv10_Model_Init>,
 * undefined behaviour will result.
 *
 * Parameters:
 *
 * model - Model to deinitialise.
 */
API_AVIDLIB_CONTAINERS void ALC_MDLv10_Model_Deinit(ALC_MDLv10_Model* model);

/**
 * Group: Bones
 */

/**
 * Function: ALC_MDLv10_Model_AllocateBones
 *
 * Allocates and default-initialises a list of <ALC_MDLv10_Bone> items in the model.
 * If any list of bones already exists, all bones are deinitialised, and the list
 * is deallocated, before a new list is allocated.
 *
 * If numBones is zero, any existing list is deallocated as above, but no new list
 * is allocated. The bones list within the model will be set to null, and null will
 * be returned.
 *
 * Parameters:
 *
 * model    - Model within which to allocate the list of bones.
 * numBones - Number of bones to allocate space for in the list.
 *
 * Returns:
 *
 * A pointer to the newly allocated list, or null if numBones was zero.
 */
API_AVIDLIB_CONTAINERS ALC_MDLv10_Bone* ALC_MDLv10_Model_AllocateBones(ALC_MDLv10_Model* model, ALP_Size numBones);

/**
 * Function: ALC_MDLv10_Model_FreeBones
 *
 * Frees any existing allocated bone list in the model. As part of the process,
 * all bones are deinitialised.
 *
 * If no bone list exists in the model, this function does nothing.
 *
 * Parameters:
 *
 * model - Model containing the list of bones.
 */
API_AVIDLIB_CONTAINERS void ALC_MDLv10_Model_FreeBones(ALC_MDLv10_Model* model);

#endif // AVIDLIB_CONTAINERS_MDLV10_MODEL_H
