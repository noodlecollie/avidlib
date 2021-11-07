/**
 * About: BoneController.h
 * Defines an MDLv10 bone controller.
 */

#ifndef AVIDLIB_IO_MDLV10_BONECONTROLLER_H
#define AVIDLIB_IO_MDLV10_BONECONTROLLER_H

#include "AVIDLib_Plat/Float.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Plat/Bool.h"

struct _ALIO_MDLv10_Header;
struct _ALC_MDLv10_Model;
struct _ALC_MDLv10_BoneController;

#pragma pack(push, 1)

/**
 * Struct: ALIO_MDLv10_BoneController
 * Defines the representation of a bone controller with an MDLv10 model file.
 */
typedef struct _ALIO_MDLv10_BoneController
{
	/**
	 * Variable: bone
	 * Bone affected by this controller.
	 */
	ALP_UInt32 boneIndex;

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
	ALP_Float32 start;

	/**
	 * Variable: end
	 * Ending value for this controller's motion range.
	 */
	ALP_Float32 end;

	/**
	 * Variable: unused
	 * Was "rest", but appears to be unused.
	 */
	ALP_Int32 unused;

	/**
	 * Variable: channel
	 * Which controller channel this bone controller maps to
	 * on the entity which uses this model.
	 */
	ALP_UInt32 channel;
} ALIO_MDLv10_BoneController;

#pragma pack(pop)

ALP_Bool ALIO_MDLv10_BoneController_Validate(const struct _ALIO_MDLv10_Header* header,
											 const ALIO_MDLv10_BoneController* boneController,
											 ALP_Char* errorString,
											 ALP_Size errorStringSize);

ALP_Bool ALIO_MDLv10_BoneController_ValidateGeneric(const struct _ALIO_MDLv10_Header* header,
													const void* boneController,
													ALP_Char* errorString,
													ALP_Size errorStringSize);

void ALIO_MDLv10_BoneController_ToContainerElement(const ALIO_MDLv10_BoneController* inController,
												   struct _ALC_MDLv10_BoneController* outController,
												   struct _ALC_MDLv10_Model* outModel);

#endif // AVIDLIB_IO_MDLV10_BONECONTROLLER_H
