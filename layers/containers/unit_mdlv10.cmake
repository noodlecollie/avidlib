function(init_unit_mdlv10 headers sources forceUse)
	set(CONTAINERS_MDLV10 "NO" CACHE BOOL "Includes MDLv10 code in containers library.")

	set(HEADERS_MDLV10
		include/${TARGETNAME_CONTAINERS}/MDLv10/Bone.h
		include/${TARGETNAME_CONTAINERS}/MDLv10/BoneController.h
		include/${TARGETNAME_CONTAINERS}/MDLv10/ContainerDefinitions.h
		include/${TARGETNAME_CONTAINERS}/MDLv10/Model.h
		PARENT_SCOPE
	)

	set(SOURCES_MDLV10
		src/MDLv10/Internal/Bone_Internal.h
		src/MDLv10/Internal/Bone_Internal.c
		src/MDLv10/Internal/BoneController_Internal.h
		src/MDLv10/Internal/BoneController_Internal.c
		src/MDLv10/Bone.c
		src/MDLv10/BoneController.c
		src/MDLv10/Model.c
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
