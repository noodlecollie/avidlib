#include "AVIDLib_ToolsCommon/BaseApplication.h"

namespace ALT_Common
{
	void BaseApplication::OnArguments(int, char**)
	{
	}

	void BaseApplication::OnGetInitialState(InitialState&)
	{
	}

	IApplicationCallbacks::InitResult BaseApplication::OnWindowCreated(GLFWwindow*, const WindowCreationState&)
	{
		return IApplicationCallbacks::InitResult::Successful;
	}

	IApplicationCallbacks::FrameResult BaseApplication::OnWindowNewFrame(GLFWwindow*)
	{
		return IApplicationCallbacks::FrameResult::NoAction;
	}

	void BaseApplication::OnWindowResized(GLFWwindow*, size_t, size_t)
	{
	}

	void BaseApplication::OnCursorMoved(GLFWwindow*, int32_t, int32_t)
	{
	}

	void BaseApplication::OnMouseButtons(GLFWwindow*, uint32_t)
	{
	}

	void BaseApplication::OnMouseScroll(GLFWwindow*, float)
	{
	}

	void BaseApplication::OnChar(GLFWwindow*, unsigned int)
	{
	}

	void BaseApplication::OnWindowAboutToBeDestroyed(GLFWwindow*)
	{
	}

	int BaseApplication::OnGetExitCode()
	{
		return 0;
	}
}
