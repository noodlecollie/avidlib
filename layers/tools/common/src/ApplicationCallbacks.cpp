#include "AVIDLib_ToolsCommon/ApplicationCallbacks.h"

namespace ALT_Common
{
	void ApplicationCallbacks::OnArguments(int, char**)
	{
	}

	void ApplicationCallbacks::OnGetInitialState(InitialState&)
	{
	}

	ApplicationCallbacks::InitResult ApplicationCallbacks::OnWindowCreated(GLFWwindow*, const char*)
	{
		return InitResult::Successful;
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

	int ApplicationCallbacks::OnGetExitCode()
	{
		return 0;
	}
}
