/**
 * About: BoneWeight.h
 * Defines a mapping between a bone and an associated weight.
 */

#ifndef AVIDLIB_CONTAINERS_MDLV10_BONEWEIGHT_H
#define AVIDLIB_CONTAINERS_MDLV10_BONEWEIGHT_H

#include "AVIDLib_Containers/LibExport.h"
#include "AVIDLib_QMath/Types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _ALC_MDLv10_Bone;

/**
 * Struct: ALC_MDLv10_BoneWeight
 * Maps a weight to a bone.
 *
 * This struct links a referenced bone with an associated weight.
 * The bone is not owned by the struct.
 */
typedef struct _ALC_MDLv10_BoneWeight
{
	/**
	 * Variable: refBone
	 * The bone within the model, to which the weight applies.
	 */
	struct _ALC_MDLv10_Bone* refBone;

	/**
	 * Variable: weight
	 * Weight for this bone, specifying how much the bone's
	 * transform affects a given piece of geometry.
	 */
	ALQM_Scalar weight;
} ALC_MDLv10_BoneWeight;

/**
 * Function: ALC_MDLv10_BoneWeight_Reset
 *
 * Resets all components of the provided element to default values.
 *
 * Parameters:
 *
 * boneWeight - Element to reset.
 *
 * Returns:
 *
 * Input element.
 */
API_AVIDLIB_CONTAINERS ALC_MDLv10_BoneWeight* ALC_MDLv10_BoneWeight_Reset(ALC_MDLv10_BoneWeight* boneWeight);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CONTAINERS_MDLV10_BONEWEIGHT_H
