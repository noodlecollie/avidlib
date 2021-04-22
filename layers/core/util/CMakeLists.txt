set(PERFORM_VALIDITY_CHECKS "YES" CACHE BOOL "If set, validity checks are included within all functions; otherwise, they are removed for speed. In this case, it is expected that inputs to functions are validated before being passed.")

set(PUBLIC_HEADERS_GENERAL
include/${TARGETNAME_UTIL}/Check.h
include/${TARGETNAME_UTIL}/Debug.h
include/${TARGETNAME_UTIL}/Util.h
)

add_library(${TARGETNAME_UTIL} INTERFACE)

if(PERFORM_VALIDITY_CHECKS)
	target_compile_definitions(${TARGETNAME_UTIL} INTERFACE AVIDLIB_VALIDITY_CHECKS)
endif()

target_link_libraries(${TARGETNAME_UTIL} INTERFACE ${TARGETNAME_PLAT})

target_include_directories(${TARGETNAME_UTIL} INTERFACE
	include
)
