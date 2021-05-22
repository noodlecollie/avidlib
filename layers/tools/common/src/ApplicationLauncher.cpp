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

	static const char* SetUpOpenGL()
	{
		// Taken from ImGui examples
#ifdef __APPLE__
		// GL 3.2 + GLSL 150
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac

		return "#version 150"
#else
		// GL 3.0 + GLSL 130
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		return "#version 130";
#endif
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
		int exit = ExitSuccess;

		do
		{
			if ( !glfwInit() )
			{
				std::cerr << "Unable to initialise GLFW!" << std::endl;
				exit = ExitUnableToInitGLFW;
				break;
			}

			const char* glslVersion = SetUpOpenGL();
			window = InitialiseApplicationWindow();

			if ( !window )
			{
				std::cerr << "Unable to create GLFW window!" << std::endl;
				exit = ExitUnableToCreateGLFWWindow;
				break;
			}

			AttachWindowCallbacks(window);

			if ( Application->OnWindowCreated(window, glslVersion) != ApplicationCallbacks::InitResult::Successful )
			{
				std::cerr << "Failed to perform custom initialisation after window creation!" << std::endl;
				exit = ExitCustomInitStateFailed;
				break;
			}

			WindowResizeTouch(window);

			while ( !glfwWindowShouldClose(window) )
			{
				glfwPollEvents();

				if ( Application->OnWindowNewFrame(window) == ApplicationCallbacks::FrameResult::CloseWindow )
				{
					break;
				}
			}
		}
		while ( false );

		if ( window )
		{
			Application->OnWindowAboutToBeDestroyed(window);
			DetachWindowCallbacks(window);
			DestroyApplicationWindow(window);
		}

		if ( exit == ExitSuccess )
		{
			// Exit code was not set by an error condition in this function.
			// Get the desired code from the application.
			exit = Application->OnGetExitCode();

			if ( exit < 0 )
			{
				// Not supposed to happen - positive error codes are supposed
				// to be used for the application. As a fallback, just use
				// a generic error code if they haven't kept to that convention.
				exit = ExitGenericError;
			}
		}

		glfwTerminate();
		glfwSetErrorCallback(nullptr);

		return exit;
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
