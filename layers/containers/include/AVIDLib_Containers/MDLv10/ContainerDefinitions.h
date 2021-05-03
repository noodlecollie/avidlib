/**
 * About: ContainerDefinitions.h
 * Defines relevant constants for the MDLv10 format.
 */

#ifndef AVIDLIB_CONTAINERS_MDLV10_DEFINITIONS_H
#define AVIDLIB_CONTAINERS_MDLV10_DEFINITIONS_H

#ifdef __cplusplus
extern "C" {
#endif

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

/**
 * Constant: ALC_MDLV10_NUM_CONTROLLER_CHANNELS
 * Defines the number of controller channels that bone controllers
 * are allowed to refer to. A bone controller's channel index
 * must be less than this value.
 */
#define ALC_MDLV10_NUM_CONTROLLER_CHANNELS 5

/**
 * Constant: ALC_MDLV10_MOUTH_CONTROLLER
 * Hard-coded engine index for the controller channel
 * on an entity which corresponds to the mouth of
 * a character.
 */
#define ALC_MDLV10_MOUTH_CONTROLLER_CHANNEL 4

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_CONTAINERS_MDLV10_DEFINITIONS_H
