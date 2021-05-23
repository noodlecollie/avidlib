add_library(${TARGETNAME_THIRDPARTY_BGFX_IMGUI} STATIC
	include/bgfx_imgui/BGFXImGuiAdapter.h
	src/BGFXImGuiAdapter.cpp
)

target_include_directories(${TARGETNAME_THIRDPARTY_BGFX_IMGUI} PUBLIC
	include
)

target_include_directories(${TARGETNAME_THIRDPARTY_BGFX_IMGUI} PRIVATE
	src
)

target_link_libraries(${TARGETNAME_THIRDPARTY_BGFX_IMGUI} PUBLIC bgfx)
target_link_libraries(${TARGETNAME_THIRDPARTY_BGFX_IMGUI} PUBLIC bx)
target_link_libraries(${TARGETNAME_THIRDPARTY_BGFX_IMGUI} PUBLIC bimg)
target_link_libraries(${TARGETNAME_THIRDPARTY_BGFX_IMGUI} PUBLIC ${TARGETNAME_THIRDPARTY_IMGUI})
