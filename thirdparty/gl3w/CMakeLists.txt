set(PUBLIC_HEADERS
	include/GL/gl3w.h
	include/GL/glcorearb.h
	include/KHR/khrplatform.h
)

set(SOURCES
	src/gl3w.c
)

add_library(${TARGETNAME_THIRDPARTY_GL3W} STATIC ${PUBLIC_HEADERS} ${SOURCES})

target_include_directories(${TARGETNAME_THIRDPARTY_GL3W} PUBLIC
	include
)
