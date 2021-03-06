cmake_minimum_required(VERSION 3.12)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to 'Release' as none was specified.")
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)

	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

project(AVIDLib)

# Target names are defined here, so that targets can refer to one another easily.
set(TARGETNAME_THIRDPARTY_IMGUI ThirdParty_ImGui)
set(TARGETNAME_THIRDPARTY_IMGUIFILEDIALOG ThirdParty_ImGuiFileDialog)
set(TARGETNAME_THIRDPARTY_GL3W ThirdParty_gl3w)
set(TARGETNAME_THIRDPARTY_SOKOL ThirdParty_sokol)
set(TARGETNAME_PLAT AVIDLib_Plat)
set(TARGETNAME_INTERNAL_UTIL AVIDLib_Internal_Util)
set(TARGETNAME_QMATH AVIDLib_QMath)
set(TARGETNAME_CONTAINERS AVIDLib_Containers)
set(TARGETNAME_IO AVIDLib_IO)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(BUILD_SHARED_LIBS "YES" CACHE BOOL "If set, builds shared libraries; otherwise, builds static libraries.")

# "Master switches" for forcing all code to be built.
# These are useful for things like CI and automated tests.
set(CONTAINERS_ALL "NO" CACHE BOOL "Includes all different container types in containers library. Useful for validating that these all compile (eg. in CI).")
set(IO_ALL "NO" CACHE BOOL "Includes all different IO readers and writers in IO library. Useful for validating that these all compile (eg. in CI).")
set(BUILD_TESTS "NO" CACHE BOOL "If set, enables building tests.")

if(BUILD_TESTS)
	# If tests are being built, ensure that all code we might want to test is also built.
	message(STATUS "Building all layers as tests are enabled.")
	set(CONTAINERS_ALL "YES")
	set(IO_ALL "YES")
endif()

# Store Git hash in VCS_COMMIT_ID
execute_process(
	COMMAND "${GIT_EXECUTABLE}" describe --always HEAD
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	RESULT_VARIABLE res
	OUTPUT_VARIABLE VCS_COMMIT_ID
	ERROR_QUIET
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Make configure step depend on git index
set_property(GLOBAL APPEND
	PROPERTY CMAKE_CONFIGURE_DEPENDS
	"${CMAKE_SOURCE_DIR}/.git/index"
)

add_compile_definitions("GIT_COMMIT_HASH=\"${VCS_COMMIT_ID}\"")

# Turn up warning levels as high as is feasible, and treat warnings as errors.
# Correct code should be warning-free at all times, no exceptions.
if(MSVC)
	add_compile_options(/W4 /WX)
	add_link_options(/WX)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
	add_link_options(-Wl,--fatal-warnings)

	# Extra things we want to know about:
	add_compile_options(-Wfloat-equal)	# Comparing floats for equality
endif()

add_subdirectory(layers)
add_subdirectory(tests)
