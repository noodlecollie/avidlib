#include "AVIDLib_ToolsCommon/BaseApplication.h"
#include "GLFW/glfw3.h"
#include "bgfx/bgfx.h"

// REMOVE ME
#include <iostream>

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

	void BaseApplication::OnChar(GLFWwindow*, unsigned int key)
	{
		m_Adapter.SetInputChar(key);
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
