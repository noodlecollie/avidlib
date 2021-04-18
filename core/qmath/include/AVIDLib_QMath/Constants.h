#ifndef AVIDLIB_QMATH_CONSTANTS_H
#define AVIDLIB_QMATH_CONSTANTS_H

// For now, we just use platform headers.
// If we get to a point in future where we need to swap this out
// depending on our target platform, we can add ifdefs.
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ALQM_PI M_PI

#define ALQM_NAN (255 << 23)
#define	ALQM_ISNAN(x) (((*(int *)&(x)) & ALQM_NAN) == ALQM_NAN)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_CONSTANTS_H
