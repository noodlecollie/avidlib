#include "MDLLoader.h"

namespace MDLLoader
{
	static std::string Path;

	void SetMDLPath(const std::string& path)
	{
		Path = path;
	}
}
