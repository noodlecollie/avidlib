/**
 * About: Model.h
 * Defines the overall container for an ABMDLv10 model.
 */

#ifndef AVIDLIB_CONTAINERS_ABMDLV10_MODEL_H
#define AVIDLIB_CONTAINERS_ABMDLV10_MODEL_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Containers/ABMDLv10/ContainerDefinitions.h"
#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/BBox.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Struct: ALC_ABMDLv10_Model
 * Represents an overall ABMDLv10 model, and contains all its relevant components.
 */
typedef struct _ALC_ABMDLv10_Model
{
	/**
	 * Variable: name
	 * Internally recorded name for this model.
	 * May not exactly match the name of the file it was loaded from.
	 */
	ALP_Char name[ALC_ABMDLV10_MODEL_NAME_LENGTH];

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
} ALC_ABMDLv10_Model;

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
 * Function: ALC_ABMDLv10_Model_Init
 *
 * Initialises a model from uninitialised memory.
 *
 * This function should always be paired with a later call to <ALC_ABMDLv10_Model_Deinit>,
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
API_AVIDLIB_CONTAINERS ALC_ABMDLv10_Model* ALC_ABMDLv10_Model_Init(ALC_ABMDLv10_Model* model);

/**
 * Function: ALC_ABMDLv10_Model_Deinit
 *
 * Deinitialises a previously initialised model.
 *
 * This function should *always* be paired with a previous call to <ALC_ABMDLv10_Model_Init>,
 * to clean up any internal data held by the model.
 *
 * After the call, the model should not be reused without being initialised again.
 *
 * If the passed model was not previously initialised using <ALC_ABMDLv10_Model_Init>,
 * undefined behaviour will result.
 *
 * Parameters:
 *
 * model - Model to deinitialise.
 */
API_AVIDLIB_CONTAINERS void ALC_ABMDLv10_Model_Deinit(ALC_ABMDLv10_Model* model);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CONTAINERS_ABMDLV10_MODEL_H
