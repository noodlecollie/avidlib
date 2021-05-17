# Override GLFW's defaults, since we only want to use it
# as an internal static library.
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

if(NOT MSVC)
	add_compile_options(
		"-Wno-pedantic"
		"-Wno-float-equal"
		"-Wno-missing-field-initializers"
		"-Wno-sign-compare"
		"-Wno-unused-parameter"
	)
endif()

# This is only ever used internally, so is built statically:
set(OLD_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(glfw)
set(BUILD_SHARED_LIBS ${OLD_BUILD_SHARED_LIBS})
