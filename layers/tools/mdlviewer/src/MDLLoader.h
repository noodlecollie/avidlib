#ifndef AVIDLIB_TOOLS_MDLVIEWER_MDLLOADER_H
#define AVIDLIB_TOOLS_MDLVIEWER_MDLLOADER_H

#include <string>

namespace MDLLoader
{
	void SetMDLPath(const std::string& path);
	void Poll();
	void Cleanup();
}

#endif // AVIDLIB_TOOLS_MDLVIEWER_MDLLOADER_H
