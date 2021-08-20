#include <shellscalingapi.h>

#include "AVIDLib_ToolsCommon/DPI.h"

namespace ALT_Common
{
	struct sEnumInfo
	{
		int iIndex;
		HMONITOR hMonitor;
	};

	static BOOL CALLBACK GetMonitorByIndex(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
	{
		(void)hdcMonitor;
		(void)lprcMonitor;

		sEnumInfo *info = (sEnumInfo*)dwData;

		if (--info->iIndex < 0)
		{
			info->hMonitor = hMonitor;
			return FALSE;
		}

		return TRUE;
	}

	void GetDPIScale(float& xScale, float& yScale, int screen)
	{
		xScale = 1.0f;
		yScale = 1.0f;

		sEnumInfo info;
		info.iIndex = screen;
		info.hMonitor = nullptr;

		EnumDisplayMonitors(nullptr, nullptr, GetMonitorByIndex, (LPARAM)&info);
		if ( !info.hMonitor )
		{
			return;
		}

		UINT dpiX = 96;
		UINT dpiY = 96;

		if ( GetDpiForMonitor(info.hMonitor, MDT_DEFAULT, &dpiX, &dpiY) == S_OK )
		{
			xScale = static_cast<float>(dpiX) / 96.0f;
			yScale = static_cast<float>(dpiY) / 96.0f;
		}
	}
}
