cmake_minimum_required(VERSION 3.12)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

PROJECT(avidlib)

# Target names are defined here, so that targets can refer to one another easily.
set(TARGETNAME_CLIB AVIDLib_CLib)
set(TARGETNAME_QMATH AVIDLib_QMath)
set(TARGETNAME_CORE AVIDLib_Core)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(BUILD_SHARED_LIBS "YES" CACHE BOOL "If set, builds shared libraries; otherwise, builds static libraries.")

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

# This is defined when building the libraries, and should not be defined when using them.
# This will allow switching between __declspec(import) and __declspec(export) on Windows.
add_compile_definitions(__AVIDLIB_PRODUCER)
add_compile_definitions("GIT_COMMIT_HASH=\"${VCS_COMMIT_ID}\"")

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
	add_compile_definitions(AVIDLIB_DEBUG)
else()
	add_compile_definitions(NDEBUG)
endif()

# Turn up warning levels as high as is feasible, and treat warnings as errors.
# Correct code should be warning-free at all times, no exceptions.
if(MSVC)
	add_compile_options(/W4 /WX)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror -Wfloat-equal)
	add_link_options(--fatal-warnings)
endif()

add_subdirectory(core)
