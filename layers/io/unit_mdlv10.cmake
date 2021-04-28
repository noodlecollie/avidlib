function(init_unit_mdlv10 headers sources forceUse)
	set(IO_MDLV10 "NO" CACHE BOOL "Includes MDLv10 code in IO library.")

	set(HEADERS_MDLV10
		include/${TARGETNAME_IO}/MDLv10/Reader/Reader.h
		PARENT_SCOPE
	)

	set(SOURCES_MDLV10
		src/MDLv10/Reader/Reader.c
		src/MDLv10/Bone.h
		src/MDLv10/Bone.c
		src/MDLv10/Header.h
		src/MDLv10/IODefinitions.h
		src/MDLv10/ValidationHelpers.h
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
		install(FILES ${HEADERS_MDLV10} DESTINATION ${TARGETNAME_IO}/include/${TARGETNAME_IO}/MDLv10)
	endif()
endmacro()
