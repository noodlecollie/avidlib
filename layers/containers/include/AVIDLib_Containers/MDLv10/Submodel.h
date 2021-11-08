/**
 * About: Submodel.h
 * Defines an MDLv10 submodel.
 */

#ifndef AVIDLIB_CONTAINERS_MDLV10_SUBMODEL_H
#define AVIDLIB_CONTAINERS_MDLV10_SUBMODEL_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_Containers/MDLv10/ContainerDefinitions.h"
#include "AVIDLib_Plat/Int.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: Include these headers once they exist.
struct _ALC_MDLv10_Mesh;
struct _ALC_MDLv10_Vertex;
struct _ALC_MDLv10_Normal;

/**
 * Struct: ALC_MDLv10_Submodel
 * Defines an MDLv10 submodel.
 *
 * A submodel is one variant of geometry that may be rendered in place
 * of a body part, depending on which of a model's body groups the game
 * engine has selected. See the <ALC_MDLv10_BodyPart> documentation for
 * more information on how body groups work.
 *
 * A submodel contains all vertices and normals that define the
 * geometry to be rendered. In addition, a submodel also contains a
 * list of meshes, which basically define the triangles that should
 * be drawn, and what textures should be used.
 */
typedef struct _ALC_MDLv10_Submodel
{
	/**
	 * Variable: name
	 * Name of this submodel. Should be unique within the model.
	 * Maximum number of characters, including the string terminator,
	 * is <ALC_MDLV10_SUBMODEL_NAME_LENGTH>.
	 */
	ALP_Char name[ALC_MDLV10_SUBMODEL_NAME_LENGTH];

	/**
	 * Variable: numMeshes
	 * Number of <meshes> owned by this submodel.
	 */
	ALP_Size numMeshes;

	/**
	 * Variable: meshes
	 * Array of meshes owned by this submodel,
	 * of length <numMeshes>.
	 */
	struct _ALC_MDLv10_Mesh* meshes;

	/**
	 * Variable: numVertices
	 * Number of <vertices> owned by this submodel.
	 */
	ALP_Size numVertices;

	/**
	 * Variable: vertices
	 * Array of vertices owned by this submodel,
	 * of length <numVertices>.
	 */
	struct _ALC_MDLv10_Vertex* vertices;

	/**
	 * Variable: numNormals
	 * Number of <normals> owned by this submodel.
	 */
	ALP_Size numNormals;

	/**
	 * Variable: normals
	 * Array of normals owned by this submodel,
	 * of length <numNormals>.
	 */
	struct _ALC_MDLv10_Normal* normals;
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
