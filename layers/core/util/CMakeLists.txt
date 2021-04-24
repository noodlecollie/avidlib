set(PERFORM_VALIDITY_CHECKS "YES" CACHE BOOL "If set, validity checks are included within all functions; otherwise, they are removed for speed. In this case, it is expected that inputs to functions are validated before being passed.")
set(PERFORM_MALLOC_CHECKS "YES" CACHE BOOL "If set, calls to malloc are checked to have succeeded before the call returns; otherwise, this check is removed for speed.")

set(PUBLIC_HEADERS_GENERAL
include/${TARGETNAME_INTERNAL_UTIL}/Check.h
include/${TARGETNAME_INTERNAL_UTIL}/Debug.h
include/${TARGETNAME_INTERNAL_UTIL}/Util.h
)

set(PUBLIC_HEADERS_ALL
	${PUBLIC_HEADERS_GENERAL}
)

set(SOURCES_ALL
	src/Check.c
)

# This library is intended only to be used internally,
# so is always built as static and never gets installed anywhere.
add_library(${TARGETNAME_INTERNAL_UTIL} STATIC ${PUBLIC_HEADERS_ALL} ${SOURCES_ALL})

if(PERFORM_VALIDITY_CHECKS)
	target_compile_definitions(${TARGETNAME_INTERNAL_UTIL} PUBLIC AVIDLIB_VALIDITY_CHECKS)
endif()

if(PERFORM_MALLOC_CHECKS)
	target_compile_definitions(${TARGETNAME_INTERNAL_UTIL} PUBLIC AVIDLIB_MALLOC_CHECKS)
endif()

target_link_libraries(${TARGETNAME_INTERNAL_UTIL} PUBLIC ${TARGETNAME_PLAT})

target_include_directories(${TARGETNAME_INTERNAL_UTIL} PUBLIC
	include
)

target_include_directories(${TARGETNAME_INTERNAL_UTIL} PRIVATE
	src
)
