set(HEADERS_MDLV10
	include/${TARGETNAME_IO}/MDLv10/Reader/Reader.h
)

set(SOURCES_MDLV10
	src/MDLv10/Reader/Reader.c
	src/MDLv10/Bone.h
	src/MDLv10/Bone.c
	src/MDLv10/BoneController.h
	src/MDLv10/BoneController.c
	src/MDLv10/GenericUnitInterface_MDLv10.h
	src/MDLv10/GenericUnitInterface_MDLv10.c
	src/MDLv10/Header.h
	src/MDLv10/IODefinitions.h
	src/MDLv10/ValidationHelpers.h
)

macro(init_unit_mdlv10 headers sources defs forceUse)
	set(IO_MDLV10 "NO" CACHE BOOL "Includes MDLv10 code in IO library.")

	if(IO_MDLV10 OR ${forceUse})
		set(${headers}
			${${headers}}
			${HEADERS_MDLV10}
		)

		set(${sources}
			${${sources}}
			${SOURCES_MDLV10}
		)

		set(${defs}
			${${defs}}
			IO_MDLV10_AVAILABLE=1
		)
	else()
		set(${defs}
			${${defs}}
			IO_MDLV10_AVAILABLE=0
		)
	endif()
endmacro()

macro(install_unit_mdlv10 forceUse)
	if(IO_MDLV10 OR ${forceUse})
		install(FILES ${HEADERS_MDLV10} DESTINATION ${TARGETNAME_IO}/include/${TARGETNAME_IO}/MDLv10)
	endif()
endmacro()
