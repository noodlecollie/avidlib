#include <iostream>

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "bgfx/bgfx.h"
#include "AVIDLib_ToolsCommon/WinSysHelpers.h"

static void glfw_error_callback(int error, const char* description)
{
	std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main(int, char**)
{
	glfwSetErrorCallback(glfw_error_callback);

	if ( !glfwInit() )
	{
		std::cerr << "Unable to initialise GLFW!" << std::endl;
		return 1;
	}

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	float yScale = 1.0f;
	glfwGetMonitorContentScale(monitor, nullptr, &yScale);

	// Create window with graphics context
	const int winWidth = static_cast<int>(1280 * yScale);
	const int winHeight = static_cast<int>(720 * yScale);
	GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "GLFW Window", NULL, NULL);

	if ( !window )
	{
		std::cerr << "Unable to create GLFW window!" << std::endl;
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	bgfx::Init bgfxInit;
	bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
	bgfxInit.resolution.width = winWidth;
	bgfxInit.resolution.height = winHeight;
	bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

	ALT_Common::GetBGFXPlatformData(window, bgfxInit.platformData);

	bgfx::init(bgfxInit);
	bgfx::reset(winWidth, winHeight, BGFX_RESET_VSYNC);

	// Enable debug text.
	bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

	// Set view rectangle for 0th view
	int display_w = 0;
	int display_h = 0;
	glfwGetFramebufferSize(window, &display_w, &display_h);

	while (!glfwWindowShouldClose(window))
	{
		static size_t counter = 0;

		glfwPollEvents();

		bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(display_w), static_cast<uint16_t>(display_h));

		// Clear the view rect
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);

		// Set empty primitive on screen
		bgfx::touch(0);

		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x0f, "Frame: %lu", counter++);

		bgfx::frame();
	}

	bgfx::shutdown();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
