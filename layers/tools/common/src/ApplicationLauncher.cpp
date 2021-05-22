#include <mutex>
#include <iostream>
#include "GLFW/glfw3.h"
#include "bgfx/bgfx.h"
#include "AVIDLib_ToolsCommon/ApplicationLauncher.h"
#include "AVIDLib_ToolsCommon/WinSysHelpers.h"

namespace ALT_Common
{
	static std::mutex ApplicationMutex;
	static ApplicationCallbacks* Application = nullptr;

	static inline void MakeSafeSize(int& size)
	{
		size = std::max<int>(size, 0);
	}

	static void OnWindowResized(GLFWwindow* window, int width, int height)
	{
		int bufferWidth = 0;
		int bufferHeight = 0;
		glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

		MakeSafeSize(bufferWidth);
		MakeSafeSize(bufferHeight);
		bgfx::reset(static_cast<uint32_t>(bufferWidth), static_cast<uint32_t>(bufferHeight), BGFX_RESET_VSYNC);

		MakeSafeSize(width);
		MakeSafeSize(height);
		Application->OnWindowResized(window, static_cast<size_t>(width), static_cast<size_t>(height));
	}

	static void WindowResizeTouch(GLFWwindow* window)
	{
		int width = 0;
		int height = 0;
		glfwGetWindowSize(window, &width, &height);

		OnWindowResized(window, width, height);
	}

	static float ContentScaleForMonitor(GLFWmonitor* monitor)
	{
		float yScale = 1.0f;
		glfwGetMonitorContentScale(monitor, nullptr, &yScale);

		return yScale;
	}

	static GLFWwindow* InitialiseApplicationWindow()
	{
		ApplicationCallbacks::InitialState initState;
		Application->OnGetInitialState(initState);

		const float contentScale = ContentScaleForMonitor(glfwGetPrimaryMonitor());

		const int32_t winWidth = static_cast<int32_t>(initState.windowWidth * contentScale);
		const int32_t winHeight = static_cast<int32_t>(initState.windowHeight * contentScale);

		GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, initState.windowTitle.c_str(), nullptr, nullptr);

		if ( !window )
		{
			return nullptr;
		}

		glfwMakeContextCurrent(window);

		// Enable vsync
		glfwSwapInterval(1);

		bgfx::Init bgfxInit;

		// Automatically choose a renderer
		bgfxInit.type = bgfx::RendererType::Count;

		bgfxInit.resolution.width = winWidth;
		bgfxInit.resolution.height = winHeight;
		bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

		ALT_Common::GetBGFXPlatformData(window, bgfxInit.platformData);

		bgfx::init(bgfxInit);
		bgfx::reset(winWidth, winHeight, BGFX_RESET_VSYNC);

		return window;
	}

	static void DestroyApplicationWindow(GLFWwindow* window)
	{
		bgfx::shutdown();
		glfwDestroyWindow(window);
	}

	static void AttachWindowCallbacks(GLFWwindow* window)
	{
		glfwSetWindowSizeCallback(window, &OnWindowResized);
	}

	static void DetachWindowCallbacks(GLFWwindow* window)
	{
		glfwSetWindowSizeCallback(window, nullptr);
	}

	static int RunApplicationInternal(int argc, char** argv)
	{
		Application->OnArguments(argc, argv);

		glfwSetErrorCallback([](int error, const char* description)
		{
			std::cerr << "GLFW Error " << error << ": " << description << std::endl;
		});

		GLFWwindow* window = nullptr;
		int returnVal = -1;

		do
		{
			if ( !glfwInit() )
			{
				std::cerr << "Unable to initialise GLFW!" << std::endl;
				break;
			}

			window = InitialiseApplicationWindow();

			if ( !window )
			{
				std::cerr << "Unable to create GLFW window!" << std::endl;
				break;
			}

			AttachWindowCallbacks(window);
			Application->OnWindowCreated(window);
			WindowResizeTouch(window);

			while ( !glfwWindowShouldClose(window) )
			{
				glfwPollEvents();

				if ( Application->OnWindowNewFrame(window) == ApplicationCallbacks::FrameResult::CloseWindow )
				{
					break;
				}
			}

			Application->OnWindowAboutToBeDestroyed(window);
			DetachWindowCallbacks(window);
			DestroyApplicationWindow(window);

			returnVal = 0;
		}
		while ( false );

		glfwTerminate();
		glfwSetErrorCallback(nullptr);

		return returnVal;
	}

	int RunApplication(int argc, char** argv, ApplicationCallbacks* application)
	{
		if ( argc < 1 || !argv )
		{
			return -1;
		}

		std::lock_guard<std::mutex> mutexLock(ApplicationMutex);

		Application = application;
		const int returnValue = RunApplicationInternal(argc, argv);
		Application = nullptr;

		return returnValue;
	}
}
