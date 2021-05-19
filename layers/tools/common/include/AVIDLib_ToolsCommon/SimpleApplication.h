#ifndef AVIDLIB_TOOLS_COMMON_SIMPLEAPPLICATION_H
#define AVIDLIB_TOOLS_COMMON_SIMPLEAPPLICATION_H

#include <memory>
#include <string>
#include <cstdint>

#include "GLFW/glfw3.h"
#include "bgfx/bgfx.h"

namespace ALT_Common
{
	class SimpleApplication
	{
	public:
		struct InitArgs
		{
			int argc = 0;
			char** argv = nullptr;
			size_t windowWidth = 0;
			size_t windowHeight = 0;
			std::string windowTitle;
			int32_t windowMonitorIndex = -1;
		};

		virtual ~SimpleApplication();

		bool Create(const InitArgs& args);
		void Destroy();
		bool IsCreated() const;
		bool Poll();

		void FrameBufferDimensions(size_t& width, size_t& height);

	protected:
		SimpleApplication();

		virtual void OnCreated();
		virtual void OnBeginDestroy();
		virtual bool OnPoll();

	private:
		GLFWmonitor* GetMonitor(int32_t monitorIndex);
		float ContentScaleForMonitor(GLFWmonitor* monitor);

		GLFWwindow* m_Window = nullptr;
		float m_ContentScale = 1.0f;
	};
}

#endif // AVIDLIB_TOOLS_COMMON_SIMPLEAPPLICATION_H
