set(TARGETNAME_UNIT_TESTS UnitTests)

add_executable(${TARGETNAME_UNIT_TESTS}
	Main.cpp
	Mat4x4.cpp
)

target_include_directories(${TARGETNAME_UNIT_TESTS} PRIVATE .)
target_link_libraries(${TARGETNAME_UNIT_TESTS} Catch2)
target_link_libraries(${TARGETNAME_UNIT_TESTS} ${TARGETNAME_QMATH})

# We allow floating-point comparisons here because they're needed in some cases.
target_compile_options(${TARGETNAME_UNIT_TESTS} PRIVATE "-Wno-float-equal")

install(TARGETS ${TARGETNAME_UNIT_TESTS}
	ARCHIVE DESTINATION tests/${TARGETNAME_UNIT_TESTS}
	LIBRARY DESTINATION tests/${TARGETNAME_UNIT_TESTS}
	RUNTIME DESTINATION tests/${TARGETNAME_UNIT_TESTS}
)
