#ifndef AVIDLIB_CLIB_DEBUG_H
#define AVIDLIB_CLIB_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

// CMake configurations seem to make adding definitions in debug annoying,
// so we just do it here.

#ifndef NDEBUG
#define AVIDLIB_DEBUG
#endif // NDEBUG

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CLIB_DEBUG_H
