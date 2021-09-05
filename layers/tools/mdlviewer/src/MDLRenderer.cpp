#include <string.h>
#include "MDLRenderer.h"
#include "Sokol/SokolHeaders.h"

namespace MDLRenderer
{
	// Example triangle code adapted from https://github.com/floooh/sokol-samples/blob/master/glfw/triangle-glfw.c
	const float vertices[] =
	{
		// positions            // colors
		0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f, 1.0f
	};

	sg_buffer vbuf;
	sg_shader shd;
	sg_pipeline pip;

	void Init()
	{
		sg_buffer_desc vbufDesc;
		memset(&vbufDesc, 0, sizeof(vbufDesc));
		vbufDesc.data = SG_RANGE(vertices);
		vbuf = sg_make_buffer(&vbufDesc);

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
		shd = sg_make_shader(&shdDesc);

		sg_pipeline_desc pipDesc;
		memset(&pipDesc, 0, sizeof(pipDesc));
		pipDesc.shader = shd;
		pipDesc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT3;
		pipDesc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT4;
		pip = sg_make_pipeline(&pipDesc);
	}

	void Draw()
	{
		sg_bindings bind;
		memset(&bind, 0, sizeof(bind));
		bind.vertex_buffers[0] = vbuf;

		sg_apply_pipeline(pip);
		sg_apply_bindings(&bind);
		sg_draw(0, 3, 1);
	}

	void Cleanup()
	{
	}
}
