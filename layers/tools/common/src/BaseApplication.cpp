#include "AVIDLib_ToolsCommon/BaseApplication.h"
#include "GLFW/glfw3.h"
#include "bgfx/bgfx.h"

namespace ALT_Common
{
	void BaseApplication::OnArguments(int, char**)
	{
	}

	void BaseApplication::OnGetInitialState(InitialState&)
	{
	}

	IApplicationCallbacks::InitResult BaseApplication::OnWindowCreated(GLFWwindow* window, const WindowCreationState& state)
	{
		int fbWidth = 0;
		int fbHeight = 0;
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

		const ImVec2 fbSize{static_cast<float>(fbWidth), static_cast<float>(fbHeight)};
		m_Adapter.Create(18.0f * state.contentScale);

		m_Adapter.SetKeyMapping(ImGuiKey_Tab, GLFW_KEY_TAB);
		m_Adapter.SetKeyMapping(ImGuiKey_LeftArrow, GLFW_KEY_LEFT);
		m_Adapter.SetKeyMapping(ImGuiKey_RightArrow, GLFW_KEY_RIGHT);
		m_Adapter.SetKeyMapping(ImGuiKey_UpArrow, GLFW_KEY_UP);
		m_Adapter.SetKeyMapping(ImGuiKey_DownArrow, GLFW_KEY_DOWN);
		m_Adapter.SetKeyMapping(ImGuiKey_PageUp, GLFW_KEY_PAGE_UP);
		m_Adapter.SetKeyMapping(ImGuiKey_PageDown, GLFW_KEY_PAGE_DOWN);
		m_Adapter.SetKeyMapping(ImGuiKey_Home, GLFW_KEY_HOME);
		m_Adapter.SetKeyMapping(ImGuiKey_End, GLFW_KEY_END);
		m_Adapter.SetKeyMapping(ImGuiKey_Insert, GLFW_KEY_INSERT);
		m_Adapter.SetKeyMapping(ImGuiKey_Delete, GLFW_KEY_DELETE);
		m_Adapter.SetKeyMapping(ImGuiKey_Backspace, GLFW_KEY_BACKSPACE);
		m_Adapter.SetKeyMapping(ImGuiKey_Space, GLFW_KEY_SPACE);
		m_Adapter.SetKeyMapping(ImGuiKey_Enter, GLFW_KEY_ENTER);
		m_Adapter.SetKeyMapping(ImGuiKey_Escape, GLFW_KEY_ESCAPE);
		m_Adapter.SetKeyMapping(ImGuiKey_KeyPadEnter, GLFW_KEY_KP_ENTER);
		m_Adapter.SetKeyMapping(ImGuiKey_A, GLFW_KEY_A);
		m_Adapter.SetKeyMapping(ImGuiKey_C, GLFW_KEY_C);
		m_Adapter.SetKeyMapping(ImGuiKey_V, GLFW_KEY_V);
		m_Adapter.SetKeyMapping(ImGuiKey_X, GLFW_KEY_X);
		m_Adapter.SetKeyMapping(ImGuiKey_Y, GLFW_KEY_Y);
		m_Adapter.SetKeyMapping(ImGuiKey_Z, GLFW_KEY_Z);

		return IApplicationCallbacks::InitResult::Successful;
	}

	IApplicationCallbacks::FrameResult BaseApplication::OnWindowNewFrame(GLFWwindow*)
	{
		return IApplicationCallbacks::FrameResult::NoAction;
	}

	void BaseApplication::OnWindowResized(GLFWwindow*, size_t width, size_t height, size_t, size_t fbHeight)
	{
		bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(width), static_cast<uint16_t>(height));

		m_Adapter.SetDisplaySize(ImVec2{static_cast<float>(width), static_cast<float>(height)});
		m_Adapter.SetDisplayScale(static_cast<float>(fbHeight) / static_cast<float>(height));
	}

	void BaseApplication::OnCursorMoved(GLFWwindow*, int32_t mouseX, int32_t mouseY)
	{
		const ImVec2 pos{static_cast<float>(mouseX), static_cast<float>(mouseY)};
		m_Adapter.SetMousePosition(pos);
	}

	void BaseApplication::OnMouseButtons(GLFWwindow*, uint32_t buttons)
	{
		m_Adapter.OverwriteMouseButtonsPressed(buttons);
	}

	void BaseApplication::OnMouseScroll(GLFWwindow*, float yDelta)
	{
		ImVec2 scrollDelta{0.0f, yDelta};
		m_Adapter.SetScrollDelta(scrollDelta);
	}

	void BaseApplication::OnChar(GLFWwindow*, unsigned int character)
	{
		m_Adapter.SetInputChar(character);
	}

	void BaseApplication::OnKey(GLFWwindow*, unsigned int key, bool pressed)
	{
		m_Adapter.SetKeyState(key, pressed);
	}

	void BaseApplication::OnWindowAboutToBeDestroyed(GLFWwindow*)
	{
		m_Adapter.Destroy();
	}

	int BaseApplication::OnGetExitCode()
	{
		return 0;
	}
}
