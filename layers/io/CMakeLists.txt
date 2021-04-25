set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}")

include(win32_export)

# Units in this layer:
include(unit_mdlv10)

create_export_header(${TARGETNAME_IO})

set(PUBLIC_HEADERS_GENERAL
	include/${TARGETNAME_IO}/LibExport.h
	include/${TARGETNAME_IO}/ReadContext.h
	include/${TARGETNAME_IO}/ReaderErrors.h
)

set(SOURCES_GENERAL
	src/ReadContext.c
	src/ReaderErrors.c
)

set(PUBLIC_HEADERS_SELECTED
)

set(SOURCES_SELECTED
)

set(IO_ALL "NO" CACHE BOOL "Includes all different IO readers and writers in IO library. Useful for validating that these all compile (eg. in CI).")
init_unit_mdlv10(PUBLIC_HEADERS_SELECTED SOURCES_SELECTED IO_ALL)

set(numSources 0)
list(LENGTH SOURCES_SELECTED numSources)

if(numSources EQUAL 0)
	message(STATUS "No IO units selected for compilation, skipping IO library.")
	return()
endif()

if(BUILD_SHARED_LIBS)
	add_library(${TARGETNAME_IO} SHARED ${PUBLIC_HEADERS_GENERAL} ${PUBLIC_HEADERS_SELECTED} ${SOURCES_GENERAL} ${SOURCES_SELECTED})
else()
	add_library(${TARGETNAME_IO} STATIC ${PUBLIC_HEADERS_GENERAL} ${PUBLIC_HEADERS_SELECTED} ${SOURCES_GENERAL} ${SOURCES_SELECTED})
endif()

target_link_libraries(${TARGETNAME_IO} PUBLIC ${TARGETNAME_PLAT})
target_link_libraries(${TARGETNAME_IO} PUBLIC ${TARGETNAME_CONTAINERS})
target_link_libraries(${TARGETNAME_IO} PRIVATE ${TARGETNAME_INTERNAL_UTIL})

target_include_directories(${TARGETNAME_IO} PUBLIC
	include
)

target_include_directories(${TARGETNAME_IO} PRIVATE
	src
)

install(TARGETS ${TARGETNAME_IO}
	ARCHIVE DESTINATION ${TARGETNAME_IO}/lib
	LIBRARY DESTINATION ${TARGETNAME_IO}/lib
	RUNTIME DESTINATION ${TARGETNAME_IO}/bin
)

install(FILES ${PUBLIC_HEADERS_GENERAL} DESTINATION ${TARGETNAME_IO}/include/${TARGETNAME_IO})
install_unit_mdlv10()
