set(TOOLS_ALL "NO" CACHE BOOL "Build all tools. Useful for validating that these all compile (eg. in CI).")

set(TARGETNAME_TOOLS_COMMON AVIDLib_ToolsCommon)

# Don't include third party libs if tools are not being built,
# otherwise we compile files that we don't need.
if(BUILD_TOOLS)
	add_subdirectory(thirdparty)
endif()

add_subdirectory(common)
add_subdirectory(mdlviewer)
