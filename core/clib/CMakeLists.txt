set(PERFORM_VALIDITY_CHECKS "YES" CACHE BOOL "If set, validity checks are included within all functions; otherwise, they are removed for speed. In this case, it is expected that inputs to functions are validated before being passed.")

set(PUBLIC_HEADERS_GENERAL
	include/${TARGETNAME_CLIB}/Bool.h
	include/${TARGETNAME_CLIB}/Check.h
	include/${TARGETNAME_CLIB}/Debug.h
	include/${TARGETNAME_CLIB}/Int.h
	include/${TARGETNAME_CLIB}/Ptr.h
	include/${TARGETNAME_CLIB}/Util.h
)

set(PUBLIC_HEADERS_ALL
	${PUBLIC_HEADERS_GENERAL}
)

add_library(${TARGETNAME_CLIB} INTERFACE)

if(PERFORM_VALIDITY_CHECKS)
	target_compile_definitions(${TARGETNAME_CLIB} INTERFACE AVIDLIB_VALIDITY_CHECKS)
endif()

target_include_directories(${TARGETNAME_CLIB} INTERFACE
	include
)

install(FILES ${PUBLIC_HEADERS_GENERAL} DESTINATION ${TARGETNAME_CLIB}/include/${TARGETNAME_CLIB})
