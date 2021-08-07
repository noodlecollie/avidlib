#include <iostream>
#include <cstring>

#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_glue.h"

static void Init()
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

static void Frame()
{
	sg_pass_action action;
	memset(&action, 0, sizeof(action));

	action.colors[0].action = SG_ACTION_CLEAR;
	action.colors[0].value.r = 1.0f;
	action.colors[0].value.g = 0.0f;
	action.colors[0].value.b = 0.0f;
	action.colors[0].value.a = 1.0f;

	sg_begin_default_pass(&action, sapp_width(), sapp_height());
	sg_end_pass();
	sg_commit();
}

static void Cleanup()
{
	sg_shutdown();
}

static void Event(const sapp_event*)
{
}

sapp_desc sokol_main(int, char**)
{
	sapp_desc desc;
	memset(&desc, 0, sizeof(desc));

	desc.init_cb = &Init;
	desc.frame_cb = &Frame;
	desc.cleanup_cb = &Cleanup;
	desc.event_cb = &Event;
	desc.width = 640;
	desc.height = 480;

	return desc;
}
