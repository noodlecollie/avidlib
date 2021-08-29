set(PUBLIC_HEADERS
	ImGuiFileDialog.h
	ImGuiFileDialogConfig.h
)

set(SOURCES
	ImGuiFileDialog.cpp
)

# This is only ever used internally, so is built statically:
add_library(${TARGETNAME_THIRDPARTY_IMGUIFILEDIALOG} STATIC ${PUBLIC_HEADERS} ${SOURCES})

target_link_libraries(${TARGETNAME_THIRDPARTY_IMGUIFILEDIALOG} PUBLIC ${TARGETNAME_THIRDPARTY_IMGUI})

target_include_directories(${TARGETNAME_THIRDPARTY_IMGUIFILEDIALOG} PUBLIC
	.
)
