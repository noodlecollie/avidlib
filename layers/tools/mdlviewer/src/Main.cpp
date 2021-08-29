#include <iostream>
#include <cstring>

#include "imgui.h"
#include "Sokol/SokolHeaders.h"

#include "AVIDLib_ToolsCommon/DPI.h"
#include "MainMenuBar.h"
#include "OpenMDLFileDialogue.h"
#include "Sokol/SokolGFXImGUI.h"

static constexpr size_t WINDOW_DEFAULT_WIDTH = 800;
static constexpr size_t WINDOW_DEFAULT_HEIGHT = 600;

static void Init()
{
	{
		sg_desc desc;
		memset(&desc, 0, sizeof(desc));

		desc.buffer_pool_size = 128;
		desc.image_pool_size = 128;
		desc.shader_pool_size = 32;
		desc.pipeline_pool_size = 64;
		desc.pass_pool_size = 16;
		desc.context_pool_size = 16;
		desc.sampler_cache_size = 64;
		desc.uniform_buffer_size = 4 * 1024 * 1024;
		desc.staging_buffer_size = 4 * 1024 * 1024;

		desc.context = sapp_sgcontext();

		sg_setup(desc);
	}

	{
		simgui_desc_t desc;
		memset(&desc, 0, sizeof(desc));

		desc.max_vertices = 65536;
		desc.color_format = SG_PIXELFORMAT_RGBA8;
		desc.depth_format = SG_PIXELFORMAT_DEPTH_STENCIL;
		desc.sample_count = 1;
		desc.dpi_scale = sapp_dpi_scale();

		simgui_setup(desc);
	}

	SokolGFXImGUI::Init();
}

static void Frame()
{
	sg_pass_action action;
	memset(&action, 0, sizeof(action));

	action.colors[0].action = SG_ACTION_CLEAR;
	action.colors[0].value.r = 200.0f / 255.0f;
	action.colors[0].value.g = 235.0f / 255.0f;
	action.colors[0].value.b = 250.0f / 255.0f;
	action.colors[0].value.a = 1.0f;

	sg_begin_default_pass(&action, sapp_width(), sapp_height());
	simgui_new_frame(sapp_width(), sapp_height(), 1.0f/60.0f);

	MainMenuBar::Draw();
	OpenMDLFileDialogue::Draw();

	SokolGFXImGUI::Draw();

	simgui_render();
	sg_end_pass();
	sg_commit();
}

static void Cleanup()
{
	simgui_shutdown();
	sg_shutdown();
}

static void Event(const sapp_event* event)
{
	simgui_handle_event(event);

	MainMenuBar::Poll();
	OpenMDLFileDialogue::Poll();
}

sapp_desc sokol_main(int, char**)
{
	float dpi = 1.0f;
	ALT_Common::GetDPIScale(&dpi, nullptr);

	sapp_desc desc;
	memset(&desc, 0, sizeof(desc));

	desc.init_cb = &Init;
	desc.frame_cb = &Frame;
	desc.cleanup_cb = &Cleanup;
	desc.event_cb = &Event;
	desc.width = WINDOW_DEFAULT_WIDTH * dpi;
	desc.height = WINDOW_DEFAULT_HEIGHT * dpi;
	desc.win32_console_attach = true;

	return desc;
}
