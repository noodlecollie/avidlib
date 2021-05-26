#ifndef AVIDLIB_TOOLS_COMMON_BASEAPPLICATION_H
#define AVIDLIB_TOOLS_COMMON_BASEAPPLICATION_H

#include "AVIDLib_ToolsCommon/IApplicationCallbacks.h"
#include "bgfx_imgui/BGFXImGuiAdapter.h"

namespace ALT_Common
{
	class BaseApplication : public IApplicationCallbacks
	{
	public:
		virtual ~BaseApplication() = default;

		// If subclasses override these functions, they should always call through to the
		// base implementation as well!
		void OnArguments(int argc, char** argv) override;
		void OnGetInitialState(InitialState& state) override;
		InitResult OnWindowCreated(GLFWwindow* window, const WindowCreationState& state) override;
		FrameResult OnWindowNewFrame(GLFWwindow* window) override;
		void OnWindowResized(GLFWwindow* window, size_t width, size_t height, size_t fbWidth, size_t fbHeight) override;
		void OnCursorMoved(GLFWwindow* window, int32_t mouseX, int32_t mouseY) override;
		void OnMouseButtons(GLFWwindow* window, uint32_t buttons) override;
		void OnMouseScroll(GLFWwindow* window, float yDelta) override;
		void OnChar(GLFWwindow* window, unsigned int character) override;
		void OnKey(GLFWwindow* window, unsigned int key, bool pressed) override;
		void OnWindowAboutToBeDestroyed(GLFWwindow* window) override;
		int OnGetExitCode() override;

	protected:
		BGFXImGuiAdapter m_Adapter;
	};
}

#endif // AVIDLIB_TOOLS_COMMON_BASEAPPLICATION_H
