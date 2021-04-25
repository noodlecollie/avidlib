set(PUBLIC_HEADERS_GENERAL
	include/${TARGETNAME_PLAT}/Bool.h
	include/${TARGETNAME_PLAT}/Float.h
	include/${TARGETNAME_PLAT}/Int.h
	include/${TARGETNAME_PLAT}/Memory.h
	include/${TARGETNAME_PLAT}/Ptr.h
	include/${TARGETNAME_PLAT}/String.h
	include/${TARGETNAME_PLAT}/VariadicArgs.h
)

add_library(${TARGETNAME_PLAT} INTERFACE)

if(WIN32)
	# We wrap the unsafe functions in this target, so we don't need to be warned about using them.
	target_compile_definitions(${TARGETNAME_PLAT} INTERFACE _CRT_SECURE_NO_WARNINGS)
endif()

target_include_directories(${TARGETNAME_PLAT} INTERFACE
	include
)

install(FILES ${PUBLIC_HEADERS_GENERAL} DESTINATION ${TARGETNAME_PLAT}/include/${TARGETNAME_PLAT})
