#include "AVIDLib_ToolsCommon/ApplicationLauncher.h"
#include "AVIDLib_ToolsCommon/BaseApplication.h"

#include "GLFW/glfw3.h"
#include "bgfx/bgfx.h"
#include "bgfx_imgui/bgfx_imgui.h"

class App : public ALT_Common::BaseApplication
{
public:
	virtual ~App() = default;

	void OnGetInitialState(InitialState& initState) override
	{
		initState.windowWidth = 1280;
		initState.windowHeight = 720;
		initState.windowTitle = "GLFW + BGFX";
	}

	InitResult OnWindowCreated(GLFWwindow* window, const WindowCreationState& state) override
	{
		const InitResult result = BaseApplication::OnWindowCreated(window, state);

		if ( result != InitResult::Successful )
		{
			return result;
		}

		BGFX_ImGui::imguiCreate(18.0f * state.contentScale);
		return InitResult::Successful;
	}

	void OnWindowAboutToBeDestroyed(GLFWwindow* window) override
	{
		BGFX_ImGui::imguiDestroy();
		BaseApplication::OnWindowAboutToBeDestroyed(window);
	}

	void OnWindowResized(GLFWwindow* window, size_t width, size_t height) override
	{
		BaseApplication::OnWindowResized(window, width, height);
		bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(width), static_cast<uint16_t>(height));
	}

	void OnCursorMoved(GLFWwindow* window, int32_t mouseX, int32_t mouseY) override
	{
		BaseApplication::OnCursorMoved(window, mouseX, mouseY);
		m_LastMouseX = mouseX;
		m_LastMouseY = mouseY;
	}

	void OnMouseButtons(GLFWwindow* window, uint32_t buttons) override
	{
		BaseApplication::OnMouseButtons(window, buttons);
		m_LastMouseButtons = buttons;
	}

	void OnMouseScroll(GLFWwindow* window, float yDelta) override
	{
		BaseApplication::OnMouseScroll(window, yDelta);
		m_MouseScrollDelta += yDelta;
	}

	void OnChar(GLFWwindow* window, unsigned int key) override
	{
		BaseApplication::OnChar(window, key);
		m_LastInputChar = static_cast<unsigned int>(key);
	}

	FrameResult OnWindowNewFrame(GLFWwindow* window) override
	{
		const FrameResult result = BaseApplication::OnWindowNewFrame(window);

		if ( result != FrameResult::NoAction )
		{
			return result;
		}

		int fbWidth = 0;
		int fbHeight = 0;
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

		// Clear the view rect
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);

		// Set empty primitive on screen
		bgfx::touch(0);

		BGFX_ImGui::imguiBeginFrame(m_LastMouseX,
									m_LastMouseY,
									m_LastMouseButtons,
									m_MouseScrollDelta,
									static_cast<uint16_t>(fbWidth),
									static_cast<uint16_t>(fbHeight),
									m_LastInputChar);
		m_LastInputChar = -1;
		m_MouseScrollDelta = 0.0;

		ImGui::ShowDemoWindow();
		BGFX_ImGui::imguiEndFrame();

		bgfx::frame();

		return FrameResult::NoAction;
	}

private:
	int32_t m_LastMouseX = 0.0f;
	int32_t m_LastMouseY = 0.0f;
	uint32_t m_LastMouseButtons = 0;
	float m_MouseScrollDelta = 0.0;
	int m_LastInputChar = -1;
};

int main(int argc, char** argv)
{
	App app;
	return ALT_Common::RunApplication(argc, argv, &app);
}
