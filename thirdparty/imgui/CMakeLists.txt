set(PUBLIC_HEADERS
	imgui/imgui.h
	imgui/backends/imgui_impl_glfw.h
	imgui/backends/imgui_impl_opengl3.h
)

set(SOURCES
	imgui/backends/imgui_impl_glfw.cpp
	imgui/backends/imgui_impl_opengl3.cpp
	imgui/imconfig.h
	imgui/imgui_demo.cpp
	imgui/imgui_draw.cpp
	imgui/imgui_internal.h
	imgui/imgui_tables.cpp
	imgui/imgui_widgets.cpp
	imgui/imgui.cpp
	imgui/imstb_rectpack.h
	imgui/imstb_textedit.h
	imgui/imstb_truetype.h
)

add_library(${TARGETNAME_THIRDPARTY_IMGUI} STATIC ${PUBLIC_HEADERS} ${SOURCES})
target_link_libraries(${TARGETNAME_THIRDPARTY_IMGUI} PRIVATE glfw)
target_link_libraries(${TARGETNAME_THIRDPARTY_IMGUI} PRIVATE ${TARGETNAME_THIRDPARTY_GL3W})

target_include_directories(${TARGETNAME_THIRDPARTY_IMGUI} PUBLIC
	imgui
	imgui/backends
)

if(NOT MSVC)
	target_compile_options(${TARGETNAME_THIRDPARTY_IMGUI} PRIVATE
		"-Wno-float-equal"
	)
endif()
