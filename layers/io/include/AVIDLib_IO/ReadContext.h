/**
 * About: ReadContext.h
 * Defines a struct encapsulating the required data for reading an asset.
 */

#ifndef AVIDLIB_IO_READCONTEXT_H
#define AVIDLIB_IO_READCONTEXT_H

#include "AVIDLib_IO/LibExport.h"
#include "AVIDLib_IO/ReaderErrors.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Plat/Bool.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constant: ALIO_READCONTEXT_MAX_ERROR_DETAIL_LENGTH
 * Defines the maximum length for an error detail string,
 * including the null terminator.
 */
#define ALIO_READCONTEXT_MAX_ERROR_DETAIL_LENGTH 128

/**
 * Struct: ALIO_ReadContext
 *
 * Encapsulates the required data for reading an asset.
 */
typedef struct _ALIO_ReadContext
{
	/**
	 * Variable: inputData
	 * Pointer to raw input file data.
	 * This data is not owned by the context.
	 */
	const ALP_Byte* inputData;

	/**
	 * Variable: inputLength
	 * Length of the raw input file data.
	 */
	ALP_Size inputLength;

	/**
	 * Variable: readError
	 * Value representing the result of the read operation.
	 * A value of ALIO_READER_ERROR_NONE indicates that
	 * the input data was read successfully; other values represent errors.
	 */
	ALIO_ReaderError readError;

	/**
	 * Variable: errorDetails
	 * Further information about the specifics of the error that occurred.
	 * Useful as feedback for the user.
	 */
	ALP_Char errorDetails[ALIO_READCONTEXT_MAX_ERROR_DETAIL_LENGTH];
} ALIO_ReadContext;

/**
 * Function: ALIO_ReadContext_Reset
 *
 * Resets all data in the read context.
 *
 * Parameters:
 *
 * context - Context object to reset.
 */
API_AVIDLIB_IO void ALIO_ReadContext_Reset(ALIO_ReadContext* context);

/**
 * Function: ALIO_ReadContext_Prepare
 *
 * Prepares the read context with an input file and length.
 * All other data in the context is reset.
 *
 * The input data pointer must be valid, and the input length
 * must be greater than zero. If this is not the case,
 * <ALIO_ReadContext.inputData> will be set to null, and
 * <ALIO_ReadContext.inputLength> will be set to zero.
 *
 * Parameters:
 *
 * context     - Context object to prepare.
 * inputData   - Raw data of the input file.
 * inputLength - Length of the input file data.
 */
API_AVIDLIB_IO void ALIO_ReadContext_Prepare(ALIO_ReadContext* context, const ALP_Byte* inputData, ALP_Size inputLength);

/**
 * Function: ALIO_ReadContext_IsValid
 *
 * Returns whether the read context is valid (ie. that it has
 * a valid pointer to input file data, and that the data length
 * is greater than zero.
 *
 * Parameters:
 *
 * context - Context to check validity state of.
 *
 * Returns:
 *
 * True if the context is valid, or false otherwise.
 */
API_AVIDLIB_IO ALP_Bool ALIO_ReadContext_IsValid(const ALIO_ReadContext* context);

/**
 * Function: ALIO_ReadContext_GetReaderError
 *
 * Returns the reader error set on the context.
 *
 * Parameters:
 *
 * context - Context from which to return the error code.
 *
 * Returns:
 *
 * Reader error code from the context.
 */
API_AVIDLIB_IO ALIO_ReaderError ALIO_ReadContext_GetReaderError(const ALIO_ReadContext* context);

/**
 * Function: ALIO_ReadContext_GetErrorDetails
 *
 * Returns a string containing details about the error
 * held in the context.
 *
 * Parameters:
 *
 * context - Context from which to return the error details string.
 *
 * Returns:
 *
 * String providing more information about the read error.
 */
API_AVIDLIB_IO const ALP_Char* ALIO_ReadContext_GetErrorDetails(const ALIO_ReadContext* context);

/**
 * Function: ALIO_ReadContext_SetError
 *
 * Sets the provided error code and string on the context.
 *
 * The error string may be null, in which case the error detail
 * string on the context will be cleared.
 *
 * Parameters:
 *
 * context     - Context on which to set the error information.
 * error       - Error code to set.
 * errorString - Description of the error, to be set as the error detail string.
 */
API_AVIDLIB_IO void ALIO_ReadContext_SetError(ALIO_ReadContext* context, ALIO_ReaderError error, const ALP_Char* errorString);

/**
 * Function: ALIO_ReadContext_SetErrorFormat
 *
 * Sets the provided error code on the context, and sets
 * the error detail string according to the provided format.
 *
 * Parameters:
 *
 * context - Context on which to set the error information.
 * error   - Error code to set.
 * format  - Printf-style format string.
 * ...     - Variadic arguments alongside the format string.
 */
API_AVIDLIB_IO void ALIO_ReadContext_SetErrorFormat(ALIO_ReadContext* context, ALIO_ReaderError error, const ALP_Char* format, ...);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_IO_READCONTEXT_H
