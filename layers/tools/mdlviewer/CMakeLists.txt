set(TARGETNAME_MDLVIEWER MDLViewer)
set(TOOLS_MDLVIEWER "NO" CACHE BOOL "If set, builds the MDLViewer tool.")

set(SOURCES
	src/sokol/sokolApp.cpp
	src/sokol/sokolGFX.cpp
	src/sokol/sokolGlue.cpp
	src/main.cpp
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
		target_link_libraries(${TARGETNAME_MDLVIEWER} PRIVATE ${TARGETNAME_THIRDPARTY_IMGUI})
		target_link_libraries(${TARGETNAME_MDLVIEWER} PRIVATE glfw)
		target_link_libraries(${TARGETNAME_MDLVIEWER} PRIVATE ${TARGETNAME_THIRDPARTY_GL3W})
		target_link_libraries(${TARGETNAME_MDLVIEWER} PRIVATE ${TARGETNAME_THIRDPARTY_SOKOL})

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

		install(TARGETS ${TARGETNAME_MDLVIEWER}
			ARCHIVE DESTINATION ${TARGETNAME_MDLVIEWER}
			LIBRARY DESTINATION ${TARGETNAME_MDLVIEWER}
			RUNTIME DESTINATION ${TARGETNAME_MDLVIEWER}
		)
	else()
		message(WARNING "Not building MDL Viewer as BUILD_TOOLS was not set.")
	endif()
endif()
