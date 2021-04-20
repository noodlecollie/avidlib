#ifndef AVIDLIB_PLAT_PTR_H
#define AVIDLIB_PLAT_PTR_H

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uintptr_t ALP_UIntPtr;
typedef intptr_t ALP_IntPtr;
typedef ptrdiff_t ALP_PtrDiff;

#define ALP_NULL NULL

#define ALP_UINTPTR_MIN UINTPTR_MIN
#define ALP_UINTPTR_MAX UINTPTR_MAX
#define ALP_INTPTR_MIN INTPTR_MIN
#define ALP_INTPTR_MAX INTPTR_MAX
#define ALP_PTRFIFF_MAX PTRDIFF_MAX

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_PLAT_PTR_H
