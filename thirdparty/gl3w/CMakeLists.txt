if(NOT WIN32)
	message(FATAL_ERROR "gl3w is not yet set up for non-Windows platforms.")
endif()

set(PUBLIC_HEADERS
	include/GL/gl3w.h
	include/GL/glcorearb.h
	include/KHR/khrplatform.h
)

set(SOURCES_WIN32
	src/win32/gl3w.c
)

add_library(${TARGETNAME_THIRDPARTY_GL3W} STATIC ${PUBLIC_HEADERS} ${SOURCES_WIN32})

target_include_directories(${TARGETNAME_THIRDPARTY_GL3W} PUBLIC
	include
)
