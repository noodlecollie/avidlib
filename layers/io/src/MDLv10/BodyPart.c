#include "MDLv10/BodyPart.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Plat/String.h"
#include "AVIDLib_Containers/MDLv10/BodyPart.h"
#include "AVIDLib_Containers/MDLv10/Model.h"

ALP_Bool ALIO_MDLv10_BodyPart_Validate(const struct _ALIO_MDLv10_Header* header,
                                       ALP_Size fileSize,
                                       const ALIO_MDLv10_BodyPart* bodyPart,
                                       ALP_Char* errorString,
                                       ALP_Size errorStringSize)
{
	if ( ALU_SANITY_VALID(header && bodyPart && errorString && errorStringSize > 0) )
	{
		// TODO: Really this should also be checking if offset + size of element is > file size
		if ( bodyPart->submodelOffset >= fileSize )
		{
			ALP_StrCpy(errorString, errorStringSize, "Submodel offset was out of range.");
			return ALP_FALSE;
		}

		return ALP_TRUE;
	}

	return ALP_FALSE;
}

ALP_Bool ALIO_MDLv10_BodyPart_ValidateGeneric(const struct _ALIO_MDLv10_Header* header,
                                              ALP_Size fileSize,
                                              const void* bodyPart,
                                              ALP_Char* errorString,
                                              ALP_Size errorStringSize)
{
	return ALIO_MDLv10_BodyPart_Validate(header,
	                                     fileSize,
	                                     (const ALIO_MDLv10_BodyPart*)bodyPart,
	                                     errorString,
	                                     errorStringSize);
}

void ALIO_MDLv10_BodyPart_ToContainerElement(const ALIO_MDLv10_BodyPart* inBodyPart,
                                             struct _ALC_MDLv10_BodyPart* outBodyPart,
                                             struct _ALC_MDLv10_Model* outModel)
{
	if ( ALU_SANITY_VALID(inBodyPart && outBodyPart && outModel) )
	{
		ALP_StrCpy(outBodyPart->name, sizeof(outBodyPart->name), inBodyPart->name);
	}
}
