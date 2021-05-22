#ifndef AVIDLIB_TOOLS_COMMON_APPLICATIONCALLBACKS_H
#define AVIDLIB_TOOLS_COMMON_APPLICATIONCALLBACKS_H

#include <cstddef>
#include <string>

#include "GLFW/glfw3.h"
#include "bgfx/bgfx.h"

namespace ALT_Common
{
	class ApplicationCallbacks
	{
	public:
		enum class FrameResult
		{
			NoAction = 0,
			CloseWindow
		};

		struct InitialState
		{
			size_t windowWidth = 640;
			size_t windowHeight = 480;
			std::string windowTitle;
		};

		virtual ~ApplicationCallbacks() = default;

		// To be implemented by subclasses:
		virtual void OnArguments(int argc, char** argv);
		virtual void OnGetInitialState(InitialState& state);
		virtual void OnWindowCreated(GLFWwindow* window);
		virtual FrameResult OnWindowNewFrame(GLFWwindow* window);
		virtual void OnWindowResized(GLFWwindow* window, size_t width, size_t height);
		virtual void OnWindowAboutToBeDestroyed(GLFWwindow* window);
	};
}

#endif // AVIDLIB_TOOLS_COMMON_APPLICATIONCALLBACKS_H
