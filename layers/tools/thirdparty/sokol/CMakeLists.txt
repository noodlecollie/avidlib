add_library(${TARGETNAME_THIRDPARTY_SOKOL} INTERFACE
	sokol/sokol_app.h
	sokol/sokol_args.h
	sokol/sokol_audio.h
	sokol/sokol_fetch.h
	sokol/sokol_gfx.h
	sokol/sokol_glue.h
	sokol/sokol_time.h
	sokol/util/sokol_color.h
	sokol/util/sokol_debugtext.h
	sokol/util/sokol_fontstash.h
	sokol/util/sokol_gfx_imgui.h
	sokol/util/sokol_gl.h
	sokol/util/sokol_imgui.h
	sokol/util/sokol_memtrack.h
	sokol/util/sokol_nuklear.h
	sokol/util/sokol_shape.h
)

target_include_directories(${TARGETNAME_THIRDPARTY_SOKOL} INTERFACE
	.
)
