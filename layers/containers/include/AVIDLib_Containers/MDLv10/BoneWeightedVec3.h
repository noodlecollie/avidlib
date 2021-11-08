/**
 * About: BoneWeightedVec3.h
 * Defines a 3D vector which may be weighted by multiple bone transforms.
 */

#ifndef AVIDLIB_CONTAINERS_MDLV10_BONEWEIGHTEDVEC3_H
#define AVIDLIB_CONTAINERS_MDLV10_BONEWEIGHTEDVEC3_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Containers/MDLv10/ContainerDefinitions.h"
#include "AVIDLib_Containers/MDLv10/BoneWeight.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Struct: ALC_MDLv10_BoneWeightedVec3
 * Defines a 3D vector which may be weighted by multiple bone transforms.
 *
 * This struct is used to represent both vertices and normals. The vertex
 * or normal is represented geometrically by a <ALQM_Vec3>, and may reference
 * a maximum of <ALC_MDLV10_MAX_VERT_BONE_WEIGHTS> bones to affect this
 * geometry.
 */
typedef struct _ALC_MDLv10_BoneWeightedVec3
{
	/**
	 * Variable: vec
	 * 3D vector representing a vertex position or normal direction.
	 */
	ALQM_Vec3 vec;

	/**
	 * Variable: boneWeights
	 * Collection of bones whose transforms may influence the
	 * vector for this vertex or normal.
	 * A maximum of <ALC_MDLV10_MAX_VERT_BONE_WEIGHTS> bones
	 * may have influence over the vector.
	 */
	ALC_MDLv10_BoneWeight boneWeights[ALC_MDLV10_MAX_VERT_BONE_WEIGHTS];
} ALC_MDLv10_BoneWeightedVec3;

/**
 * Function: ALC_MDLv10_BoneWeightedVec3_Reset
 *
 * Resets all components of the provided weighted Vec3 element to default values.
 *
 * Parameters:
 *
 * vec - Element to reset.
 *
 * Returns:
 *
 * Input element.
 */
API_AVIDLIB_CONTAINERS ALC_MDLv10_BoneWeightedVec3* ALC_MDLv10_BoneWeightedVec3_Reset(ALC_MDLv10_BoneWeightedVec3* vec);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CONTAINERS_MDLV10_BONEWEIGHTEDVEC3_H
