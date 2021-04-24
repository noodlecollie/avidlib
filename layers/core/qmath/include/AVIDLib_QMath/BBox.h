/**
 * About: BBox.h
 * This file defines a 3D axis-aligned bounding box, specified by min and max vectors.
 */

#ifndef AVIDLIB_QMATH_BBOX_H
#define AVIDLIB_QMATH_BBOX_H

#include "AVIDLib_QMath/Vec3.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Struct: ALQM_BBox
 * A 3D axis-aligned bounding box, specified by min and max vectors.
 *
 * See <BBox.h> for documentation on functions.
 */
typedef struct _ALQM_BBox
{
	/**
	 * Variable: min
	 * Minimum point of the bounding box.
	 */
	ALQM_Vec3 min;

	/**
	 * Variable: max
	 * Maximum point of the bounding box.
	 */
	ALQM_Vec3 max;
} ALQM_BBox;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_BBOX_H
