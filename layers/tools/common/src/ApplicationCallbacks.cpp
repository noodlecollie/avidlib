#include "AVIDLib_ToolsCommon/ApplicationCallbacks.h"

namespace ALT_Common
{
	void ApplicationCallbacks::OnArguments(int, char**)
	{
	}

	void ApplicationCallbacks::OnGetInitialState(InitialState&)
	{
	}

	void ApplicationCallbacks::OnWindowCreated(GLFWwindow*)
	{
	}

	ApplicationCallbacks::FrameResult ApplicationCallbacks::OnWindowNewFrame(GLFWwindow*)
	{
		return FrameResult::NoAction;
	}

	void ApplicationCallbacks::OnWindowResized(GLFWwindow*, size_t, size_t)
	{
	}

	void ApplicationCallbacks::OnWindowAboutToBeDestroyed(GLFWwindow*)
	{
	}
}
