set(TARGETNAME_MDLVIEWER MDLViewer)
set(TOOLS_MDLVIEWER "NO" CACHE BOOL "If set, builds the MDLViewer tool.")

set(SOURCES
	src/Sokol/SokolApp.cpp
	src/Sokol/SokolGFX.cpp
	src/Sokol/SokolGFXImGUI.cpp
	src/Sokol/SokolGlue.cpp
	src/Sokol/SokolImGUI.cpp
	src/InfoDisplay.cpp
	src/Main.cpp
	src/MainMenuBar.cpp
	src/MDLLoader.cpp
	src/MDLRenderer.cpp
	src/OpenMDLFileDialogue.cpp
)

if(TOOLS_ALL OR TOOLS_MDLVIEWER)
	if(BUILD_TOOLS)
		if(UNIX)
			find_package(OpenGL REQUIRED)
			find_package(Threads REQUIRED)
			find_package(X11 REQUIRED COMPONENTS Xi Xcursor)
		endif()

		add_executable(${TARGETNAME_MDLVIEWER} ${SOURCES})
		target_include_directories(${TARGETNAME_MDLVIEWER} PRIVATE src)

		target_link_libraries(${TARGETNAME_MDLVIEWER} PRIVATE
			${TARGETNAME_THIRDPARTY_IMGUI}
			${TARGETNAME_THIRDPARTY_IMGUIFILEDIALOG}
			glfw
			${TARGETNAME_THIRDPARTY_GL3W}
			${TARGETNAME_THIRDPARTY_SOKOL}
			${TARGETNAME_TOOLS_COMMON}
			${TARGETNAME_CONTAINERS}
			${TARGETNAME_IO}
		)

		if(NOT MSVC)
			target_compile_options(${TARGETNAME_MDLVIEWER} PRIVATE -pthread)
			target_link_options(${TARGETNAME_MDLVIEWER} PRIVATE -pthread)
		endif()

		if(UNIX)
			target_link_libraries(${TARGETNAME_MDLVIEWER} PRIVATE
				${X11_LIBRARIES}
				${X11_Xi_LIB}
				${X11_Xcursor_LIB}
				${OPENGL_LIBRARIES}
			)
		endif()

		target_compile_definitions(${TARGETNAME_MDLVIEWER} PRIVATE "$<$<CONFIG:DEBUG>:SOKOL_TRACE_HOOKS>")

		install(TARGETS ${TARGETNAME_MDLVIEWER}
			ARCHIVE DESTINATION ${TARGETNAME_MDLVIEWER}
			LIBRARY DESTINATION ${TARGETNAME_MDLVIEWER}
			RUNTIME DESTINATION ${TARGETNAME_MDLVIEWER}
		)
	else()
		message(WARNING "Not building MDL Viewer as BUILD_TOOLS was not set.")
	endif()
endif()
