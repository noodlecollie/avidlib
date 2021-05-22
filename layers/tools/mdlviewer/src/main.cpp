#include "AVIDLib_ToolsCommon/ApplicationLauncher.h"
#include "AVIDLib_ToolsCommon/ApplicationCallbacks.h"

#include "GLFW/glfw3.h"
#include "bgfx/bgfx.h"
#include "bgfx_imgui/bgfx_imgui.h"

class App : public ALT_Common::ApplicationCallbacks
{
public:
	virtual ~App() = default;

	void OnGetInitialState(InitialState& initState) override
	{
		initState.windowWidth = 1280;
		initState.windowHeight = 720;
		initState.windowTitle = "GLFW + BGFX";
	}

	InitResult OnWindowCreated(GLFWwindow*, const WindowCreationState& state) override
	{
		bgfx::setDebug(BGFX_DEBUG_TEXT);
		BGFX_ImGui::imguiCreate(18.0f * state.contentScale);
		return InitResult::Successful;
	}

	void OnWindowAboutToBeDestroyed(GLFWwindow*) override
	{
		BGFX_ImGui::imguiDestroy();
	}

	void OnWindowResized(GLFWwindow*, size_t width, size_t height) override
	{
		bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(width), static_cast<uint16_t>(height));
	}

	void OnCursorMoved(GLFWwindow*, int32_t mouseX, int32_t mouseY) override
	{
		m_LastMouseX = mouseX;
		m_LastMouseY = mouseY;
	}

	void OnMouseButtons(GLFWwindow*, uint32_t buttons) override
	{
		m_LastMouseButtons = buttons;
	}

	void OnMouseScroll(GLFWwindow*, float yDelta) override
	{
		m_MouseScrollDelta += yDelta;
	}

	FrameResult OnWindowNewFrame(GLFWwindow* window) override
	{
		int fbWidth = 0;
		int fbHeight = 0;
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

		BGFX_ImGui::imguiBeginFrame(m_LastMouseX, m_LastMouseY, m_LastMouseButtons, m_MouseScrollDelta, uint16_t(fbWidth), uint16_t(fbHeight));
		m_MouseScrollDelta = 0.0;

		ImGui::ShowDemoWindow();
		BGFX_ImGui::imguiEndFrame();

		// Clear the view rect
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);

		// Set empty primitive on screen
		bgfx::touch(0);

		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x0f, "Mouse co-ords: %d, %d", m_LastMouseX, m_LastMouseY);
		bgfx::dbgTextPrintf(0, 2, 0x0f, "Mouse buttons: 0x%08x", m_LastMouseButtons);

		bgfx::frame();

		return FrameResult::NoAction;
	}

private:
	int32_t m_LastMouseX = 0.0f;
	int32_t m_LastMouseY = 0.0f;
	uint32_t m_LastMouseButtons = 0;
	float m_MouseScrollDelta = 0.0;
};

int main(int argc, char** argv)
{
	App app;
	return ALT_Common::RunApplication(argc, argv, &app);
}
