function(init_unit_mdlv10 headers sources forceUse)
	set(CONTAINERS_MDLV10 "NO" CACHE BOOL "Includes MDLv10 code in containers library.")

	set(HEADERS_MDLV10
		include/${TARGETNAME_CONTAINERS}/MDLv10/MDLFile.h
		PARENT_SCOPE
	)

	set(SOURCES_MDLV10
		src/MDLv10/MDLFile.c
	)

	if(CONTAINERS_MDLV10 OR ${forceUse})
		set(${headers}
			${${headers}}
			${HEADERS_MDLV10}
			PARENT_SCOPE
		)

		set(${sources}
			${${sources}}
			${SOURCES_MDLV10}
			PARENT_SCOPE
		)
	endif()
endfunction()

macro(install_unit_mdlv10)
	if(CONTAINERS_MDLV10)
		install(FILES ${HEADERS_MDLV10} DESTINATION ${TARGETNAME_CONTAINERS}/include/${TARGETNAME_CONTAINERS}/MDLv10)
	endif()
endmacro()
