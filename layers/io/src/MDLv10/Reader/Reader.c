#include "AVIDLib_IO/MDLv10/Reader/Reader.h"
#include "MDLv10/IODefinitions.h"
#include "MDLv10/FileElements.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_Plat/Ptr.h"
#include "Validation.h"
#include "AVIDLib_Plat/String.h"

static ALIO_MDLv10_FileType DetermineFileType(ALIO_ReadContext* context)
{
	const ALIO_MDLv10_Header* header = (const ALIO_MDLv10_Header*)context->inputData;

	switch ( header->identifier )
	{
		case ALIO_MDLV10_GENFILE_IDENT:
		{
			return ALIO_MDLV10_FILE_GENERAL;
		}

		case ALIO_MDLV10_SEQFILE_IDENT:
		{
			return ALIO_MDLV10_FILE_SEQUENCE_CONTAINER;
		}

		default:
		{
			return ALIO_MDLV10_FILE_INVALID;
		}
	}
}

static ALP_Bool ValidateChunk(ALIO_ReadContext* context, const ALIO_CountOffsetPair* chunk, const ALP_Char* chunkName, ALP_Size itemSize)
{
	const ALIO_ValidationResult result = ALIO_Validation_ValidateFileChunk(context->inputLength, chunk, itemSize);

	if ( result != ALIO_VALIDATION_VALID )
	{
		ALIO_ReadContext_SetErrorFormat(context,
										ALIO_READER_ERROR_INVALID_STRUCTURE,
										"%s: %s",
										chunkName,
										ALIO_ValidationResult_Description(result));
	}

	return ALIO_ReadContext_GetReaderError(context) == ALIO_READER_ERROR_NONE;
}

static void PopulateBones(ALP_Size numBones, const ALIO_MDLv10_Bone* inBones, ALC_MDLv10_Bone* outBones)
{
	for ( ALP_Size index = 0; index < numBones; ++index )
	{
		// TODO: Move this to a function within the bone class.
		const ALIO_MDLv10_Bone* inBone = &inBones[index];
		ALC_MDLv10_Bone* outBone = &outBones[index];

		ALP_StrCpy(outBone->name, sizeof(outBone->name), inBone->name);

		outBone->refParentBone = inBone->parentBoneIndex >= 0
			? &outBones[inBone->parentBoneIndex]
			: ALP_NULL;

		// TODO: Add bone controller links once we set them up.

		outBone->defaultPosition.v[ALQM_VECX] = inBone->values[0];
		outBone->defaultPosition.v[ALQM_VECY] = inBone->values[1];
		outBone->defaultPosition.v[ALQM_VECZ] = inBone->values[2];

		outBone->defaultRotation.v[ALQM_VECX] = inBone->values[3];
		outBone->defaultRotation.v[ALQM_VECY] = inBone->values[4];
		outBone->defaultRotation.v[ALQM_VECZ] = inBone->values[5];

		outBone->positionScale.v[ALQM_VECX] = inBone->scales[0];
		outBone->positionScale.v[ALQM_VECY] = inBone->scales[1];
		outBone->positionScale.v[ALQM_VECZ] = inBone->scales[2];

		outBone->rotationScale.v[ALQM_VECX] = inBone->scales[3];
		outBone->rotationScale.v[ALQM_VECY] = inBone->scales[4];
		outBone->rotationScale.v[ALQM_VECZ] = inBone->scales[5];
	}
}

static ALP_Bool ValidateGeneralFile(ALIO_ReadContext* context, const ALIO_MDLv10_Header* header)
{
	// TODO: Make this data-driven?
	// TODO: Add more chunks as we code them up.
	return ValidateChunk(context, &header->bones, "Bones", sizeof(ALIO_MDLv10_Bone));

	// TODO: Validate individual elements
}

static void AllocateFileElements(const ALIO_MDLv10_Header* header, ALC_MDLv10_Model* outModel)
{
	// TODO: Make this data-driven?
	// TODO: Add more chunks as we code them up.
	ALC_MDLv10_Model_AllocateBones(outModel, header->bones.count);
}

static void PopulateFileElements(const ALIO_MDLv10_Header* header, ALC_MDLv10_Model* outModel)
{
	// TODO: Make this data-driven?
	// TODO: Add more chunks as we code them up.
	PopulateBones(header->bones.count,
				  (const ALIO_MDLv10_Bone*)(((const ALP_Byte*)header) + header->bones.offset),
				  outModel->bones);
}

static void ReadGeneralFile(ALIO_ReadContext* context, ALC_MDLv10_Model* outModel)
{
	const ALIO_MDLv10_Header* header = (const ALIO_MDLv10_Header*)context->inputData;

	if ( !ValidateGeneralFile(context, header) )
	{
		return;
	}

	AllocateFileElements(header, outModel);
	PopulateFileElements(header, outModel);
}

ALP_Bool ALIO_MDLv10_Read(ALIO_ReadContext* context, ALC_MDLv10_Model* outModel)
{
	if ( ALU_SANITY_VALID(context) )
	{
		do
		{
			if ( !outModel )
			{
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_EMPTY_OUTPUT, ALP_NULL);
				break;
			}

			if ( !ALIO_ReadContext_IsValid(context) )
			{
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_EMPTY_INPUT, ALP_NULL);
				break;
			}

			const ALIO_MDLv10_FileType fileType = DetermineFileType(context);

			if ( fileType == ALIO_MDLV10_FILE_INVALID )
			{
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_UNKNOWN_MAGIC, ALP_NULL);
				break;
			}

			if ( fileType != ALIO_MDLV10_FILE_GENERAL )
			{
				// TODO: Not supported yet.
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_UNIMPLEMENTED, "Non-general files are not yet supported.");
				break;
			}

			ReadGeneralFile(context, outModel);
		}
		while ( ALP_FALSE );

		return ALIO_ReadContext_GetReaderError(context) == ALIO_READER_ERROR_NONE;
	}

	// Context is not valid, so we can't set an error.
	return ALP_FALSE;
}
