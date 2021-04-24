/**
 * About: ReadResult.h
 * Defines a struct encapsulating the result of a read operation.
 */

#ifndef AVIDLIB_IO_READRESULT_H
#define AVIDLIB_IO_READRESULT_H

#include "AVIDLib_IO/LibExport.h"
#include "AVIDLib_IO/ReaderErrors.h"

/**
 * Struct: ALIO_ReadResult
 *
 * Encapsulates the result of a read operation.
 */
typedef struct _ALIO_ReadResult
{
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
	char errorDetails[64];
} ALIO_ReadResult;

/**
 * Function: ALIO_ReadResult_Reset
 *
 * Resets all data in the read result.
 *
 * Parameters:
 *
 * result - Result object to reset.
 */
API_AVIDLIB_IO void ALIO_ReadResult_Reset(ALIO_ReadResult* result);

#endif // AVIDLIB_IO_READRESULT_H
