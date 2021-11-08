#include "AVIDLib_Containers/MDLv10/Submodel.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Internal_Util/Memory.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Internal_Util/ItemInitialisation.h"
#include "Internal/BoneWeightedVec3_Internal.h"

ALC_MDLv10_Submodel* ALC_MDLv10_Submodel_Init(ALC_MDLv10_Submodel* submodel)
{
	if ( ALU_SANITY_VALID(submodel) )
	{
		ALU_ZERO_STRUCT(submodel);
	}

	return submodel;
}

void ALC_MDLv10_Submodel_Deinit(ALC_MDLv10_Submodel* submodel)
{
	if ( ALU_SANITY_VALID(submodel) )
	{
		ALC_MDLv10_BodyPart_FreeVertices(submodel);
		ALC_MDLv10_BodyPart_FreeNormals(submodel);
	}
}

ALC_MDLv10_BoneWeightedVec3* ALC_MDLv10_BodyPart_AllocateVertices(ALC_MDLv10_Submodel* submodel, ALP_Size numVertices)
{
	ALC_MDLv10_BoneWeightedVec3* out = ALP_NULL;

	if ( ALU_SANITY_VALID(submodel) )
	{
		out = (ALC_MDLv10_BoneWeightedVec3*)ALU_SetArrayOfItems(
			(void**)&submodel->vertices,
			&submodel->numVertices,
			numVertices,
			sizeof(*submodel->vertices),
			&BoneWeightedVec3Internal_GenericInit,
			ALP_NULL,
			ALP_NULL,
			ALP_NULL);
	}

	return out;
}

void ALC_MDLv10_BodyPart_FreeVertices(ALC_MDLv10_Submodel* submodel)
{
	if ( ALU_SANITY_VALID(submodel) )
	{
		ALC_MDLv10_BodyPart_AllocateVertices(submodel, 0);
	}
}

ALC_MDLv10_BoneWeightedVec3* ALC_MDLv10_BodyPart_AllocateNormals(ALC_MDLv10_Submodel* submodel, ALP_Size numNormals)
{
	ALC_MDLv10_BoneWeightedVec3* out = ALP_NULL;

	if ( ALU_SANITY_VALID(submodel) )
	{
		out = (ALC_MDLv10_BoneWeightedVec3*)ALU_SetArrayOfItems(
			(void**)&submodel->normals,
			&submodel->numNormals,
			numNormals,
			sizeof(*submodel->normals),
			&BoneWeightedVec3Internal_GenericInit,
			ALP_NULL,
			ALP_NULL,
			ALP_NULL);
	}

	return out;
}

void ALC_MDLv10_BodyPart_FreeNormals(ALC_MDLv10_Submodel* submodel)
{
	if ( ALU_SANITY_VALID(submodel) )
	{
		ALC_MDLv10_BodyPart_AllocateNormals(submodel, 0);
	}
}
