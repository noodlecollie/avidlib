set(PERFORM_VALIDITY_CHECKS "YES" CACHE BOOL "If set, validity checks are included within all functions; otherwise, they are removed for speed. In this case, it is expected that inputs to functions are validated before being passed.")

set(PUBLIC_HEADERS_GENERAL
	include/${TARGETNAME_CORE}/Bool.h
	include/${TARGETNAME_CORE}/Check.h
	include/${TARGETNAME_CORE}/Debug.h
	include/${TARGETNAME_CORE}/Int.h
	include/${TARGETNAME_CORE}/Ptr.h
	include/${TARGETNAME_CORE}/Util.h
)

set(PUBLIC_HEADERS_ALL
	${PUBLIC_HEADERS_GENERAL}
)

add_library(${TARGETNAME_CORE} INTERFACE)

if(PERFORM_VALIDITY_CHECKS)
	target_compile_definitions(${TARGETNAME_CORE} INTERFACE AVIDLIB_VALIDITY_CHECKS)
endif()

target_include_directories(${TARGETNAME_CORE} INTERFACE
	include
)

install(FILES ${PUBLIC_HEADERS_GENERAL} DESTINATION ${TARGETNAME_CORE}/include/${TARGETNAME_CORE})
