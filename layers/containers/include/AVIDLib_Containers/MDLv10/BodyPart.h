/**
 * About: BodyPart.h
 * Defines an MDLv10 body part.
 */

#ifndef AVIDLIB_CONTAINERS_MDLV10_BODYPART_H
#define AVIDLIB_CONTAINERS_MDLV10_BODYPART_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_Containers/MDLv10/ContainerDefinitions.h"
#include "AVIDLib_Containers/MDLv10/Submodel.h"
#include "AVIDLib_Plat/Int.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Struct: ALC_MDLv10_BodyPart
 * Defines an MDLv10 body part.
 *
 * Body parts are used to allow different groupings of geometry
 * in a model. The way this works can seem a little convoluted
 * if you don't know how it works, so let's go through a small
 * example in detail.
 *
 * Let's say a gun model has three different sections of geometry
 * that may be varied by game code: the gun itself, the sight on
 * top, and the silencer. Each of the gun, sight and silencer
 * would comprise a "body part".
 *
 * Additionally, the gun has four different "body groups": the
 * gun with no accessories, the gun with a silencer but no sight,
 * the gun with a large silencer and large sight, and the gun with
 * a small silencer and small sight. For each of the individual
 * body parts, there are four different meshes that could be
 * rendered depending on the body group that the game wants to show.
 * In the case where the gun has a silencer but no sight, the
 * permutation for the sight has no geometry at all.
 *
 * The <ALC_MDLv10_BodyPart> struct defines a body part in the
 * above scenario. The body part may make reference to multiple
 * different meshes, depending on how many body groups have been
 * defined on the model.
 */
typedef struct _ALC_MDLv10_BodyPart
{
	/**
	 * Variable: name
	 * Name of this body part. Should be unique within the model.
	 * Maximum number of characters, including the string terminator,
	 * is <ALC_MDLV10_BODYPART_NAME_LENGTH>.
	 */
	ALP_Char name[ALC_MDLV10_BODYPART_NAME_LENGTH];

	/**
	 * Variable: numSubmodels
	 * Number of <submodels> referenced by this body part.
	 */
	ALP_Size numSubmodels;

	/**
	 * Variable: submodels
	 * Array of submodels owned by this body part,
	 * of length <numSubmodels>.
	 */
	ALC_MDLv10_Submodel** submodels;
} ALC_MDLv10_BodyPart;

/**
 * Function: ALC_MDLv10_BodyPart_Init
 *
 * Initialises a body part from uninitialised memory.
 *
 * This function should always be paired with a later call to <ALC_MDLv10_BodyPart_Deinit>,
 * to clean up any internal data held by the body part.
 *
 * *Do not* call this function on a body part which has already been initialised,
 * or undefined behaviour will result.
 *
 * Parameters:
 *
 * bodyPart - Body part to initialise.
 *
 * Returns:
 *
 * Input body part.
 */
API_AVIDLIB_CONTAINERS ALC_MDLv10_BodyPart* ALC_MDLv10_BodyPart_Init(ALC_MDLv10_BodyPart* bodyPart);

/**
 * Function: ALC_MDLv10_BodyPart_Deinit
 *
 * Deinitialises a previously initialised body part.
 *
 * This function should *always* be paired with a previous call to <ALC_MDLv10_BodyPart_Init>,
 * to clean up any internal data held by the body part.
 *
 * After the call, the body part should not be reused without being initialised again.
 *
 * If the passed body part was not previously initialised using <ALC_MDLv10_BodyPart_Init>,
 * undefined behaviour will result.
 *
 * Parameters:
 *
 * bodyPart - Body part to deinitialise.
 */
API_AVIDLIB_CONTAINERS void ALC_MDLv10_BodyPart_Deinit(ALC_MDLv10_BodyPart* bodyPart);

/**
 * Group: Submodels
 */

/**
 * Function: ALC_MDLv10_BodyPart_AllocateSubmodels
 *
 * Allocates and default-initialises a list of <ALC_MDLv10_Submodel> items in the body part.
 * If any list of submodels already exists, all submodels are deinitialised, and the list
 * is deallocated, before a new list is allocated.
 *
 * If numSubmodels is zero, any existing list is deallocated as above, but no new list
 * is allocated. The submodels list within the body part will be set to null, and null will
 * be returned.
 *
 * Parameters:
 *
 * bodyPart     - Body part within which to allocate the list of submodels.
 * numSubmodels - Number of submodels to allocate space for in the list.
 *
 * Returns:
 *
 * A pointer to the newly allocated list, or null if numSubmodels was zero.
 */
API_AVIDLIB_CONTAINERS ALC_MDLv10_Submodel* ALC_MDLv10_BodyPart_AllocateSubmodels(ALC_MDLv10_BodyPart* bodyPart, ALP_Size numSubmodels);

/**
 * Function: ALC_MDLv10_BodyPart_FreeSubmodels
 *
 * Frees any existing allocated submodels list in the body part. As part of the process,
 * all submodels are deinitialised.
 *
 * If no submodels list exists in the body part, this function does nothing.
 *
 * Parameters:
 *
 * bodyPart - Body part containing the list of submodels.
 */
API_AVIDLIB_CONTAINERS void ALC_MDLv10_BodyPart_FreeSubmodels(ALC_MDLv10_BodyPart* bodyPart);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CONTAINERS_MDLV10_BODYPART_H
