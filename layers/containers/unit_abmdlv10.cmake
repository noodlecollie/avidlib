set(HEADERS_ABMDLV10
	include/${TARGETNAME_CONTAINERS}/ABMDLv10/ContainerDefinitions.h
	include/${TARGETNAME_CONTAINERS}/ABMDLv10/Model.h
)

set(SOURCES_ABMDLV10
	src/ABMDLv10/Model.c
)

macro(init_unit_abmdlv10 headers sources defs forceUse)
	set(CONTAINERS_ABMDLV10 "NO" CACHE BOOL "Includes ABMDLv10 code in containers library.")

	if(CONTAINERS_ABMDLV10 OR ${forceUse})
		set(${headers}
			${${headers}}
			${HEADERS_ABMDLV10}
		)

		set(${sources}
			${${sources}}
			${SOURCES_ABMDLV10}
		)

		set(${defs}
			${${defs}}
			CONTAINERS_ABMDLV10_AVAILABLE=1
		)
	else()
		set(${defs}
			${${defs}}
			CONTAINERS_ABMDLV10_AVAILABLE=0
		)
	endif()
endmacro()

macro(install_unit_abmdlv10 forceUse)
	if(CONTAINERS_ABMDLV10 OR ${forceUse})
		install(FILES ${HEADERS_ABMDLV10} DESTINATION ${TARGETNAME_CONTAINERS}/include/${TARGETNAME_CONTAINERS}/ABMDLv10)
	endif()
endmacro()
