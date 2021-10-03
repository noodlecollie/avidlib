set(CATCH_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
set(CATCH_INSTALL_EXTRAS OFF CACHE BOOL "" FORCE)

if(NOT MSVC)
	add_compile_options("-Wno-float-equal")
endif()

add_subdirectory(catch2)
