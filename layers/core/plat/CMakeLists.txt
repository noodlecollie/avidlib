set(PERFORM_VALIDITY_CHECKS "YES" CACHE BOOL "If set, validity checks are included within all functions; otherwise, they are removed for speed. In this case, it is expected that inputs to functions are validated before being passed.")

set(PUBLIC_HEADERS_GENERAL
	include/${TARGETNAME_PLAT}/Bool.h
	include/${TARGETNAME_PLAT}/Check.h
	include/${TARGETNAME_PLAT}/Debug.h
	include/${TARGETNAME_PLAT}/Int.h
	include/${TARGETNAME_PLAT}/Ptr.h
	include/${TARGETNAME_PLAT}/Util.h
)

set(PUBLIC_HEADERS_ALL
	${PUBLIC_HEADERS_GENERAL}
)

add_library(${TARGETNAME_PLAT} INTERFACE)

if(PERFORM_VALIDITY_CHECKS)
	target_compile_definitions(${TARGETNAME_PLAT} INTERFACE AVIDLIB_VALIDITY_CHECKS)
endif()

target_include_directories(${TARGETNAME_PLAT} INTERFACE
	include
)

install(FILES ${PUBLIC_HEADERS_GENERAL} DESTINATION ${TARGETNAME_PLAT}/include/${TARGETNAME_PLAT})
