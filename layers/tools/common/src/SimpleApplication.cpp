#include <iostream>
#include "AVIDLib_ToolsCommon/SimpleApplication.h"
#include "AVIDLib_ToolsCommon/WinSysHelpers.h"

namespace ALT_Common
{
	SimpleApplication::SimpleApplication()
	{
		glfwSetErrorCallback([](int error, const char* description)
		{
			std::cerr << "GLFW Error " << error << ": " << description << std::endl;
		});
	}

	SimpleApplication::~SimpleApplication()
	{
		Destroy();
		glfwSetErrorCallback(nullptr);
	}

	bool SimpleApplication::Create(const InitArgs& args)
	{
		if ( !glfwInit() )
		{
			std::cerr << "Unable to initialise GLFW!" << std::endl;
			return false;
		}

		m_ContentScale = ContentScaleForMonitor(GetMonitor(args.windowMonitorIndex));
		const int32_t winWidth = static_cast<int32_t>(args.windowWidth * m_ContentScale);
		const int32_t winHeight = static_cast<int32_t>(args.windowHeight * m_ContentScale);

		m_Window = glfwCreateWindow(winWidth, winHeight, args.windowTitle.c_str(), nullptr, nullptr);

		if ( !m_Window )
		{
			std::cerr << "Unable to create GLFW window!" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_Window);

		// Enable vsync
		glfwSwapInterval(1);

		bgfx::Init bgfxInit;

		// Automatically choose a renderer
		bgfxInit.type = bgfx::RendererType::Count;

		bgfxInit.resolution.width = winWidth;
		bgfxInit.resolution.height = winHeight;
		bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

		ALT_Common::GetBGFXPlatformData(m_Window, bgfxInit.platformData);

		bgfx::init(bgfxInit);
		bgfx::reset(winWidth, winHeight, BGFX_RESET_VSYNC);

		OnCreated();

		return true;
	}

	void SimpleApplication::Destroy()
	{
		if ( !IsCreated() )
		{
			return;
		}

		OnBeginDestroy();

		bgfx::shutdown();

		if ( m_Window )
		{
			glfwDestroyWindow(m_Window);
			m_Window = nullptr;
		}

		m_ContentScale = 1.0f;

		glfwTerminate();
	}

	bool SimpleApplication::IsCreated() const
	{
		return m_Window != nullptr;
	}

	bool SimpleApplication::Poll()
	{
		if ( !IsCreated() || glfwWindowShouldClose(m_Window) )
		{
			return false;
		}

		glfwPollEvents();
		return OnPoll();
	}

	void SimpleApplication::FrameBufferDimensions(size_t& width, size_t& height)
	{
		width = 0;
		height = 0;

		if ( !IsCreated() )
		{
			return;
		}

		int w = 0;
		int h = 0;

		glfwGetFramebufferSize(m_Window, &w, &h);

		width = static_cast<size_t>(std::max<int>(w, 0));
		height = static_cast<size_t>(std::max<int>(h, 0));
	}

	void SimpleApplication::OnCreated()
	{
		// Default implementation does nothing.
	}

	bool SimpleApplication::OnPoll()
	{
		// Default implementation does nothing.
		return true;
	}

	void SimpleApplication::OnBeginDestroy()
	{
		// Default implementation does nothing.
	}

	GLFWmonitor* SimpleApplication::GetMonitor(int32_t monitorIndex)
	{
		int monitorCount = 0;
		GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

		return (monitorIndex >= 0 && monitorIndex < monitorCount)
			? monitors[monitorIndex]
			: glfwGetPrimaryMonitor();
	}

	float SimpleApplication::ContentScaleForMonitor(GLFWmonitor* monitor)
	{
		float yScale = 1.0f;
		glfwGetMonitorContentScale(monitor, nullptr, &yScale);

		return yScale;
	}
}
