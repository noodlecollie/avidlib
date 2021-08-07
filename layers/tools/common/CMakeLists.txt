set(PUBLIC_HEADERS_ALL
	include/${TARGETNAME_TOOLS_COMMON}/DPI.h
)

if(WIN32)
	# TODO: Add Win32 sources here
elseif(UNIX)
	set(SOURCES_LINUX
		src/DPI_Linux.cpp
	)

	set(SOURCES_ALL ${SOURCES_LINUX})
endif()

if(BUILD_TOOLS)
	if(UNIX)
		find_package(X11 REQUIRED COMPONENTS Xrandr)
	endif()

	# This library is intended only to be used internally,
	# so is always built as static and never gets installed anywhere.
	add_library(${TARGETNAME_TOOLS_COMMON} STATIC ${PUBLIC_HEADERS_ALL} ${SOURCES_ALL})
	target_include_directories(${TARGETNAME_TOOLS_COMMON} PUBLIC include)
	target_include_directories(${TARGETNAME_TOOLS_COMMON} PRIVATE src)

	if(UNIX)
		target_link_libraries(${TARGETNAME_TOOLS_COMMON} PRIVATE
			${X11_LIBRARIES}
			${X11_Xrandr_LIB}
		)
	endif()
endif()
