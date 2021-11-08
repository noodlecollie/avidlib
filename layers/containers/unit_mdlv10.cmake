set(HEADERS_MDLV10
	include/${TARGETNAME_CONTAINERS}/MDLv10/Bone.h
	include/${TARGETNAME_CONTAINERS}/MDLv10/BoneController.h
	include/${TARGETNAME_CONTAINERS}/MDLv10/BoneWeight.h
	include/${TARGETNAME_CONTAINERS}/MDLv10/BoneWeightedVec3.h
	include/${TARGETNAME_CONTAINERS}/MDLv10/ContainerDefinitions.h
	include/${TARGETNAME_CONTAINERS}/MDLv10/Model.h
	include/${TARGETNAME_CONTAINERS}/MDLv10/Submodel.h
)

set(SOURCES_MDLV10
	src/MDLv10/Helpers/BodyPart_Helpers.h
	src/MDLv10/Helpers/BodyPart_Helpers.c
	src/MDLv10/Helpers/Bone_Helpers.h
	src/MDLv10/Helpers/Bone_Helpers.c
	src/MDLv10/Helpers/BoneController_Helpers.h
	src/MDLv10/Helpers/BoneController_Helpers.c
	src/MDLv10/Helpers/BoneWeightedVec3_Helpers.h
	src/MDLv10/Helpers/BoneWeightedVec3_Helpers.c
	src/MDLv10/Helpers/Submodel_Helpers.h
	src/MDLv10/Helpers/Submodel_Helpers.c
	src/MDLv10/BodyPart.c
	src/MDLv10/Bone.c
	src/MDLv10/BoneController.c
	src/MDLv10/BoneWeight.c
	src/MDLv10/BoneWeightedVec3.c
	src/MDLv10/Model.c
	src/MDLv10/Submodel.c
)

macro(init_unit_mdlv10 headers sources defs forceUse)
	set(CONTAINERS_MDLV10 "NO" CACHE BOOL "Includes MDLv10 code in containers library.")

	if(CONTAINERS_MDLV10 OR ${forceUse})
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
			CONTAINERS_MDLV10_AVAILABLE=1
		)
	else()
		set(${defs}
			${${defs}}
			CONTAINERS_MDLV10_AVAILABLE=0
		)
	endif()
endmacro()

macro(install_unit_mdlv10 forceUse)
	if(CONTAINERS_MDLV10 OR ${forceUse})
		install(FILES ${HEADERS_MDLV10} DESTINATION ${TARGETNAME_CONTAINERS}/include/${TARGETNAME_CONTAINERS}/MDLv10)
	endif()
endmacro()
