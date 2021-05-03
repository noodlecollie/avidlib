/**
 * About: MDLv10Definitions.h
 * Provides definitions relating to the MDLv10 model file format.
 */

#ifndef AVIDLIB_IO_MDLV10_DEFINITIONS_H
#define AVIDLIB_IO_MDLV10_DEFINITIONS_H

#include "AVIDLib_Plat/Int.h"

/**
 * Constant: ALIO_MDLV10_FILE_VERSION
 * Expected version (10) for an MDLv10 model file.
 */
#define ALIO_MDLV10_FILE_VERSION 10

/**
 * Constant: ALIO_MDLV10_GENFILE_IDENT
 * "Magic number" for an MDLv10 general-purpose model file, which holds
 * model data such as meshes, animations and textures.
 *
 * This is a little-endian concatenation of the characters "IDST".
 */
#define ALIO_MDLV10_GENFILE_IDENT ((ALP_UInt32)('I' | ('D' << 8) | ('S' << 16) | ('T' << 24)))

/**
 * Constant: ALIO_MDLV10_SEQFILE_IDENT
 * "Magic number" for an MDLv10 sequence container model file, which holds
 * animation sequence data only.
 *
 * This is a little-endian concatenation of the characters "IDSQ".
 */
#define ALIO_MDLV10_SEQFILE_IDENT ((ALP_UInt32)('I' | ('D' << 8) | ('S' << 16) | ('Q' << 24)))

/**
 * Constant: ALIO_MDLV10_MODEL_NAME_LENGTH
 * Defines the maximum length of the internal name of the model.
 */
#define ALIO_MDLV10_MODEL_NAME_LENGTH 64

/**
 * Constant: ALIO_MDLV10_ELEMENT_NAME_LENGTH
 * Defines the maximum length of the internal name of any model components (eg. bones).
 */
#define ALIO_MDLV10_ELEMENT_NAME_LENGTH 32

/**
 * Constant: ALIO_MDLV10_NUM_MOTION_TYPES
 * Number of types of motion supported (XYZ translation and XYZ rotation).
 */
#define ALIO_MDLV10_NUM_MOTION_TYPES 6

/**
 * Constants: Supported Model Flags
 * These constants are taken from the Xash3D engine.
 *
 * ALIO_MDLV10_FLAG_ROCKET          - This model is a rocket, and leaves an appropriate movement trail.
 * ALIO_MDLV10_FLAG_GRENADE         - This model is a grenade, and leaves an appropriate movement trail.
 * ALIO_MDLV10_FLAG_GIB             - This model is a gib, and leaves an appropriate movement trail.
 * ALIO_MDLV10_FLAG_ROTATE          - This model rotates continuously on yaw. Useful for powerups.
 * ALIO_MDLV10_FLAG_TRACER          - This model leaves a green spit movement trail.
 * ALIO_MDLV10_FLAG_ZOMGIB          - This model is a zombie gib, and leaves an appropriate movement trail.
 * ALIO_MDLV10_FLAG_TRACER2         - This model leaves an orange spit movement trail.
 * ALIO_MDLV10_FLAG_TRACER3         - This model leaves a purple spit movement trail.
 * ALIO_MDLV10_FLAG_AMBIENT_LIGHT   - This model only receives ambient light, and never produces a shadow.
 * ALIO_MDLV10_FLAG_TRACE_HITBOX    - This model should always use hitboxes for interacting with traces, and never bounding boxes.
 * ALIO_MDLV10_FLAG_FORCE_SKYLIGHT  - Lighting values for this model are always taken from sky settings, even if the sky is invisible.
 * ALIO_MDLV10_FLAG_HAS_BUMP        - Appears to be unused.
 * ALIO_MDLV10_FLAG_STATIC_PROP     - Appears to be unused.
 * ALIO_MDLV10_FLAG_HAS_BONEINFO    - (Xash3D-specific) Model contains extra bone information for calculating bone weights.
 * ALIO_MDLV10_FLAG_HAS_BONEWEIGHTS - (Xash3D-specific) Model contains bone weights for complex vertex skinning.
 */
#define ALIO_MDLV10_FLAG_ROCKET (1U<<0)
#define ALIO_MDLV10_FLAG_GRENADE (1U<<1)
#define ALIO_MDLV10_FLAG_GIB (1U<<2)
#define ALIO_MDLV10_FLAG_ROTATE (1U<<3)
#define ALIO_MDLV10_FLAG_TRACER (1U<<4)
#define ALIO_MDLV10_FLAG_ZOMGIB (1U<<5)
#define ALIO_MDLV10_FLAG_TRACER2 (1U<<6)
#define ALIO_MDLV10_FLAG_TRACER3 (1U<<7)
#define ALIO_MDLV10_FLAG_AMBIENT_LIGHT (1U<<8)
#define ALIO_MDLV10_FLAG_TRACE_HITBOX (1U<<9)
#define ALIO_MDLV10_FLAG_FORCE_SKYLIGHT (1U<<10)
#define ALIO_MDLV10_FLAG_HAS_BUMP (1U<<16)
#define ALIO_MDLV10_FLAG_STATIC_PROP (1U<<29)
#define ALIO_MDLV10_FLAG_HAS_BONEINFO (1U<<30)
#define ALIO_MDLV10_FLAG_HAS_BONEWEIGHTS (1U<<31)

/**
 * Constants: Motion Flags
 * These constants are taken from the Xash3D Engine.
 *
 * ALIO_MDLV10_MVFLAG_X         - Bone controller motion on the X axis.
 * ALIO_MDLV10_MVFLAG_Y         - Bone controller motion on the Y axis.
 * ALIO_MDLV10_MVFLAG_Z         - Bone controller motion on the Z axis.
 * ALIO_MDLV10_MVFLAG_XR        - Bone controller rotation on the X axis.
 * ALIO_MDLV10_MVFLAG_YR        - Bone controller rotation on the Y axis.
 * ALIO_MDLV10_MVFLAG_ZR        - Bone controller rotation on the Z axis.
 * ALIO_MDLV10_MVFLAG_LX        - Linear animation sequence motion on the X axis.
 * ALIO_MDLV10_MVFLAG_LY        - Linear animation sequence motion on the Y axis.
 * ALIO_MDLV10_MVFLAG_LZ        - Linear animation sequence motion on the Z axis.
 * ALIO_MDLV10_MVFLAG_LXR       - Appears to be unused in engine.
 * ALIO_MDLV10_MVFLAG_LYR       - Appears to be unused in engine.
 * ALIO_MDLV10_MVFLAG_LZR       - Appears to be unused in engine.
 * ALIO_MDLV10_MVFLAG_LINEAR    - Appears to be unused in engine.
 * ALIO_MDLV10_MVFLAG_QUADRATIC - Appears to be unused in engine.
 * ALIO_MDLV10_MVFLAGO_RESERVED - Appears to be unused in engine.
 * ALIO_MDLV10_MVFLAG_TYPES     - Mask value for all allowed motion flags.
 * ALIO_MDLV10_MVFLAG_RLOOP     - Specifies that controller motion wraps around to beginning.
 */
#define ALIO_MDLV10_MVFLAG_X (1U << 0)
#define ALIO_MDLV10_MVFLAG_Y (1U << 1)
#define ALIO_MDLV10_MVFLAG_Z (1U << 2)
#define ALIO_MDLV10_MVFLAG_XR (1U << 3)
#define ALIO_MDLV10_MVFLAG_YR (1U << 4)
#define ALIO_MDLV10_MVFLAG_ZR (1U << 5)
#define ALIO_MDLV10_MVFLAG_LX (1U << 6)
#define ALIO_MDLV10_MVFLAG_LY (1U << 7)
#define ALIO_MDLV10_MVFLAG_LZ (1U << 8)
#define ALIO_MDLV10_MVFLAG_LXR (1U << 9)
#define ALIO_MDLV10_MVFLAG_LYR (1U << 10)
#define ALIO_MDLV10_MVFLAG_LZR (1U << 11)
#define ALIO_MDLV10_MVFLAG_LINEAR (1U << 12)
#define ALIO_MDLV10_MVFLAG_QUADRATIC (1U << 13)
#define ALIO_MDLV10_MVFLAGO_RESERVED (1U << 14)
#define ALIO_MDLV10_MVFLAG_TYPES 0x7FFF
#define ALIO_MDLV10_MVFLAG_RLOOP (1U << 15)

/**
 * Constant: ALIO_MDLV10_NUM_CONTROLLER_CHANNELS
 * Defines the number of controller channels that bone controllers
 * are allowed to refer to. A bone controller's channel index
 * must be less than this value.
 */
#define ALIO_MDLV10_NUM_CONTROLLER_CHANNELS 5

/**
 * Constant: ALIO_MDLV10_MOUTH_CONTROLLER
 * Hard-coded engine index for the controller channel
 * on an entity which corresponds to the mouth of
 * a character.
 */
#define ALIO_MDLV10_MOUTH_CONTROLLER_CHANNEL 4

typedef enum _ALIO_MDLv10_FileType
{
	ALIO_MDLV10_FILE_INVALID = 0,
	ALIO_MDLV10_FILE_GENERAL,
	ALIO_MDLV10_FILE_SEQUENCE_CONTAINER
} ALIO_MDLv10_FileType;

#endif // AVIDLIB_IO_MDLV10_DEFINITIONS_H
