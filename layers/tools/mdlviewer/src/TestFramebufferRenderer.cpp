#include <string.h>
#include "TestFramebufferRenderer.h"
#include "Sokol/SokolHeaders.h"

namespace TestFramebufferRenderer
{
	// Adapted from https://github.com/GeertArien/learnopengl-examples/blob/master/src/4-5-framebuffers/1-render-to-texture.c

	static constexpr int SLOT_diffuse_texture = 0;

	const float vertices[] =
	{
		// positions           // colors
		 0.0f,  0.5f, 0.5f,    1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,    0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f, 1.0f
	};

	const float quad_vertices[] =
	{
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	static struct
	{
		struct
		{
			sg_pass pass;
			sg_pass_desc pass_desc;
			sg_pass_action pass_action;
			sg_pipeline pip;
			sg_bindings bind_triangle;
		} offscreen;

		struct
		{
			sg_pass_action pass_action;
			sg_pipeline pip;
			sg_bindings bind;
		} display;
	} state;

	void create_offscreen_pass(int width, int height)
	{
		/* destroy previous resource (can be called for invalid id) */
		sg_destroy_pass(state.offscreen.pass);
		sg_destroy_image(state.offscreen.pass_desc.color_attachments[0].image);
		sg_destroy_image(state.offscreen.pass_desc.depth_stencil_attachment.image);

		/* create offscreen rendertarget images and pass */
		sg_image_desc color_img_desc;
		memset(&color_img_desc, 0, sizeof(color_img_desc));

		color_img_desc.render_target = true;
		color_img_desc.width = width;
		color_img_desc.height = height;
		color_img_desc.pixel_format = SG_PIXELFORMAT_RGBA8;
		color_img_desc.wrap_u = SG_WRAP_CLAMP_TO_EDGE;
		color_img_desc.wrap_v = SG_WRAP_CLAMP_TO_EDGE;
		color_img_desc.min_filter = SG_FILTER_LINEAR;
		color_img_desc.mag_filter = SG_FILTER_LINEAR;
		color_img_desc.label = "colour-image";

		sg_image color_img = sg_make_image(&color_img_desc);

		sg_image_desc depth_img_desc = color_img_desc;

		depth_img_desc.pixel_format = SG_PIXELFORMAT_DEPTH;
		depth_img_desc.label = "depth-image";

		sg_image depth_img = sg_make_image(&depth_img_desc);

		state.offscreen.pass_desc.color_attachments[0].image = color_img;
		state.offscreen.pass_desc.depth_stencil_attachment.image = depth_img;
		state.offscreen.pass_desc.label = "offscreen-pass";

		state.offscreen.pass = sg_make_pass(&state.offscreen.pass_desc);

		/* also need to update the fullscreen-quad texture bindings */
		state.display.bind.fs_images[SLOT_diffuse_texture] = color_img;
	}

	void Init()
	{
		create_offscreen_pass(128, 128);

		state.offscreen.pass_action.colors[0].action = SG_ACTION_CLEAR;
		state.offscreen.pass_action.colors[0].value.r = 0.1f;
		state.offscreen.pass_action.colors[0].value.g = 0.1f;
		state.offscreen.pass_action.colors[0].value.b = 0.1f;
		state.offscreen.pass_action.colors[0].value.a = 1.0f;

		state.display.pass_action.colors[0].action = SG_ACTION_DONTCARE;
		state.display.pass_action.depth.action = SG_ACTION_DONTCARE;
		state.display.pass_action.stencil.action = SG_ACTION_DONTCARE;

		sg_buffer_desc vbufDesc;
		memset(&vbufDesc, 0, sizeof(vbufDesc));
		vbufDesc.data = SG_RANGE(vertices);
		sg_buffer vbuf = sg_make_buffer(&vbufDesc);

		sg_buffer_desc quadBufferDesc;
		memset(&quadBufferDesc, 0, sizeof(quadBufferDesc));
		quadBufferDesc.data = SG_RANGE(quad_vertices);
		sg_buffer quadBuffer = sg_make_buffer(&quadBufferDesc);

		state.offscreen.bind_triangle.vertex_buffers[0] = vbuf;

		/* resource bindings to render an fullscreen-quad */
		state.display.bind.vertex_buffers[0] = quadBuffer;

		sg_shader_desc shdDesc;
		memset(&shdDesc, 0, sizeof(shdDesc));
		shdDesc.vs.source =
			"#version 330\n"
			"layout(location=0) in vec4 position;\n"
			"layout(location=1) in vec4 color0;\n"
			"out vec4 color;\n"
			"void main() {\n"
			"  gl_Position = position;\n"
			"  color = color0;\n"
			"}\n";
		shdDesc.fs.source =
			"#version 330\n"
			"in vec4 color;\n"
			"out vec4 frag_color;\n"
			"void main() {\n"
			"  frag_color = color;\n"
			"}\n";
		sg_shader shd1 = sg_make_shader(&shdDesc);

		shdDesc.vs.source =
			"#version 330\n"
			"in vec2 a_pos;\n"
			"in vec2 a_tex_coords;\n"
			"out vec2 tex_coords;\n"
			"void main() {\n"
			"  gl_Position = vec4(a_pos, 0.0, 1.0);\n"
			"  tex_coords = a_tex_coords;\n"
			"}\n";

		shdDesc.fs.source =
			"#version 330\n"
			"in vec2 tex_coords;\n"
			"out vec4 frag_color;\n"
			"uniform sampler2D diffuse_texture;\n"
			"void main() {\n"
			"  frag_color = texture(diffuse_texture, tex_coords);\n"
			"}\n";
		sg_shader shd2 = sg_make_shader(&shdDesc);

		/* create a pipeline object for offscreen pass */
		sg_pipeline_desc pipelineDesc;
		memset(&pipelineDesc, 0, sizeof(pipelineDesc));

		pipelineDesc.shader = shd1;
		pipelineDesc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT3;
		pipelineDesc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT4;
		pipelineDesc.depth.compare = SG_COMPAREFUNC_LESS;
		pipelineDesc.depth.write_enabled = true;
		pipelineDesc.label = "offscreen-pipeline";

		state.offscreen.pip = sg_make_pipeline(&pipelineDesc);

		/* and another pipeline-state-object for the display pass */
		sg_pipeline_desc pipelineDesc2;
		memset(&pipelineDesc2, 0, sizeof(pipelineDesc2));

		pipelineDesc2.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT2;
		pipelineDesc2.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT2;
		pipelineDesc2.shader = shd2;
		pipelineDesc2.label = "display-pipeline";

		state.display.pip = sg_make_pipeline(&pipelineDesc2);
	}

	void Draw()
	{
		sg_begin_pass(state.offscreen.pass, &state.offscreen.pass_action);

		sg_apply_pipeline(state.offscreen.pip);
		sg_apply_bindings(&state.offscreen.bind_triangle);
		sg_draw(0, 3, 1);

		sg_end_pass();

		sg_begin_default_pass(&state.display.pass_action, sapp_width(), sapp_height());

		sg_apply_pipeline(state.display.pip);
		sg_apply_bindings(&state.display.bind);
		sg_draw(0, 6, 1);

		sg_end_pass();

		sg_commit();
	}

	void Cleanup()
	{

	}
}
