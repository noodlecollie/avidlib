#include "AVIDLib_ToolsCommon/ApplicationLauncher.h"
#include "AVIDLib_ToolsCommon/BaseApplication.h"

#include "bgfx/bgfx.h"

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

	FrameResult OnWindowNewFrame(GLFWwindow* window) override
	{
		const FrameResult result = BaseApplication::OnWindowNewFrame(window);

		if ( result != FrameResult::NoAction )
		{
			return result;
		}

		// Clear the view rect
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);

		// Set empty primitive on screen
		bgfx::touch(0);

		m_Adapter.BeginFrame();
		ImGui::ShowDemoWindow();
		m_Adapter.EndFrame();

		bgfx::frame();

		return FrameResult::NoAction;
	}
};

int main(int argc, char** argv)
{
	App app;
	return ALT_Common::RunApplication(argc, argv, &app);
}
