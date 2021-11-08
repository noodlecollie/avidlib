#ifndef AVIDLIB_TOOLS_MDLVIEWER_MDLLOADER_H
#define AVIDLIB_TOOLS_MDLVIEWER_MDLLOADER_H

#include <string>
#include "AVIDLib_IO/UnitSupport.h"
#include "AVIDLib_IO/GenericOperations.h"

namespace MDLLoader
{
	std::string GetMDLPath();
	void SetMDLPath(const std::string& path);
	void Poll();
	void Cleanup();

	ALIO_GenericContainer* GetGenericIOContainer();
	ALP_Opaque* GetUnderlyingContainer(ALIO_UnitID id);
}

#endif // AVIDLIB_TOOLS_MDLVIEWER_MDLLOADER_H
