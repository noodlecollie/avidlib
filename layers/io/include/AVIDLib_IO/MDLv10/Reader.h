/**
 * About: Reader.h
 * This file defines functions for reading MDLv10 model files.
 */

#ifndef AVIDLIB_IO_MDLV10_READER_H
#define AVIDLIB_IO_MDLV10_READER_H

#include "AVIDLib_IO/LibExport.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Containers/MDLv10/Model.h"
#include "AVIDLib_IO/ReadContext.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Function: ALIO_MDLv10_Read
 *
 * Given read context, interprets the input data as a v10 MDL file and
 * populates the provided MDLv10 model object.
 *
 * Parameters:
 *
 * readContext - Contextual data for this read operation.
 * outModel    - Model to populate based on the input data.
 *
 * Returns:
 *
 * True if the result of the read was ALIO_READER_ERROR_NONE,
 * or false if some read error occurred. The actual error code,
 * along with any other error details, is set on the context.
 */
API_AVIDLIB_IO ALP_Bool ALIO_MDLv10_Read(ALIO_ReadContext* context, ALC_MDLv10_Model* outModel);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_IO_MDLV10_READER_H
