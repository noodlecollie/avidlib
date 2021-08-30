#define SOKOL_GFX_IMGUI_IMPL
#include "imgui.h"
#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/util/sokol_imgui.h"
#include "sokol/util/sokol_gfx_imgui.h"

namespace SokolGFXImGUI
{
	static sg_imgui_t InternalPersistence;

	sg_imgui_t* GetPersistence()
	{
		return &InternalPersistence;
	}

	void Init()
	{
		sg_imgui_init(&InternalPersistence);
	}

	void Draw()
	{
		sg_imgui_draw(&InternalPersistence);
	}

	void Cleanup()
	{
		sg_imgui_discard(&InternalPersistence);
	}
}
