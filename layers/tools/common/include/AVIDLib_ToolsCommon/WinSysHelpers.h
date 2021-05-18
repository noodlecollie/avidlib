#ifndef AVIDLIB_TOOLS_COMMON_WINSYSHELPERS_H
#define AVIDLIB_TOOLS_COMMON_WINSYSHELPERS_H

#include "bgfx/bgfx.h"
#include "GLFW/glfw3.h"

namespace ALT_Common
{
	void GetBGFXPlatformData(GLFWwindow* window, bgfx::PlatformData& platformData);
}

#endif // AVIDLIB_TOOLS_COMMON_WINSYSHELPERS_H
