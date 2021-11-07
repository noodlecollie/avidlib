/**
 * About: Submodel.h
 * Defines an MDLv10 submodel.
 */

#ifndef AVIDLIB_CONTAINERS_MDLV10_SUBMODEL_H
#define AVIDLIB_CONTAINERS_MDLV10_SUBMODEL_H

#include "AVIDLib_Containers/LibExport.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Struct: ALC_MDLv10_Submodel
 * Defines an MDLv10 submodel.
 *
 * A submodel is one variant of geometry that may be rendered in place
 * of a body part, depending on which of a model's body groups the game
 * engine has selected. See the <ALC_MDLv10_BodyPart> documentation for
 * more information on how body groups work.
 */
typedef struct _ALC_MDLv10_Submodel
{
	// TODO: Define
	int dummy;
} ALC_MDLv10_Submodel;

/**
 * Function: ALC_MDLv10_Submodel_Init
 *
 * Initialises a submodel from uninitialised memory.
 *
 * This function should always be paired with a later call to <ALC_MDLv10_BodyPart_Deinit>,
 * to clean up any internal data held by the submodel.
 *
 * *Do not* call this function on a submodel which has already been initialised,
 * or undefined behaviour will result.
 *
 * Parameters:
 *
 * submodel - Submodel to initialise.
 *
 * Returns:
 *
 * Input submodel.
 */
API_AVIDLIB_CONTAINERS ALC_MDLv10_Submodel* ALC_MDLv10_Submodel_Init(ALC_MDLv10_Submodel* submodel);

/**
 * Function: ALC_MDLv10_Submodel_Deinit
 *
 * Deinitialises a previously initialised submodel.
 *
 * This function should *always* be paired with a previous call to <ALC_MDLv10_Submodel_Deinit>,
 * to clean up any internal data held by the submodel.
 *
 * After the call, the submodel should not be reused without being initialised again.
 *
 * If the passed submodel was not previously initialised using <ALC_MDLv10_Submodel_Init>,
 * undefined behaviour will result.
 *
 * Parameters:
 *
 * submodel - Submodel to deinitialise.
 */
API_AVIDLIB_CONTAINERS void ALC_MDLv10_Submodel_Deinit(ALC_MDLv10_Submodel* submodel);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CONTAINERS_MDLV10_SUBMODEL_H
