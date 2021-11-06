#include "AVIDLib_IO/MDLv10/Reader/Reader.h"
#include "MDLv10/IODefinitions.h"
#include "MDLv10/Header.h"
#include "MDLv10/Bone.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_Plat/Ptr.h"
#include "Validation.h"
#include "AVIDLib_Plat/String.h"
#include "MDLv10/ValidationHelpers.h"

static inline ALP_Bool EnoughDataToReadHeader(const ALIO_ReadContext* context)
{
	return ALIO_ReadContext_IsValid(context) && context->inputLength >= sizeof(ALIO_MDLv10_Header);
}

static inline ALP_UInt32 GetFileVersion(const ALIO_ReadContext* context)
{
	return ((const ALIO_MDLv10_Header*)context->inputData)->version;
}

static ALIO_MDLv10_FileType DetermineFileType(const ALIO_ReadContext* context)
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

		case ALIO_MDLV10_AFTERBURNER_IDENT:
		{
			return ALIO_MDLV10_FILE_AFTERBURNER;
		}

		default:
		{
			return ALIO_MDLV10_FILE_INVALID;
		}
	}
}

static void PopulateBones(const ALIO_MDLv10_Bone* inBones, ALC_MDLv10_Model* outModel)
{
	for ( ALP_Size index = 0; index < outModel->numBones; ++index )
	{
		ALIO_MDLv10_Bone_ToContainerElement(&inBones[index], &outModel->bones[index], outModel);
	}
}

static ALP_Bool ValidateGeneralFile(ALIO_ReadContext* context)
{
	return ALIO_MDLv10_ValidateAllChunks(context) && ALIO_MDLv10_ValidateAllItems(context);
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
	PopulateBones((const ALIO_MDLv10_Bone*)ALIO_CHUNK_OFFSET(header, bones), outModel);
}

static void ReadGeneralFile(ALIO_ReadContext* context, ALC_MDLv10_Model* outModel)
{
	const ALIO_MDLv10_Header* header = (const ALIO_MDLv10_Header*)context->inputData;

	if ( !ValidateGeneralFile(context) )
	{
		return;
	}

	AllocateFileElements(header, outModel);
	PopulateFileElements(header, outModel);
}

ALP_Bool ALIO_MDLv10_Identify(const ALIO_ReadContext* context)
{
	if ( ALU_SANITY_VALID(context) )
	{
		return EnoughDataToReadHeader(context) &&
		       DetermineFileType(context) != ALIO_MDLV10_FILE_INVALID &&
		       GetFileVersion(context) == ALIO_MDLV10_FILE_VERSION;
	}

	return ALP_FALSE;
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

			if ( !EnoughDataToReadHeader(context) )
			{
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_INSUFFICIENT_DATA, ALP_NULL);
				break;
			}

			const ALIO_MDLv10_FileType fileType = DetermineFileType(context);

			if ( fileType == ALIO_MDLV10_FILE_INVALID )
			{
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_UNKNOWN_MAGIC, ALP_NULL);
				break;
			}

			if ( fileType == ALIO_MDLV10_FILE_SEQUENCE_CONTAINER )
			{
				// TODO: Not supported yet.
				ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_UNIMPLEMENTED, "Sequence container files are not yet supported.");
				break;
			}

			const ALP_UInt32 fileVersion = GetFileVersion(context);

			if ( fileVersion != ALIO_MDLV10_FILE_VERSION )
			{
				ALIO_ReadContext_SetErrorFormat(context,
				                                ALIO_READER_ERROR_UNSUPPORTED_VERSION,
				                                "Expected version %u but got version %u.",
				                                ALIO_MDLV10_FILE_VERSION,
				                                fileVersion);

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
