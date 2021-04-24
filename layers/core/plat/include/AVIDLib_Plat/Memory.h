/**
 * About: Memory.h
 * This file provides memory-related functions and helpers for the chosen platform.
 */

#ifndef AVIDLIB_PLAT_MEMORY_H
#define AVIDLIB_PLAT_MEMORY_H

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <string.h>
#include <stdlib.h>

#include "AVIDLib_Plat/Int.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Function: ALP_Malloc
 *
 * Allocates memory of the specified number of bytes, and returns a pointer to the memory.
 *
 * If the memory cannot be allocated, a null pointer is returned.
 *
 * Parameters:
 *
 * size - Number of bytes required by the allocation.
 *
 * Returns:
 *
 * Pointer to a block of allocated memory containing at least the number of
 * required bytes, or a null pointer if this memory could not be allocated.
 */
static inline void* ALP_Malloc(ALP_Size size)
{
	return malloc(size);
}

/**
 * Function: ALP_Free
 *
 * Frees a block of memory previously allocated by <ALP_Malloc>.
 *
 * If the pointer passed in is null, this function does nothing.
 *
 * If the pointer passed in was not previously allocated by <ALP_Malloc>,
 * or has already been freed by <ALP_Free>, undefined behaviour occurrs.
 *
 * Parameters:
 *
 * ptr - Pointer to previously allocated memory.
 */
static inline void ALP_Free(void* ptr)
{
	if ( ptr )
	{
		free(ptr);
	}
}

/**
 * Function: ALP_MemCpy
 *
 * Copies the specified number of bytes from src to dest, which should not overlap.
 *
 * If src and dest do overlap, use <ALP_MemMove> instead.
 *
 * Parameters:
 *
 * dest  - Destination buffer, which should be at least count bytes long.
 * src   - Source buffer, which should be at least count bytes long.
 * count - Number of bytes to copy from src to dest.
 *
 * Returns:
 *
 * dest.
 */
static inline void* ALP_MemCpy(void* restrict dest, const void* restrict src, ALP_Size count)
{
	return memcpy(dest, src, count);
}

/**
 * Function: ALP_MemMove
 *
 * Copies the specified number of bytes from src to dest. Src is allowed to
 * overlap with dest.
 *
 * If src and dest do not overlap, <ALP_MemCpy> will likely be more efficient.
 *
 * Parameters:
 *
 * dest  - Destination buffer, which should be at least count bytes long.
 * src   - Source buffer, which should be at least count bytes long.
 * count - Number of bytes to copy from src to dest.
 *
 * Returns:
 *
 * dest.
 */
static inline void* ALP_MemMove(void* dest, const void* src, ALP_Size count)
{
	return memmove(dest, src, count);
}

/**
 * Function: ALP_MemSet
 *
 * Sets num bytes from the specified address to hold the specified value.
 *
 * Parameters:
 *
 * ptr   - Address from which to begin setting byte values.
 * value - Value to set bytes to.
 * num   - Number of bytes to set the value of.
 *
 * Returns:
 *
 * ptr.
 */
static inline void* ALP_MemSet(void* ptr, ALP_UInt8 value, ALP_Size num)
{
	return memset(ptr, value, num);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_PLAT_MEMORY_H
