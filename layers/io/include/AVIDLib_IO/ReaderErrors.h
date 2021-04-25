/**
 * About: ReaderErrors.h
 * This file defines identifiers for different possible errors when reading model files.
 */

#ifndef AVIDLIB_IO_READERERRORS_H
#define AVIDLIB_IO_READERERRORS_H

#include "AVIDLib_IO/LibExport.h"
#include "AVIDLib_Plat/Int.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Macro: ALIO_READER_ERROR_LIST
 * "XMACRO" list typing error values to their readable descriptions.
 * See <ALIO_ReaderError> and <ALIO_ReaderError_Description>.
 */
#define ALIO_READER_ERROR_LIST \
	ALIO_LIST_ITEM(ALIO_READER_ERROR_NONE = 0, "No reader error.") \
	ALIO_LIST_ITEM(ALIO_READER_ERROR_UNIMPLEMENTED, "The requested operation was not implemented.")

#define ALIO_LIST_ITEM(value, description) value,

/**
 * Enum: ALIO_ReaderError
 * ALIO_READER_ERROR_NONE            - No errors were encountered when reading the model file.
 * ALIO_READER_ERROR_UNIMPLEMENTED - The requested operation was not implemented.
 */
typedef enum _ALIO_ReaderError
{
	ALIO_READER_ERROR_LIST

	ALIO_READER_ERROR__COUNT
} ALIO_ReaderError;

#undef ALIO_LIST_ITEM

/**
 * Function: ALIO_ReaderError_Description
 *
 * Returns a human-readable description of the specified error.
 *
 * Parameters:
 *
 * error - Error to fetch the description string for.
 *
 * Returns:
 *
 * Descriptive string for the error.
 */
API_AVIDLIB_IO const ALP_Char* ALIO_ReaderError_Description(ALIO_ReaderError error);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_IO_READERERRORS_H
