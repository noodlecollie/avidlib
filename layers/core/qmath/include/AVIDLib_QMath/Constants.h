#ifndef AVIDLIB_QMATH_CONSTANTS_H
#define AVIDLIB_QMATH_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#define ALQM_PI 3.14159265358979323846f

#define ALQM_NAN (255 << 23)
#define	ALQM_ISNAN(x) (((*(int *)&(x)) & ALQM_NAN) == ALQM_NAN)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_CONSTANTS_H
