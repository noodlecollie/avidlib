#include "AVIDLib_IO/ReadContext.h"
#include "AVIDLib_Internal_Util/Memory.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Plat/String.h"

void ALIO_ReadContext_Reset(ALIO_ReadContext* context)
{
	if ( ALU_SANITY_VALID(context) )
	{
		ALU_ZERO_STRUCT(context);
		context->readError = ALIO_READER_ERROR_NONE;
	}
}

void ALIO_ReadContext_Prepare(ALIO_ReadContext* context, const ALP_Byte* inputData, ALP_Size inputLength)
{
	if ( ALU_SANITY_VALID(context) )
	{
		ALIO_ReadContext_Reset(context);

		if ( inputData && inputLength > 0 )
		{
			context->inputData = inputData;
			context->inputLength = inputLength;
		}
	}
}

ALP_Bool ALIO_ReadContext_IsValid(const ALIO_ReadContext* context)
{
	return ALU_TSANITY_VALID(context,
							 context->inputData && context->inputLength > 0,
							 ALP_FALSE);
}

ALIO_ReaderError ALIO_ReadContext_GetReaderError(const ALIO_ReadContext* context)
{
	return ALU_TSANITY_VALID(context,
							 context->readError,
							 ALIO_READER_ERROR_INTERNAL);
}

const ALP_Char* ALIO_ReadContext_GetReaderErrorString(const ALIO_ReadContext* context)
{
	return ALIO_ReaderError_Description(ALIO_ReadContext_GetReaderError(context));
}

const ALP_Char* ALIO_ReadContext_GetErrorDetails(const ALIO_ReadContext* context)
{
	return ALU_TSANITY_VALID(context,
							 context->errorDetails,
							 ALP_NULL);
}

void ALIO_ReadContext_SetError(ALIO_ReadContext* context, ALIO_ReaderError error, const ALP_Char* errorString)
{
	if ( ALU_SANITY_VALID(context) )
	{
		context->readError = error;

		if ( errorString )
		{
			ALP_StrCpy(context->errorDetails, sizeof(context->errorDetails), errorString);
		}
		else
		{
			context->errorDetails[0] = '\0';
		}
	}
}

void ALIO_ReadContext_SetErrorFormat(ALIO_ReadContext* context, ALIO_ReaderError error, const ALP_Char* format, ...)
{
	if ( ALU_SANITY_VALID(context) )
	{
		context->readError = error;

		if ( format )
		{
			ALP_VAList args;
			ALP_VA_START(args, format);
			ALP_VSPrintF(context->errorDetails, sizeof(context->errorDetails), format, args);
			ALP_VA_END(args);
		}
		else
		{
			context->errorDetails[0] = '0';
		}
	}
}
