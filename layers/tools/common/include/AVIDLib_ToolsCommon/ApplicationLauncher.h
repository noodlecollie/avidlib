#ifndef AVIDLIB_TOOLS_COMMON_APPLICATIONLAUNCHER_H
#define AVIDLIB_TOOLS_COMMON_APPLICATIONLAUNCHER_H

#include "AVIDLib_ToolsCommon/ApplicationCallbacks.h"

namespace ALT_Common
{
	int RunApplication(int argc, char** argv, ApplicationCallbacks* application);
}

#endif // AVIDLIB_TOOLS_COMMON_APPLICATIONLAUNCHER_H
