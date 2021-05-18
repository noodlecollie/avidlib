#include "AVIDLib_ToolsCommon/WinSysHelpers.h"

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

namespace ALT_Common
{
	void GetBGFXPlatformData(GLFWwindow* window, bgfx::PlatformData& platformData)
	{
		platformData.ndt = glfwGetX11Display();
		platformData.nwh = reinterpret_cast<void*>(static_cast<uintptr_t>(glfwGetX11Window(window)));
	}
}
