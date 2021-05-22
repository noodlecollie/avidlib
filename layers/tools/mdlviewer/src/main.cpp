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

	InitResult OnWindowCreated(GLFWwindow*, const char*) override
	{
		bgfx::setDebug(BGFX_DEBUG_TEXT);
		BGFX_ImGui::imguiCreate();
		return InitResult::Successful;
	}

	void OnWindowAboutToBeDestroyed(GLFWwindow*) override
	{
		BGFX_ImGui::imguiDestroy();
	}

	void OnWindowResized(GLFWwindow*, size_t width, size_t height)
	{
		bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(width), static_cast<uint16_t>(height));
	}

	FrameResult OnWindowNewFrame(GLFWwindow* window)
	{
		static size_t counter = 0;

		int fbWidth = 0;
		int fbHeight = 0;
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

		BGFX_ImGui::imguiBeginFrame(0, 0, 0, 0, uint16_t(fbWidth), uint16_t(fbHeight));
		ImGui::ShowDemoWindow();
		BGFX_ImGui::imguiEndFrame();

		// Clear the view rect
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);

		// Set empty primitive on screen
		bgfx::touch(0);

		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x0f, "Frame: %lu", counter++);

		bgfx::frame();

		return FrameResult::NoAction;
	}
};

int main(int argc, char** argv)
{
	App app;
	return ALT_Common::RunApplication(argc, argv, &app);
}
