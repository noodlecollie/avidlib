#ifndef AVIDLIB_CORE_PTR_H
#define AVIDLIB_CORE_PTR_H

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uintptr_t ALC_UIntPtr;
typedef intptr_t ALC_IntPtr;
typedef ptrdiff_t ALC_PtrDiff;

#define ALC_NULL NULL

#define ALC_UINTPTR_MIN UINTPTR_MIN
#define ALC_UINTPTR_MAX UINTPTR_MAX
#define ALC_INTPTR_MIN INTPTR_MIN
#define ALC_INTPTR_MAX INTPTR_MAX
#define ALC_PTRFIFF_MAX PTRDIFF_MAX

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CORE_PTR_H
