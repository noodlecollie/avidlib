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
 * "XMACRO" list tying error values to their readable descriptions.
 * See <ALIO_ReaderError> and <ALIO_ReaderError_Description>.
 */
#define ALIO_READER_ERROR_LIST \
	ALIO_LIST_ITEM(ALIO_READER_ERROR_NONE = 0, "Reading was successful.") \
	ALIO_LIST_ITEM(ALIO_READER_ERROR_UNIMPLEMENTED, "The requested operation was not implemented.") \
	ALIO_LIST_ITEM(ALIO_READER_ERROR_INTERNAL, "An unexpected internal error occurred when reading.") \
	ALIO_LIST_ITEM(ALIO_READER_ERROR_EMPTY_INPUT, "No input data was provided.") \
	ALIO_LIST_ITEM(ALIO_READER_ERROR_EMPTY_OUTPUT, "No output container was provided.") \
	ALIO_LIST_ITEM(ALIO_READER_ERROR_UNKNOWN_MAGIC, "The type of the input file could not be determined.") \
	ALIO_LIST_ITEM(ALIO_READER_ERROR_INVALID_STRUCTURE, "The internal structure of the input file was not valid.")

#define ALIO_LIST_ITEM(value, description) value,

/**
 * Enum: ALIO_ReaderError
 * ALIO_READER_ERROR_NONE              - Reading was successful.
 * ALIO_READER_ERROR_UNIMPLEMENTED     - The requested operation was not implemented.
 * ALIO_READER_ERROR_INTERNAL          - An unexpected internal error occurred when reading.
 * ALIO_READER_ERROR_EMPTY_INPUT       - No input data was provided.
 * ALIO_READER_ERROR_EMPTY_OUTPUT      - No output container was provided.
 * ALIO_READER_ERROR_UNKNOWN_MAGIC     - The type of the input file could not be determined.
 * ALIO_READER_ERROR_INVALID_STRUCTURE - The internal structure of the input file was not valid.
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
