/**
 * About: Definitions.h
 * Defines relevant constants for the MDLv10 format.
 */

#ifndef AVIDLIB_CONTAINERS_MDLV10_DEFINITIONS_H
#define AVIDLIB_CONTAINERS_MDLV10_DEFINITIONS_H

/**
 * Constant: ALC_MDLV10_MODEL_NAME_LENGTH
 * Defines the maximum length of the internal name of the model.
 */
#define ALC_MDLV10_MODEL_NAME_LENGTH 64

/**
 * Constant: ALC_MDLV10_ELEMENT_NAME_LENGTH
 * Defines the maximum length of the internal name of any model components (eg. bones).
 */
#define ALC_MDLV10_ELEMENT_NAME_LENGTH 32

/**
 * Constant: ALC_MDLV10_NUM_MOTION_TYPES
 * Number of types of motion supported (XYZ translation and XYZ rotation).
 */
#define ALC_MDLV10_NUM_MOTION_TYPES 6

#endif // AVIDLIB_CONTAINERS_MDLV10_DEFINITIONS_H
