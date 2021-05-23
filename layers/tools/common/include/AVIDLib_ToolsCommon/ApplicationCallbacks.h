#ifndef AVIDLIB_TOOLS_COMMON_APPLICATIONCALLBACKS_H
#define AVIDLIB_TOOLS_COMMON_APPLICATIONCALLBACKS_H

#include <cstddef>
#include <string>

typedef struct GLFWwindow GLFWwindow;

namespace ALT_Common
{
	class ApplicationCallbacks
	{
	public:
		enum class InitResult
		{
			Successful = 0,
			Error
		};

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

		struct WindowCreationState
		{
			const char* glslVersion = nullptr;
			float contentScale = 1.0f;
		};

		virtual ~ApplicationCallbacks() = default;

		// To be implemented by subclasses:
		virtual void OnArguments(int argc, char** argv);
		virtual void OnGetInitialState(InitialState& state);
		virtual InitResult OnWindowCreated(GLFWwindow* window, const WindowCreationState& state);
		virtual FrameResult OnWindowNewFrame(GLFWwindow* window);
		virtual void OnWindowResized(GLFWwindow* window, size_t width, size_t height);
		virtual void OnCursorMoved(GLFWwindow* window, int32_t mouseX, int32_t mouseY);
		virtual void OnMouseButtons(GLFWwindow* window, uint32_t buttons);
		virtual void OnMouseScroll(GLFWwindow* window, float yDelta);
		virtual void OnChar(GLFWwindow* window, unsigned int key);
		virtual void OnWindowAboutToBeDestroyed(GLFWwindow* window);
		virtual int OnGetExitCode();
	};
}

#endif // AVIDLIB_TOOLS_COMMON_APPLICATIONCALLBACKS_H
