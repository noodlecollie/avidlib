set(BUILD_TESTS "NO" CACHE BOOL "If set, enables building tests.")

if(BUILD_TESTS)
	add_subdirectory(frameworks)
	add_subdirectory(propertyTests)
	add_subdirectory(unitTests)
endif()
