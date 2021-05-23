set(PUBLIC_HEADERS_ALL
	include/${TARGETNAME_TOOLS_COMMON}/ApplicationLauncher.h
	include/${TARGETNAME_TOOLS_COMMON}/BaseApplication.h
	include/${TARGETNAME_TOOLS_COMMON}/IApplicationCallbacks.h
	include/${TARGETNAME_TOOLS_COMMON}/WinSysHelpers.h
)

set(SOURCES_GENERAL
	src/ApplicationLauncher.cpp
	src/BaseApplication.cpp
)

set(SOURCES_X11
	src/x11/WinSysHelpers_X11.cpp
)

if(WIN32)
	# TODO: Add Win32 sources here
else()
	set(SOURCES_ALL ${SOURCES_GENERAL} ${SOURCES_X11})
endif()

if(BUILD_TOOLS)
	# This library is intended only to be used internally,
	# so is always built as static and never gets installed anywhere.
	add_library(${TARGETNAME_TOOLS_COMMON} STATIC ${PUBLIC_HEADERS_ALL} ${SOURCES_ALL})

	target_include_directories(${TARGETNAME_TOOLS_COMMON} PUBLIC include)
	target_include_directories(${TARGETNAME_TOOLS_COMMON} PRIVATE src)

	target_link_libraries(${TARGETNAME_TOOLS_COMMON} PRIVATE glfw)
	target_link_libraries(${TARGETNAME_TOOLS_COMMON} PRIVATE bgfx)
	target_link_libraries(${TARGETNAME_TOOLS_COMMON} PRIVATE ${TARGETNAME_THIRDPARTY_IMGUI})
endif()
