include(win32_export)
create_export_header(${TARGETNAME_QMATH})

set(PUBLIC_HEADERS_GENERAL
	include/${TARGETNAME_QMATH}/Constants.h
	include/${TARGETNAME_QMATH}/Conversions.h
	include/${TARGETNAME_QMATH}/EulerAngle.h
	include/${TARGETNAME_QMATH}/LibExport.h
	include/${TARGETNAME_QMATH}/Mat3x4.h
	include/${TARGETNAME_QMATH}/Mat4x4.h
	include/${TARGETNAME_QMATH}/Math.h
	include/${TARGETNAME_QMATH}/Quat.h
	include/${TARGETNAME_QMATH}/Types.h
	include/${TARGETNAME_QMATH}/Vec3.h
	include/${TARGETNAME_QMATH}/Vec4.h
)

set(PUBLIC_HEADERS_ALL
	${PUBLIC_HEADERS_GENERAL}
)

set(SOURCES_ALL
	src/Conversions.c
	src/EulerAngle.c
	src/Mat3x4.c
	src/Mat4x4.c
	src/Math.c
	src/Quat.c
	src/Vec3.c
	src/Vec4.c
)

if(BUILD_SHARED_LIBS)
	add_library(${TARGETNAME_QMATH} SHARED ${PUBLIC_HEADERS_ALL} ${SOURCES_ALL})
else()
	add_library(${TARGETNAME_QMATH} STATIC ${PUBLIC_HEADERS_ALL} ${SOURCES_ALL})
endif()

add_export_defs(${TARGETNAME_QMATH})

target_link_libraries(${TARGETNAME_QMATH} PUBLIC ${TARGETNAME_PLAT})
target_link_libraries(${TARGETNAME_QMATH} PRIVATE ${TARGETNAME_INTERNAL_UTIL})

target_include_directories(${TARGETNAME_QMATH} PUBLIC
	include
)

target_include_directories(${TARGETNAME_QMATH} PRIVATE
	src
)

install(TARGETS ${TARGETNAME_QMATH}
	ARCHIVE DESTINATION ${TARGETNAME_QMATH}/lib
	LIBRARY DESTINATION ${TARGETNAME_QMATH}/lib
	RUNTIME DESTINATION ${TARGETNAME_QMATH}/bin
)

install(FILES ${PUBLIC_HEADERS_GENERAL} DESTINATION ${TARGETNAME_QMATH}/include/${TARGETNAME_QMATH})
