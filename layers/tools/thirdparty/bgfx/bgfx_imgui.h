#ifndef CUSTOM_HELPER_BGFX_IMGUI_H
#define CUSTOM_HELPER_BGFX_IMGUI_H

// This file wraps the internal BGFX ImGUI helper files, which are something of a mess IMO.
// The helper file itself is just called imgui.h, so we can't include it directlt in other
// projects in this repo because it would clash with the *actual* imgui.h...

#include <cstdint>

namespace bx
{
	struct AllocatorI;
}

namespace bgfx
{
	typedef uint16_t ViewId;
}

namespace CustomHelper_BGFX_Imgui
{
	void Create(float fontSize = 18.0f, bx::AllocatorI* allocator = nullptr);
	void Destroy();

	void BeginFrame(int32_t mx,
					int32_t my,
					uint8_t button,
					int32_t scroll,
					uint16_t width,
					uint16_t height,
					int inputChar = -1,
					bgfx::ViewId view = 255);

	void EndFrame();
}

#endif // CUSTOM_HELPER_BGFX_IMGUI_H
