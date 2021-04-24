#include "AVIDLib_Containers/MDLv10/ModelFile.h"
#include "AVIDLib_Internal_Util/Util.h"
#include "AVIDLib_Internal_Util/Check.h"

ALC_MDLv10_ModelFile* ALC_MDLv10_ModelFile_Init(ALC_MDLv10_ModelFile* modelFile)
{
	if ( ALU_SANITY_VALID(modelFile) )
	{
		ALU_MemSet(modelFile, 0, sizeof(*modelFile));
	}

	return modelFile;
}

void ALC_MDLv10_ModelFile_Deinit(ALC_MDLv10_ModelFile* modelFile)
{
	if ( ALU_SANITY_VALID(modelFile) )
	{
		// TODO: Free any allocated memory
	}
}
