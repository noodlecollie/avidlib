add_library(${TARGETNAME_THIRDPARTY_SOKOL} INTERFACE)
target_include_directories(${TARGETNAME_THIRDPARTY_SOKOL} INTERFACE
	.
)

if(NOT MSVC)
	target_compile_options(${TARGETNAME_THIRDPARTY_SOKOL} INTERFACE
		"-Wno-float-equal"
	)
endif()
