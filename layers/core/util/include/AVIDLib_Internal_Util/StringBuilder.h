#ifndef AVIDLIB_INTERNAL_UTIL_STRINGBUILDER_H
#define AVIDLIB_INTERNAL_UTIL_STRINGBUILDER_H

#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_Plat/Int.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ALU_StringBuilder
{
	ALP_Char* buffer;
	ALP_Size size;
	ALP_Char* cursor;
} ALU_StringBuilder;

ALP_Bool ALU_StringBuilder_IsValid(const ALU_StringBuilder* builder);
ALP_Size ALU_StringBuilder_StrLen(const ALU_StringBuilder* builder);

// Not including terminator:
ALP_Size ALU_StringBuilder_CharsRemaining(const ALU_StringBuilder* builder);

// Including terminator:
ALP_Size ALU_StringBuilder_BufferSizeRemaining(const ALU_StringBuilder* builder);

const ALP_Char* ALU_StringBuilder_String(const ALU_StringBuilder* builder);
ALP_Size ALU_StringBuilder_TotalBufferSize(const ALU_StringBuilder* builder);

// Be careful with this function - writing to the buffer manually will not update the internal state.
// Call ALU_StringBuilder_UpdateCursor() after modification.
// Ensure that this pointer stays within the range [mutableBegin mutableEnd),
// and that any modifications via the cursor keep the string terminated.
ALP_Char* ALU_StringBuilder_MutableCursor(ALU_StringBuilder* builder);
ALP_Char* ALU_StringBuilder_MutableBegin(ALU_StringBuilder* builder);
ALP_Char* ALU_StringBuilder_MutableEnd(ALU_StringBuilder* builder);
void ALU_StringBuilder_UpdateCursor(ALU_StringBuilder* builder);

// All functions that operate on the internal string buffer will ensure that it remains properly terminated.

// The following functions return true if the given data was written without truncation.
// The number of characters written can be computed efficiently by calling ALU_StringBuilder_StrLen()
// before and after the operation.
ALP_Bool ALU_StringBuilder_StrCat(ALU_StringBuilder* builder, const ALP_Char* string);
ALP_Bool ALU_StringBuilder_StrCpy(ALU_StringBuilder* builder, const ALP_Char* string);
ALP_Bool ALU_StringBuilder_SPrintF(ALU_StringBuilder* builder, const ALP_Char* format, ...);
ALP_Bool ALU_StringBuilder_VSPrintF(ALU_StringBuilder* builder, const ALP_Char* format, va_list args);
ALP_Bool ALU_StringBuilder_AppendFormat(ALU_StringBuilder* builder, const ALP_Char* format, ...);
ALP_Bool ALU_StringBuilder_AppendVFormat(ALU_StringBuilder* builder, const ALP_Char* format, va_list args);
ALP_Bool ALU_StringBuilder_AppendChar(ALU_StringBuilder* builder, ALP_Char ch);
ALP_Bool ALU_StringBuilder_AppendRepeatedChar(ALU_StringBuilder* builder, ALP_Char ch, size_t count);

void ALU_StringBuilder_Clear(ALU_StringBuilder* builder);

ALP_Bool ALU_StringBuilder_EndsWith(const ALU_StringBuilder* builder, const ALP_Char* suffix);

// Operates the same way as strcat, except that if there is not enough free space
// on the end of the buffer for the new string, it will overwrite existing characters.
// For example, calling this function with the string "End" on an existing buffer
// comprised of { 'S', 't', 'a', 'r', 't', '\0', '\0' } will result in
// { 'S', 't', 'a', 'E', 'n', 'd', '\0' }.
// This function returns false if the string is too long for the buffer in the first
// place - in this case, it will begin at the start of the buffer and as many
// characters will be written as possible. Otherwise, it will return true.
ALP_Bool ALU_StringBuilder_StrCatWithOverwrite(ALU_StringBuilder* builder, const ALP_Char* string);

// If length is greater than the current length, does nothing.
// If length is less than the current length, truncates the string to be
// the specified number of characters long (not including the terminator).
void ALU_StringBuilder_Truncate(ALU_StringBuilder* builder, ALP_Size length);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_INTERNAL_UTIL_STRINGBUILDER_H
