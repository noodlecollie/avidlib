set(BUILD_TOOLS "NO" CACHE BOOL "If set, allows building tools. If not set, no tools or third party CMakeLists.txt files will be used. Note that individual tools must still be enabled for compilation using the TOOL_* options.")

add_subdirectory(core)
add_subdirectory(containers)
add_subdirectory(io)
add_subdirectory(tools)
