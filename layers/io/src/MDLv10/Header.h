/**
 * About: Header.h
 * Defines an MDLv10 file header.
 */

#ifndef AVIDLIB_IO_MDLV10_FILEELEMENTS_H
#define AVIDLIB_IO_MDLV10_FILEELEMENTS_H

#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_QMath/Types.h"
#include "FormatCommon/FileElementHelpers.h"
#include "MDLv10/IODefinitions.h"

#pragma pack(push, 1)

/**
 * Struct: ALIO_MDLv10_Header
 * Defines the structure of the beginning of a MDLv10 model file.
 *
 * Any <ALIO_CountOffsetPair> variable defines how many of each of
 * its elements there are in the file, and the offset from the
 * beginning of the file at which the data can be found. The data
 * is contiguous for the entire block of elements.
 *
 * If the count is 0, the offset should be considered undefined
 * (as StudioMDL doesn't guarantee what value the offset will be
 * in this case).
 */
typedef struct _ALIO_MDLv10_Header
{
	/**
	 * Variable: identifier
	 * "Magic number" for identifying the file.
	 * This should be a little-endian combination of
	 * the characters "IDST" for a general-purpose
	 * model file, or "IDSQ" for a model file which
	 * holds sequences only.
	 */
	ALP_UInt32 identifier;

	/**
	 * Variable: version
	 * StudioMDL format version (should be 10).
	 */
	ALP_UInt32 version;

	/**
	 * Variable: name
	 * Internal model name. This may be different from the model's file name.
	 */
	ALP_Char name[ALIO_MDLV10_MODEL_NAME_LENGTH];

	/**
	 * Variable: length
	 * Total file size in bytes.
	 * *Should* match the actual file size, if the compiler
	 * that generated the model is well-behaved.
	 */
	ALP_UInt32 length;

	/**
	 * Variable: eyePosition
	 * Position of the character's eyes within this model.
	 */
	ALIO_RawVec3 eyePosition;

	/**
	 * Variable: movementHull
	 * Movement hull, for collision calculations.
	 */
	ALIO_BBox movementHull;

	/**
	 * Variable: clippingHull
	 * Clipping hull, for visibility calculations?
	 */
	ALIO_BBox clippingHull;

	/**
	 * Variable: flags
	 * Engine-specific feature flags. See <Supported Model Flags>.
	 */
	ALP_UInt32 flags;

	/**
	 * Variable: bones
	 * Specifies how many bones are present in the model, and
	 * the location of the bone data.
	 */
	ALIO_CountOffsetPair bones;

	/**
	 * Variable: boneControllers
	 * Specifies how many bone controllers are present in the model,
	 * and the location of the bone controller data.
	 */
	ALIO_CountOffsetPair boneControllers;

	/**
	 * Variable: hitboxes
	 * Specifies how many hitboxes are present in the model, and
	 * the location of the hitbox data.
	 */
	ALIO_CountOffsetPair hitboxes;

	/**
	 * Variable: sequences
	 * Specifies how many sequences are present in the model, and
	 * the location of the sequence data.
	 */
	ALIO_CountOffsetPair sequences;

	/**
	 * Variable: sequenceGroups
	 * Specifies how many sequence groups are present in the model,
	 * and the location of the sequence group data.
	 */
	ALIO_CountOffsetPair sequenceGroups;

	/**
	 * Variable: textureInfos
	 * Specifies how many texture infos are present in the model,
	 * and the location of the texture info data.
	 */
	ALIO_CountOffsetPair textureInfos;

	/**
	 * Variable: textureDataOffset
	 * Offset to the first texture's image data.
	 *
	 * Texture images *should* always be in the final chunk of the file.
	 * This offset doesn't appear to be used for anything
	 * significant according to the Xash3D engine, but it is
	 * used to determine the length of the model file
	 * excluding any texture data, since the texture data should
	 * be the last chunk in the file.
	 */
	ALP_UInt32 textureDataOffset;

	/**
	 * Variable: numSkinRefs
	 * How many texture references one skin family contains.
	 * This corresponds to how many independent textures are
	 * referenced by meshes within this model at one time.
	 */
	ALP_UInt32 numSkinRefs;

	/**
	 * Variable: numSkinFamilies
	 * An entity's "skin" property in Half Life refers to a skin family,
	 * and is allowed to be within the range [0 numSkinFamilies). This
	 * variable essentially describes how many different skins are
	 * selectable from within the game.
	 */
	ALP_UInt32 numSkinFamilies;

	/**
	 * Variable: skinDataOffset
	 * Offset to the model's skin data. This is an array of 16-bit
	 * unsigned integers which refer to textures by index.
	 * There are <ALIO_MDLv10_Header.numSkinRefs> *
	 * <ALIO_MDLv10_Header.numSkinFamilies> different skin
	 * data entries.
	 */
	ALP_UInt32		skinDataOffset;

	/**
	 * Variable: bodyParts
	 * Specifies how many body parts are present in the model,
	 * and the location of the body part data.
	 */
	ALIO_CountOffsetPair bodyParts;

	/**
	 * Variable: attachments
	 * Specifies how many attachments are present in the model,
	 * and the location of the attachment data.
	 */
	ALIO_CountOffsetPair attachments;

	/**
	 * Variable: studioHdr2Offset
	 * In Xash3D, this is used to point to an extended second
	 * header, which contains additional model information for
	 * content supported by the Xash3D engine. In the Half Life
	 * engine, this variable appears to be unused.
	 */
	ALP_UInt32 studioHdr2Offset;

	/**
	 * Variable: unused
	 * This was "soundIndex" in the original MDL header,
	 * but appears to be unused.
	 */
	ALP_UInt32 unused;

	/**
	 * Variable: unused2
	 * This was "soundGroups" in the original MDL header,
	 * but appears to be unused.
	 */
	ALP_UInt32 unused2;

	/**
	 * Variable: unused3
	 * This was "soundGroupIndex" in the original MDL header,
	 * but appears to be unused.
	 */
	ALP_UInt32 unused3;

	/**
	 * Variable: transitions
	 * Specifies how many transitions are present in the model,
	 * and the location of the transition data.
	 */
	ALIO_CountOffsetPair transitions;
} ALIO_MDLv10_Header;

#pragma pack(pop)

#endif // AVIDLIB_IO_MDLV10_FILEELEMENTS_H
