#ifndef AVIDLIB_CLIB_BOOL_H
#define AVIDLIB_CLIB_BOOL_H

// Bool comes as part of C++, so don't mess with anything if this header
// has been imported into a C++ application.
#ifndef __cplusplus

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <stdbool.h>

#endif // __cplusplus

typedef bool ALC_Bool;

#define ALC_TRUE true
#define ALC_FALSE false

#endif // AVIDLIB_CLIB_BOOL_H
