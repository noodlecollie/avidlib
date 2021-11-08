/**
 * About: FileElementHelpers.h
 * Defines useful helper types for reading files, which are common to multiple file formats.
 */

#ifndef AVIDLIB_IO_FILEELEMENTHELPERS_H
#define AVIDLIB_IO_FILEELEMENTHELPERS_H

#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Plat/Float.h"

#pragma pack(push, 1)

/**
 * Typedef: ALIO_RawVec3
 * Convenience typedef for an array of 3 floats.
 */
typedef ALP_Float32 ALIO_RawVec3[3];

/**
 * Struct: ALIO_CountOffsetPair
 * A struct holding an element count, along with a file offset
 * at which the element data can be found.
 */
typedef struct _ALIO_CountOffsetPair
{
	/**
	 * Variable: count
	 * How many of a certain element are present in the file.
	 */
	ALP_UInt32 count;

	/**
	 * Variable: offset
	 * The offset from the beginning of the file at which element
	 * data can be found. Element data is stored consecutively
	 * from this offset, and the length of the entire block is
	 * equal to <ALIO_CountOffsetPair.count> * sizeof(element).
	 */
	ALP_UInt32 offset;
} ALIO_CountOffsetPair;

/**
 * Struct: ALIO_BBox
 * A struct representing an axis-aligned bounding box,
 * defined by a min and max vector.
 */
typedef struct _ALIO_BBox
{
	/**
	 * Variable: min
	 * The minimum point of the bounding box.
	 */
	ALIO_RawVec3 min;

	/**
	 * Variable: max
	 * The maximum point of the bounding box.
	 */
	ALIO_RawVec3 max;
} ALIO_BBox;

#define ALIO_CHUNK_CDATA(headerPtr, chunkName) ((const void*)(((const ALP_Byte*)(headerPtr)) + (headerPtr)->chunkName.offset))

#pragma pack(pop)

#endif // AVIDLIB_IO_FILEELEMENTHELPERS_H
