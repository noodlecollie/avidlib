#ifndef AVIDLIB_CONTAINERS_MDLV10_BONE_INTERNAL_H
#define AVIDLIB_CONTAINERS_MDLV10_BONE_INTERNAL_H

#include "AVIDLib_Containers/MDLv10/Bone.h"
#include "AVIDLib_Internal_Util/Util.h"

static void BoneInternal_GenericInit(void* bone, void* data) { ALU_UNUSED(data); ALC_MDLv10_Bone_Init((ALC_MDLv10_Bone*)bone); }
static void BoneInternal_GenericDeinit(void* bone, void* data ) { ALU_UNUSED(data); ALC_MDLv10_Bone_Deinit((ALC_MDLv10_Bone*)bone); }

#endif // AVIDLIB_CONTAINERS_MDLV10_BONE_INTERNAL_H
