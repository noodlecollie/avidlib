#ifndef AVIDLIB_CLIB_UTIL_H
#define AVIDLIB_CLIB_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

// #define min and #define max are evil. We define macros that aren't as likely
// to collide catastrophically with other names in the global namespace.
#define ALC_MIN(a, b) ((a) < (b) ? (a) : (b))
#define ALC_MAX(a, b) ((a) > (b) ? (a) : (b))

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CLIB_BOOL_H
