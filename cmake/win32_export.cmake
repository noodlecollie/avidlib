function(create_export_header moduleName)
	set(moduleNameUpper "")

	set(sharedLibStatement
		"// Platform is not Windows, so no __declspec is required."
	)

	string(TOUPPER ${moduleName} moduleNameUpper)

	if(WIN32)
		if(BUILD_SHARED_LIBS)
			# Add a preprocessor definition to say that we're building shared libraries.
			# This has to go in a physical header file, because it needs to be packaged
			# with the rest of the files so that users of the library can use it.
			set(sharedLibStatement
				"// Libraries built in shared configuration. __declspec is required on Windows.\n#define AVIDLIB_IS_SHARED_BUILD"
			)
		else()
			# No need to add any definition in static lib mode.
			set(sharedLibStatement
				"// Libraries built in static configuration. No __declspec is required on Windows."
			)
		endif()
	endif()

	file(WRITE "include/${moduleName}/LibExport.h"
		"#ifndef ${moduleNameUpper}_LIBEXPORT_H\n"
		"#define ${moduleNameUpper}_LIBEXPORT_H\n"
		"\n"
		"${sharedLibStatement}\n"
		"\n"
		"#if defined(AVIDLIB_IS_SHARED_BUILD) && defined(_MSC_VER)\n"
		"\n"
		"#if defined(__AVIDLIB_PRODUCER)\n"
		"// This build is producing a library for another application to use.\n"
		"// Mark symbols as being exported.\n"
		"#define API_${moduleNameUpper} __declspec(dllexport)\n"
		"#else // defined(__AVIDLIB_PRODUCER)\n"
		"// This library is being used by some application.\n"
		"// Mark symbols as being imported.\n"
		"#define API_${moduleNameUpper} __declspec(dllimport)\n"
		"#endif // defined(__AVIDLIB_PRODUCER)\n"
		"\n"
		"#else // defined(AVIDLIB_IS_SHARED_BUILD) && defined(_MSC_VER)\n"
		"\n"
		"// We're not using shared libraries, or we're not building under Windows.\n"
		"// No need to use __declspec, so define this to nothing.\n"
		"#define API_${moduleNameUpper}\n"
		"\n"
		"#endif // defined(AVIDLIB_IS_SHARED_BUILD) && defined(_MSC_VER)\n"
		"#endif // ${moduleNameUpper}_LIBEXPORT_H\n"
	)
endfunction()
