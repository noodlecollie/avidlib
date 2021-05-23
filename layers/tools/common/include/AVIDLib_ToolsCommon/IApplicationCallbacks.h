#ifndef AVIDLIB_TOOLS_COMMON_IAPPLICATIONCALLBACKS_H
#define AVIDLIB_TOOLS_COMMON_IAPPLICATIONCALLBACKS_H

#include <cstddef>
#include <string>

typedef struct GLFWwindow GLFWwindow;

namespace ALT_Common
{
	class IApplicationCallbacks
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

		virtual ~IApplicationCallbacks() = default;

		virtual void OnArguments(int argc, char** argv) = 0;
		virtual void OnGetInitialState(InitialState& state) = 0;
		virtual InitResult OnWindowCreated(GLFWwindow* window, const WindowCreationState& state) = 0;
		virtual FrameResult OnWindowNewFrame(GLFWwindow* window) = 0;
		virtual void OnWindowResized(GLFWwindow* window, size_t width, size_t height) = 0;
		virtual void OnCursorMoved(GLFWwindow* window, int32_t mouseX, int32_t mouseY) = 0;
		virtual void OnMouseButtons(GLFWwindow* window, uint32_t buttons) = 0;
		virtual void OnMouseScroll(GLFWwindow* window, float yDelta) = 0;
		virtual void OnChar(GLFWwindow* window, unsigned int key) = 0;
		virtual void OnWindowAboutToBeDestroyed(GLFWwindow* window) = 0;
		virtual int OnGetExitCode() = 0;
	};
}

#endif // AVIDLIB_TOOLS_COMMON_IAPPLICATIONCALLBACKS_H
