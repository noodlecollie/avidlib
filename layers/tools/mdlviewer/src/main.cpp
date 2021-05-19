#include "AVIDLib_ToolsCommon/SimpleApplication.h"

class App : public ALT_Common::SimpleApplication
{
public:
	virtual ~App() = default;

protected:
	void OnCreated() override
	{
		bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);
	}

	bool OnPoll() override
	{
		static size_t counter = 0;

		glfwPollEvents();

		size_t width = 0;
		size_t height = 0;
		FrameBufferDimensions(width, height);

		bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(width), static_cast<uint16_t>(height));

		// Clear the view rect
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);

		// Set empty primitive on screen
		bgfx::touch(0);

		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x0f, "Frame: %lu", counter++);

		bgfx::frame();

		return true;
	}
};

int main(int argc, char** argv)
{
	using namespace ALT_Common;

	SimpleApplication::InitArgs args;

	args.argc = argc;
	args.argv = argv;
	args.windowWidth = 1280;
	args.windowHeight = 720;
	args.windowTitle = "GLFW + BGFX";

	App app;

	if ( !app.Create(args) )
	{
		return 1;
	}

	while ( app.Poll() )
	{
		// Don't quit yet.
	}

	app.Destroy();
	return 0;
}
