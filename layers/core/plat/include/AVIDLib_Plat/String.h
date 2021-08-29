/**
 * About: String.h
 * This file provides string-related definitions for the chosen platform.
 */

#ifndef AVIDLIB_PLAT_STRING_H
#define AVIDLIB_PLAT_STRING_H

/**
 * For now, we just use platform headers.
 * If we get to a point in future where we need to swap this out
 * depending on our target platform, we can add ifdefs.
 */
#include <stdio.h>
#include <string.h>

#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_Plat/VariadicArgs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Function: ALP_VSPrintF
 *
 * Replacement for vsprintf, which ensures that the buffer is always terminated.
 *
 * Parameters:
 *
 * buffer     - Output buffer for the string.
 * bufferSize - Number of characters in the output buffer.
 * format     - Format string specifying what gets written to the buffer.
 * arg        - Variadic arguments.
 *
 * Returns:
 *
 * On success, the total number of characters written is returned. This count
 * does not include the additional null-character automatically appended at
 * the end of the string. On failure, a negative number is returned.
 */
static inline ALP_Int32 ALP_VSPrintF(ALP_Char* restrict buffer, ALP_Size bufferSize, const ALP_Char* restrict format, ALP_VAList arg)
{
	const ALP_Int32 result = vsnprintf(buffer, bufferSize, format, arg);

	if ( buffer && bufferSize > 0 )
	{
		if ( (ALP_Size)result >= bufferSize )
		{
			// String was not automatically terminated (boo, CLib).
			buffer[bufferSize - 1] = '\0';
		}
		else if ( result < 1 )
		{
			// Just in case.
			buffer[0] = '\0';
		}
	}

	return result;
}

/**
 * Function: ALP_SPrintF
 *
 * Replacement for sprintf, which ensures that the buffer is always terminated.
 *
 * Parameters:
 *
 * buffer     - Output buffer for the string.
 * bufferSize - Number of characters in the output buffer.
 * format     - Format string specifying what gets written to the buffer.
 * ...        - Variadic arguments.
 *
 * Returns:
 *
 * On success, the total number of characters written is returned. This count
 * does not include the additional null-character automatically appended at
 * the end of the string. On failure, a negative number is returned.
 */
static inline ALP_Int32 ALP_SPrintF(ALP_Char* restrict buffer, ALP_Size bufferSize, const ALP_Char* restrict format, ...)
{
	ALP_VAList args;
	ALP_VA_START(args, format);
	const ALP_Int32 result = ALP_VSPrintF(buffer, bufferSize, format, args);
	ALP_VA_END(args);

	return result;
}

/**
 * Function: ALP_StrCpy
 *
 * Replacement for strcpy, which ensures that the buffer is always terminated.
 *
 * Parameters:
 *
 * dest     - Destination string buffer.
 * destSize - Number of characters in the destination string buffer.
 * src      - Source string to copy into the destination buffer.
 *
 * Returns:
 *
 * dest.
 */
static inline ALP_Char* ALP_StrCpy(ALP_Char* restrict dest, ALP_Size destSize, const ALP_Char* restrict src)
{
	strncpy(dest, src, destSize);

	// No real easy way to determine how many characters were copied,
	// so use a simple safety terminator.

	if ( dest && destSize > 0 )
	{
		dest[destSize - 1] = '\0';
	}

	return dest;
}

/**
 * Function: ALP_StrLen
 *
 * Returns the length of the provided string, not including the null terminator.
 *
 * Parameters:
 *
 * str - String to calculate length of.
 *
 * Returns:
 *
 * Length of the string, not including the null terminator.
 */
static inline ALP_Size ALP_StrLen(const ALP_Char* str)
{
	return strlen(str);
}

/**
 * Function: ALP_StrEqual
 *
 * Returns whether the contents of two strings are exactly equal.
 *
 * Parameters:
 *
 * str1 - First string to compare.
 * str2 - String to compare against str1.
 *
 * Returns:
 *
 * True if all characters of both strings match one another, or false otherwise.
 */
static inline ALP_Bool ALP_StrEqual(const ALP_Char* str1, const ALP_Char* str2)
{
	return strcmp(str1, str2) == 0;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_PLAT_STRING_H
