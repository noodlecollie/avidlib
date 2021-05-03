/**
 * About: BoneController.h
 * Defines an MDLv10 bone controller.
 */

#ifndef AVIDLIB_CONTAINERS_MDLV10_BONECONTROLLER_H
#define AVIDLIB_CONTAINERS_MDLV10_BONECONTROLLER_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_QMath/Types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _ALC_MDLv10_Bone;

/**
 * Struct: ALC_MDLv10_BoneController
 * Defines an MDLv10 bone controller.
 *
 * Bone controllers specify parameters by which bones can be
 * programmatically controlled. A bone controller specifies
 * the bone whose motion should be affected, along with which
 * components of motion (both translation and rotation)
 * are controlled.
 */
typedef struct _ALC_MDLv10_BoneController
{
	/**
	 * Variable: refBone
	 * Pointer to the bone within the model which
	 * this controller affects.
	 */
	struct _ALC_MDLv10_Bone* refBone;

	/**
	 * Variable: motionType
	 * Type of motion this controller applies.
	 * Bitmask of ALIO_MDLV10_MVFLAG_* values.
	 */
	ALP_UInt32 motionType;

	/**
	 * Variable: start
	 * Starting value for this controller's motion range.
	 */
	ALQM_Scalar start;

	/**
	 * Variable: end
	 * Ending value for this controller's motion range.
	 */
	ALQM_Scalar end;

	/**
	 * Variable: channel
	 * Which controller channel this bone controller maps to
	 * on the entity which uses this model.
	 */
	ALP_Size channel;
} ALC_MDLv10_BoneController;

/**
 * Function: ALC_MDLv10_BoneController_Init
 *
 * Initialises a bone controller from uninitialised memory.
 *
 * This function should always be paired with a later call to <ALC_MDLv10_BoneController_Deinit>,
 * to clean up any internal data held by the bone controller.
 *
 * *Do not* call this function on a bone controller which has already been initialised,
 * or undefined behaviour will result.
 *
 * Parameters:
 *
 * controller - Bone controller to initialise.
 *
 * Returns:
 *
 * Input bone controller.
 */
API_AVIDLIB_CONTAINERS ALC_MDLv10_BoneController* ALC_MDLv10_BoneController_Init(ALC_MDLv10_BoneController* controller);

/**
 * Function: ALC_MDLv10_BoneController_Deinit
 *
 * Deinitialises a previously initialised bone controller.
 *
 * This function should *always* be paired with a previous call to <ALC_MDLv10_BoneController_Init>,
 * to clean up any internal data held by the bone controller.
 *
 * After the call, the bone controller should not be reused without being initialised again.
 *
 * If the passed bone controller was not previously initialised using <ALC_MDLv10_BoneController_Init>,
 * undefined behaviour will result.
 *
 * Parameters:
 *
 * controller - Bone controller to deinitialise.
 */
API_AVIDLIB_CONTAINERS void ALC_MDLv10_BoneController_Deinit(ALC_MDLv10_BoneController* controller);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CONTAINERS_MDLV10_BONECONTROLLER_H
