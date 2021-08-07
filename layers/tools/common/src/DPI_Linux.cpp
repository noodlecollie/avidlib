#include <string>
#include <cmath>
#include <X11/extensions/Xrandr.h>
#include "AVIDLib_ToolsCommon/DPI.h"

namespace ALT_Common
{
	void GetDPIScale(float& xScale, float& yScale, int screen)
	{
		static constexpr size_t WIDTH_4K = 3840;
		static constexpr size_t HEIGHT_4K = 2160;
		static constexpr size_t MIN_DIM_4K = std::min(WIDTH_4K, HEIGHT_4K);

		xScale = 1.0f;
		yScale = 1.0f;

		if ( screen < 0 )
		{
			screen = 0;
		}

		Display* display = XOpenDisplay(":0");
		XRRScreenResources* screenRes = XRRGetScreenResources(display, DefaultRootWindow(display));

		if ( !screenRes || screenRes->ncrtc < 1 )
		{
			return;
		}

		XRRCrtcInfo* crtcInfo = XRRGetCrtcInfo(display, screenRes, screenRes->crtcs[std::min(screen, screenRes->ncrtc - 1)]);

		if ( !crtcInfo )
		{
			return;
		}

		// Cheap: consider any resolution under 4K to use DPI scaling of 1.
		if ( std::min(crtcInfo->width, crtcInfo->height) < MIN_DIM_4K )
		{
			return;
		}

		// Cater for if the screen is rotated.
		if ( crtcInfo->width < crtcInfo->height )
		{
			xScale = 1.0f + static_cast<float>(crtcInfo->height / WIDTH_4K);
			yScale = 1.0f + static_cast<float>(crtcInfo->width / HEIGHT_4K);
		}
		else
		{
			xScale = 1.0f + static_cast<float>(crtcInfo->width / WIDTH_4K);
			yScale = 1.0f + static_cast<float>(crtcInfo->height / HEIGHT_4K);
		}
	}
}
