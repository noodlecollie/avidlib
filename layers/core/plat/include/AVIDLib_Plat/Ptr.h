/**
 * About: Ptr.h
 * This file provides pointer-related definitions for the chosen platform.
 */

#ifndef AVIDLIB_PLAT_PTR_H
#define AVIDLIB_PLAT_PTR_H

/**
 * For now, we just use platform headers.
 * If we get to a point in future where we need to swap this out
 * depending on our target platform, we can add ifdefs.
 */
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Types: Pointer Arithmetic Types
 * ALP_UIntPtr - Unsigned integer representation of a pointer.
 * ALP_IntPtr  - Signed integer representation of a pointer.
 * ALP_PtrDiff - Type representing the numerical difference between two pointers.
 */
typedef uintptr_t ALP_UIntPtr;
typedef intptr_t ALP_IntPtr;
typedef ptrdiff_t ALP_PtrDiff;

/**
 * Type: ALP_Void
 * AVIDLib void type, eg. for pointers to arbitrary data.
 */
typedef void ALP_Void;

/**
 * Constant: ALP_NULL
 * AVIDLib null pointer constant.
 */
#define ALP_NULL NULL

/**
 * Constants: Pointer Arithmetic Ranges
 * ALP_UINTPTR_MIN - Minimum value of an ALP_UIntPtr type.
 * ALP_UINTPTR_MAX - Maximum value of an ALP_UIntPtr type.
 * ALP_INTPTR_MIN  - Minimum value of an ALP_IntPtr type.
 * ALP_INTPTR_MAX  - Maximum value of an ALP_IntPtr type.
 * ALP_PTRDIFF_MAX - Maximum value of an ALP_PtrDiff type.
 */
#define ALP_UINTPTR_MIN UINTPTR_MIN
#define ALP_UINTPTR_MAX UINTPTR_MAX
#define ALP_INTPTR_MIN INTPTR_MIN
#define ALP_INTPTR_MAX INTPTR_MAX
#define ALP_PTRDIFF_MAX PTRDIFF_MAX

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_PLAT_PTR_H
