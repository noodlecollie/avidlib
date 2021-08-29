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
#include "sokol/util/sokol_gfx_imgui.h"

#include "AVIDLib_ToolsCommon/DPI.h"
#include "ImGuiFileDialog.h"

static constexpr size_t WINDOW_DEFAULT_WIDTH = 800;
static constexpr size_t WINDOW_DEFAULT_HEIGHT = 600;
static constexpr const char* const KEY_OPEN_MDL_FILE = "OpenMDLFile";

static sg_imgui_t ImGUIPersistence;

static bool ExitRequested = false;
static bool OpenFileRequested = false;

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

	sg_imgui_init(&ImGUIPersistence);
}

static void DrawMainMenuBar()
{
	if ( ImGui::BeginMainMenuBar() )
	{
		if ( ImGui::BeginMenu("File") )
		{
			ImGui::MenuItem("Open", nullptr, &OpenFileRequested);
			ImGui::MenuItem("Exit", nullptr, &ExitRequested);

			ImGui::EndMenu();
		}

		if ( ImGui::BeginMenu("GFX Debug") )
		{
			ImGui::MenuItem("Buffers", nullptr, &ImGUIPersistence.buffers.open);
			ImGui::MenuItem("Images", nullptr, &ImGUIPersistence.images.open);
			ImGui::MenuItem("Shaders", nullptr, &ImGUIPersistence.shaders.open);
			ImGui::MenuItem("Pipelines", nullptr, &ImGUIPersistence.pipelines.open);
			ImGui::MenuItem("Passes", nullptr, &ImGUIPersistence.passes.open);
			ImGui::MenuItem("Calls", nullptr, &ImGUIPersistence.capture.open);

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

static void DrawOpenFileDialogue()
{
	if ( ImGuiFileDialog::Instance()->Display(KEY_OPEN_MDL_FILE, 32, ImVec2(0, 200)) )
	{
		if ( ImGuiFileDialog::Instance()->IsOk() )
		{
			// TODO: Do something with path.
		}

		ImGuiFileDialog::Instance()->Close();
	}
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

	DrawMainMenuBar();
	DrawOpenFileDialogue();

	sg_imgui_draw(&ImGUIPersistence);

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

	if ( OpenFileRequested )
	{
		static constexpr ImGuiWindowFlags FLAGS =
			ImGuiFileDialogFlags_DontShowHiddenFiles |
			ImGuiFileDialogFlags_DisableCreateDirectoryButton;

		ImGuiFileDialog::Instance()->OpenDialog(KEY_OPEN_MDL_FILE, "Choose MDL File", ".mdl", ".", 1, nullptr, FLAGS);
		OpenFileRequested = false;
	}
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
