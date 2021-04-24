#ifndef AVIDLIB_INTERNAL_UTIL_MEMORY_H
#define AVIDLIB_INTERNAL_UTIL_MEMORY_H

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <string.h>
#include <stdlib.h>

#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Plat/Memory.h"

#ifdef __cplusplus
extern "C" {
#endif

// Records the file and line at which the allocation call was made, for debugging purposes.
static inline void* ALU_MallocFrom(ALP_Size size, const char* file, int line)
{
	void* const ptr = ALP_Malloc(size);
	ALU_CHECK_MALLOC_RESULT(ptr, size, file, line);
	return ptr;
}

// Records the file and line at which the free call was made, for debugging purposes.
static inline void ALU_FreeFrom(void* ptr, const char* file, int line)
{
	ALU_UNUSED(file);
	ALU_UNUSED(line);

	ALP_Free(ptr);
}

#define ALU_MALLOC(size) ALU_MallocFrom(size, __FILE__, __LINE__)
#define ALU_FREE(ptr) ALU_FreeFrom(ptr, __FILE__, __LINE__)
#define ALU_ZERO_STRUCT(structPtr) ALP_MemSet(structPtr, 0, sizeof(*(structPtr)))

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_INTERNAL_UTIL_MEMORY_H
