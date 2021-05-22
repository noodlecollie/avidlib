# Set up desired BGFX options before we process the project file.
set(BGFX_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BGFX_INSTALL OFF CACHE BOOL "" FORCE)

# This is only ever used internally, so is built statically:
set(BGFX_LIBRARY_TYPE "STATIC" CACHE STRING "" FORCE)

if(NOT MSVC)
	# I can't seem to find a way to use decent CMake functions to add to
	# C++ flags and not C flags. These go to both compilers:
	add_compile_options(
		"-Wno-float-equal"
		"-Wno-pedantic"
		"-Wno-implicit-fallthrough"
		"-Wno-shift-negative-value"
	)

	# And these go to C++ only (they must be in one string to avoid CMake inserting semicolons):
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-class-memaccess -Wno-deprecated-copy")
endif()

add_subdirectory(bgfx.cmake)

# This is an adaptation of the bgfx example ImGUI integration,
# cleaned up and isolated a little so that it works in this repo.
add_subdirectory(bgfx_imgui)
