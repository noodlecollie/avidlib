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
		virtual void OnArguments(int argc, char** argv) override;
		virtual void OnGetInitialState(InitialState& state) override;
		virtual InitResult OnWindowCreated(GLFWwindow* window, const WindowCreationState& state) override;
		virtual FrameResult OnWindowNewFrame(GLFWwindow* window) override;
		virtual void OnWindowResized(GLFWwindow* window, size_t width, size_t height, size_t fbWidth, size_t fbHeight) override;
		virtual void OnCursorMoved(GLFWwindow* window, int32_t mouseX, int32_t mouseY) override;
		virtual void OnMouseButtons(GLFWwindow* window, uint32_t buttons) override;
		virtual void OnMouseScroll(GLFWwindow* window, float yDelta) override;
		virtual void OnChar(GLFWwindow* window, unsigned int key) override;
		virtual void OnWindowAboutToBeDestroyed(GLFWwindow* window) override;
		virtual int OnGetExitCode() override;

	protected:
		BGFXImGuiAdapter m_Adapter;
	};
}

#endif // AVIDLIB_TOOLS_COMMON_BASEAPPLICATION_H
