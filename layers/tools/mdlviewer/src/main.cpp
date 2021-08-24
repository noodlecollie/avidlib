#include <iostream>
#include <cstring>

#include "imgui.h"

// The include order matters here.
// sokol_app.h and sokol_gfx.h must be included first,
// so that they can provide definitions to later headers.
#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_glue.h"
#include "sokol/util/sokol_imgui.h"

#include "AVIDLib_ToolsCommon/DPI.h"

static float HorizontalDPI = 1.0f;
static float VerticalDPI = 1.0f;

static bool ExitRequested = false;

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
		desc.dpi_scale = std::max(HorizontalDPI, VerticalDPI);

		simgui_setup(desc);
	}
}

static void DrawMainMenu()
{
	if ( ImGui::BeginMainMenuBar() )
	{
		if ( ImGui::BeginMenu("File") )
		{
			ImGui::MenuItem("Exit", nullptr, &ExitRequested);

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

static void Frame()
{
	sg_pass_action action;
	memset(&action, 0, sizeof(action));

	action.colors[0].action = SG_ACTION_CLEAR;
	action.colors[0].value.r = 0.91f;
	action.colors[0].value.g = 0.99f;
	action.colors[0].value.b = 1.0f;
	action.colors[0].value.a = 1.0f;

	sg_begin_default_pass(&action, sapp_width(), sapp_height());
	simgui_new_frame(sapp_width(), sapp_height(), 1.0f/60.0f);

	DrawMainMenu();

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

	if ( ExitRequested )
	{
		sapp_request_quit();
		ExitRequested = false;
	}
}

sapp_desc sokol_main(int, char**)
{
	ALT_Common::GetDPIScale(HorizontalDPI, VerticalDPI);

	sapp_desc desc;
	memset(&desc, 0, sizeof(desc));

	desc.init_cb = &Init;
	desc.frame_cb = &Frame;
	desc.cleanup_cb = &Cleanup;
	desc.event_cb = &Event;
	desc.width = 640;
	desc.height = 480;
	desc.high_dpi = HorizontalDPI > 1.0f || VerticalDPI > 1.0f;
	desc.win32_console_attach = true;

	return desc;
}
