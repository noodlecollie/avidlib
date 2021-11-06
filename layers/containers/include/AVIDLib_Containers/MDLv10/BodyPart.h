/**
 * About: BosyPart.h
 * Defines an MDLv10 body part.
 */

#ifndef AVIDLIB_CONTAINERS_MDLV10_BODYPART_H
#define AVIDLIB_CONTAINERS_MDLV10_BODYPART_H

#include "AVIDLib_Containers/LibExport.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Struct: ALC_MDLv10_BodyPart
 * Defines an MDLv10 body part.
 *
 * Body parts are used to allow different groupings of geometry
 * in a model. The way this works can seem a little convoluted
 * if you don't know how it works, so let's go through a small
 * example in detail.
 *
 * Let's say a gun model has three different sections of geometry
 * that may be varied by game code: the gun itself, the sight on
 * top, and the silencer. Each of the gun, sight and silencer
 * would comprise a "body part".
 *
 * Additionally, the gun has four different "body groups": the
 * gun with no accessories, the gun with a silencer but no sight,
 * the gun with a large silencer and large sight, and the gun with
 * a small silencer and small sight. For each of the individual
 * body parts, there are four different meshes that could be
 * rendered depending on the body group that the game wants to show.
 * In the case where the gun has a silencer but no sight, the
 * permutation for the sight has no geometry at all.
 *
 * The <ALC_MDLv10_BodyPart> struct defines a body part in the
 * above scenario. The body part may make reference to multiple
 * different meshes, depending on how many body groups have been
 * defined on the model.
 */
typedef struct _ALC_MDLv10_BodyPart
{
	// TODO: contents
	int dummy;
} ALC_MDLv10_BodyPart;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CONTAINERS_MDLV10_BODYPART_H
