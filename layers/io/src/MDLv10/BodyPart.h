/**
 * About: BodyPart.h
 * Defines an MDLv10 body part.
 */

#ifndef AVIDLIB_IO_MDLV10_BODYPART_H
#define AVIDLIB_IO_MDLV10_BODYPART_H

#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Plat/Bool.h"
#include "MDLv10/IODefinitions.h"

struct _ALIO_MDLv10_Header;
struct _ALC_MDLv10_Model;
struct _ALC_MDLv10_BodyPart;

#pragma pack(push, 1)

/**
 * Struct: ALIO_MDLv10_BodyPart
 * Defines the representation of a body part with an MDLv10 model file.
 */
typedef struct _ALIO_MDLv10_BodyPart
{
	/**
	 * Variable: name
	 * Name of the body part. Should be unique within the model.
	 * Maximum number of characters, including the string terminator,
	 * is <ALIO_MDLV10_BODYPART_NAME_LENGTH>.
	 */
	ALP_Char name[ALIO_MDLV10_BODYPART_NAME_LENGTH];

	/**
	 * Variable: numSubmodels
	 * Number of submodels available for this body part.
	 * The submodel data can be found at <submodelOffset>
	 * bytes from the beginning of the file header.
	 */
	ALP_UInt32 numSubmodels;

	/**
	 * Variable: base
	 * When selecting a body in game code, the index of the
	 * body is divided by this value to convert it to an
	 * index that is local to this body part. For example:
	 *
	 * ======= C =======
	 * int submodelIndex = entityBodyIndex / bodyPart->base;
	 * submodelIndex %= bodyPart->numSubmodels;
	 * =================
	 *
	 * As the entity's body index increases, it will increase
	 * the submodel index for different body parts at different
	 * rates, allowing all body group permutations to be
	 * cycled through.
	 */
	ALP_UInt32 base;

	/**
	 * Variable: submodelOffset
	 * The submodels referenced by this body part begin at
	 * this many bytes from the beginning of the file header.
	 */
	ALP_UInt32 submodelOffset;
} ALIO_MDLv10_BodyPart;

#pragma pack(pop)

ALP_Bool ALIO_MDLv10_BodyPart_Validate(const struct _ALIO_MDLv10_Header* header,
                                       ALP_Size fileSize,
                                       const ALIO_MDLv10_BodyPart* bodyPart,
                                       ALP_Char* errorString,
                                       ALP_Size errorStringSize);

ALP_Bool ALIO_MDLv10_BodyPart_ValidateGeneric(const struct _ALIO_MDLv10_Header* header,
                                              ALP_Size fileSize,
                                              const void* bodyPart,
                                              ALP_Char* errorString,
                                              ALP_Size errorStringSize);

void ALIO_MDLv10_BodyPart_ToContainerElement(const ALIO_MDLv10_BodyPart* inBodyPart,
                                             struct _ALC_MDLv10_BodyPart* outBodyPart,
                                             struct _ALC_MDLv10_Model* outModel);

#endif // AVIDLIB_IO_MDLV10_BODYPART_H
