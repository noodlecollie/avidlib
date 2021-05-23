#ifndef AVIDLIB_TOOLS_COMMON_APPLICATIONLAUNCHER_H
#define AVIDLIB_TOOLS_COMMON_APPLICATIONLAUNCHER_H

#include "AVIDLib_ToolsCommon/IApplicationCallbacks.h"

namespace ALT_Common
{
	// Exit codes > 0 are reserved for the application.
	// Exit codes < 0 are specified here.
	enum ExitCode : int
	{
		ExitSuccess = 0,
		ExitGenericError = -1,
		ExitUnableToInitGLFW = -2,
		ExitUnableToCreateGLFWWindow = -3,
		ExitCustomInitStateFailed = -4
	};

	int RunApplication(int argc, char** argv, IApplicationCallbacks* application);
}

#endif // AVIDLIB_TOOLS_COMMON_APPLICATIONLAUNCHER_H
