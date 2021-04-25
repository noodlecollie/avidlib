#include "AVIDLib_IO/MDLv10/Reader/Reader.h"
#include "MDLv10/Definitions.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_Plat/Ptr.h"

static ALIO_MDLv10_FileType DetermineFileType(ALIO_ReadContext* context)
{
	switch ( *((ALP_Int32*)context->inputData) )
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

static void ReadGeneralFile(ALIO_ReadContext* context, ALC_MDLv10_Model* outModel)
{
	// TODO
	ALU_UNUSED(context);
	ALU_UNUSED(outModel);
	ALIO_ReadContext_SetError(context, ALIO_READER_ERROR_UNIMPLEMENTED, "TODO: Implement");
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
