/**
 * About: Reader.h
 * This file defines functions for reading MDLv10 model files.
 */

#ifndef AVIDLIB_IO_MDLV10_READER_H
#define AVIDLIB_IO_MDLV10_READER_H

#include "AVIDLib_IO/LibExport.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Containers/MDLv10/Model.h"
#include "AVIDLib_IO/ReadResult.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Function: ALIO_MDLv10_Read
 *
 * Given an array of raw data, interprets the data as a v10 MDL file and
 * populates the provided MDLv10 model object.
 *
 * Parameters:
 *
 * inData    - Binary data to read.
 * inSize    - Size of the input data.
 * outResult - Struct filled out with the result of the read.
 * outModel  - Model to populate based on the input data.
 *
 * Returns:
 *
 * ALIO_ReaderError representing the result of the operation.
 * The value that is returned reflects the <ALIO_ReadResult.readError>
 * in outResult, for convenience.
 * A value of ALIO_READER_ERROR_NONE indicates that
 * the input data was read successfully; other values represent errors.
 */
API_AVIDLIB_IO ALIO_ReaderError ALIO_MDLv10_Read(const ALP_Byte* inData, ALP_Size inSize, ALIO_ReadResult* outResult, ALC_MDLv10_Model* outModel);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_IO_MDLV10_READER_H
