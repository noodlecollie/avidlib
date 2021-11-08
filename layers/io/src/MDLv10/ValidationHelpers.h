#ifndef AVIDLIB_IO_MDLV10_VALIDATIONHELPERS_H
#define AVIDLIB_IO_MDLV10_VALIDATIONHELPERS_H

#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_IO/ReadContext.h"
#include "FormatCommon/FileElementHelpers.h"
#include "MDLv10/Header.h"
#include "MDLv10/Bone.h"
#include "Validation.h"

typedef ALP_Bool (*ALIO_MDLv10_ItemValidationFunc)(const struct _ALIO_MDLv10_Header* header,
												   const void* element,
												   ALP_Char* errorString,
												   ALP_Size errorStringSize);

typedef struct _ALIO_MDLv10_VDesc_FileChunk
{
	ALP_Size headerCOPOffset;
	const ALP_Char* chunkName;
	ALP_Size itemSize;
	ALIO_MDLv10_ItemValidationFunc validationFunc;
} ALIO_MDLv10_VDesc_FileChunk;

static const ALIO_MDLv10_VDesc_FileChunk ALIO_MDLV10_VDESC_CHUNKS[] =
{
	{ ALP_OFFSETOF(ALIO_MDLv10_Header, bones), "Bones", sizeof(ALIO_MDLv10_Bone), &ALIO_MDLv10_Bone_ValidateGeneric },
	{ ALP_OFFSETOF(ALIO_MDLv10_Header, boneControllers), "Bone Controllers", sizeof(ALIO_MDLv10_BoneController), &ALIO_MDLv10_BoneController_ValidateGeneric }
};

static inline ALP_Bool ALIO_MDLv10_ValidateAllChunks(ALIO_ReadContext* context)
{
	if ( ALU_SANITY_VALID(context) )
	{
		for ( ALP_Size chunkIndex = 0; chunkIndex < ALU_ARRAY_LENGTH(ALIO_MDLV10_VDESC_CHUNKS); ++chunkIndex )
		{
			const ALIO_MDLv10_VDesc_FileChunk* vDesc = &ALIO_MDLV10_VDESC_CHUNKS[chunkIndex];
			const ALIO_CountOffsetPair* cop = (const ALIO_CountOffsetPair*)(context->inputData + vDesc->headerCOPOffset);

			const ALIO_ValidationResult result = ALIO_Validation_ValidateFileChunk(context->inputLength, cop, vDesc->itemSize);

			if ( result != ALIO_VALIDATION_VALID )
			{
				ALIO_ReadContext_SetErrorFormat(context,
												ALIO_READER_ERROR_INVALID_STRUCTURE,
												"%s: %s",
												vDesc->chunkName,
												ALIO_ValidationResult_Description(result));
				break;
			}
		}

		return ALIO_ReadContext_GetReaderError(context) == ALIO_READER_ERROR_NONE;
	}

	return ALP_FALSE;
}

static inline ALP_Bool ALIO_MDLv10_ValidateAllItems(ALIO_ReadContext* context)
{
	if ( ALU_SANITY_VALID(context) )
	{
		for ( ALP_Size chunkIndex = 0; chunkIndex < ALU_ARRAY_LENGTH(ALIO_MDLV10_VDESC_CHUNKS); ++chunkIndex )
		{
			const ALIO_MDLv10_VDesc_FileChunk* vDesc = &ALIO_MDLV10_VDESC_CHUNKS[chunkIndex];

			if ( !vDesc->validationFunc )
			{
				continue;
			}

			const ALIO_CountOffsetPair* cop = (const ALIO_CountOffsetPair*)(context->inputData + vDesc->headerCOPOffset);

			for ( ALP_Size itemIndex = 0; itemIndex < cop->count; ++itemIndex )
			{
				ALP_Char errorString[64] = "Unknown error.";
				const ALP_Size itemOffset = cop->offset + (vDesc->itemSize * itemIndex);

				if ( !(*vDesc->validationFunc)((const ALIO_MDLv10_Header*)context->inputData,
											   (const void*)(context->inputData + itemOffset),
											   errorString,
											   sizeof(errorString)) )
				{
					ALIO_ReadContext_SetErrorFormat(context,
													ALIO_READER_ERROR_INVALID_STRUCTURE,
													"%s[%u]: %s",
													vDesc->chunkName,
													itemIndex,
													errorString);

					break;
				}
			}

			if ( ALIO_ReadContext_GetReaderError(context) != ALIO_READER_ERROR_NONE )
			{
				break;
			}
		}

		return ALIO_ReadContext_GetReaderError(context) == ALIO_READER_ERROR_NONE;
	}

	return ALP_FALSE;
}

#endif // AVIDLIB_IO_MDLV10_VALIDATIONHELPERS_H
