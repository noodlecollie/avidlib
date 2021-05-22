add_library(bgfx_imgui
	bgfx_imgui/include/bgfx_imgui/bgfx_imgui.h
	bgfx_imgui/src/bgfx_imgui.cpp
)

target_include_directories(bgfx_imgui PUBLIC
	bgfx_imgui/include
)

target_include_directories(bgfx_imgui PRIVATE
	bgfx_imgui/src
)

target_link_libraries(bgfx_imgui PUBLIC bgfx)
target_link_libraries(bgfx_imgui PUBLIC bx)
target_link_libraries(bgfx_imgui PUBLIC bimg)
target_link_libraries(bgfx_imgui PUBLIC ${TARGETNAME_THIRDPARTY_IMGUI})
