#include "AVIDLib_Internal_Util/StringBuilder.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Plat/String.h"

static inline ALP_Bool IsValid(const ALU_StringBuilder* builder)
{
	return builder->buffer && builder->size > 0;
}

static inline ALP_Size StrLen(const ALU_StringBuilder* builder)
{
	return builder->cursor - builder->buffer;
}

static inline ALP_Size WritableCharsRemaining(const ALU_StringBuilder* builder)
{
	return builder->size - StrLen(builder) - 1;
}

static inline void SetCursorIndex(ALU_StringBuilder* builder, ALP_Size index)
{
	builder->cursor = builder->buffer + index;
	*builder->cursor = '\0';
}

static inline ALP_Bool VFormatInternal(ALU_StringBuilder* builder, ALP_Char* restrict cursor, const ALP_Char* restrict format, va_list args)
{
	const ALP_Size remainingSpace = builder->size - (cursor - builder->buffer);
	ALP_Int32 result = ALP_VSPrintF(cursor, remainingSpace, format, args);

	ALP_Bool writtenSuccessfully = false;

	if ( result < 1 )
	{
		result = 0;
		builder->cursor = cursor;
	}
	else
	{
		if ( (ALP_Size)result > remainingSpace - 1 )
		{
			result = (ALP_Int32)remainingSpace - 1;
		}
		else
		{
			writtenSuccessfully = true;
		}

		builder->cursor = cursor + result;
	}

	return writtenSuccessfully;
}

ALP_Bool ALU_StringBuilder_IsValid(const ALU_StringBuilder* builder)
{
	return ALU_TSANITY_VALID(builder,
							 IsValid(builder),
							 ALP_FALSE);
}

ALP_Size ALU_StringBuilder_StrLen(const ALU_StringBuilder* builder)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) )
	{
		return StrLen(builder);
	}

	return 0;
}

ALP_Size ALU_StringBuilder_CharsRemaining(const ALU_StringBuilder* builder)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) )
	{
		return WritableCharsRemaining(builder);
	}

	return 0;
}

ALP_Size ALU_StringBuilder_BufferSizeRemaining(const ALU_StringBuilder* builder)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) )
	{
		return WritableCharsRemaining(builder) + 1;
	}

	return 0;
}

const ALP_Char* ALU_StringBuilder_String(const ALU_StringBuilder* builder)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) )
	{
		return builder->buffer;
	}

	return ALP_NULL;
}

ALP_Size ALU_StringBuilder_TotalBufferSize(const ALU_StringBuilder* builder)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) )
	{
		return builder->size;
	}

	return 0;
}

ALP_Char* ALU_StringBuilder_MutableCursor(ALU_StringBuilder* builder)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) )
	{
		return builder->cursor;
	}

	return ALP_NULL;
}

ALP_Char* ALU_StringBuilder_MutableBegin(ALU_StringBuilder* builder)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) )
	{
		return builder->buffer;
	}

	return ALP_NULL;
}

ALP_Char* ALU_StringBuilder_MutableEnd(ALU_StringBuilder* builder)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) )
	{
		return builder->buffer + builder->size;
	}

	return ALP_NULL;
}

void ALU_StringBuilder_UpdateCursor(ALU_StringBuilder* builder)
{
	if ( ALU_SANITY_VALID(builder) )
	{
		if ( IsValid(builder) )
		{
			ALP_Size stringLength = ALP_StrLen(builder->buffer);

			if ( stringLength >= builder->size )
			{
				// Oops! Someone's modified the string and overflowed the buffer!
				// Not much we can do from here other than reset the cursor to the correct size.
				stringLength = builder->size - 1;
			}

			SetCursorIndex(builder, stringLength);
		}
		else
		{
			builder->cursor = ALP_NULL;
		}
	}
}

ALP_Bool ALU_StringBuilder_StrCat(ALU_StringBuilder* builder, const ALP_Char* string)
{
	if ( ALU_SANITY_VALID(builder) && ALU_CHECK_VALID(string) && IsValid(builder) )
	{
		if ( !(*string) )
		{
			return ALP_TRUE;
		}

		while ( *string && builder->cursor < (builder->buffer + builder->size - 1) )
		{
			*(builder->cursor++) = *(string++);
		}

		*builder->cursor = '\0';
		return *string == '\0';
	}

	return ALP_FALSE;
}

ALP_Bool ALU_StringBuilder_StrCpy(ALU_StringBuilder* builder, const ALP_Char* string)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) )
	{
		SetCursorIndex(builder, 0);
		return ALU_StringBuilder_StrCat(builder, string);
	}

	return ALP_FALSE;
}

ALP_Bool ALU_StringBuilder_SPrintF(ALU_StringBuilder* builder, const ALP_Char* format, ...)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) && format )
	{
		va_list args;

		va_start(args, format);
		const ALP_Bool result = ALU_StringBuilder_VSPrintF(builder, format, args);
		va_end(args);

		return result;
	}

	return ALP_FALSE;
}

ALP_Bool ALU_StringBuilder_VSPrintF(ALU_StringBuilder* builder, const ALP_Char* format, va_list args)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) && format )
	{
		return VFormatInternal(builder, builder->buffer, format, args);
	}

	return ALP_FALSE;
}

ALP_Bool ALU_StringBuilder_AppendFormat(ALU_StringBuilder* builder, const ALP_Char* format, ...)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) && format )
	{
		va_list args;

		va_start(args, format);
		const ALP_Bool result = ALU_StringBuilder_AppendVFormat(builder, format, args);
		va_end(args);

		return result;
	}

	return ALP_FALSE;
}

ALP_Bool ALU_StringBuilder_AppendVFormat(ALU_StringBuilder* builder, const ALP_Char* format, va_list args)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) && format )
	{
		return VFormatInternal(builder, builder->cursor, format, args);
	}

	return ALP_FALSE;
}

ALP_Bool ALU_StringBuilder_AppendChar(ALU_StringBuilder* builder, ALP_Char ch)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) && WritableCharsRemaining(builder) > 0 )
	{
		*(builder->cursor++) = ch;
		return ALP_TRUE;
	}

	return ALP_FALSE;
}

ALP_Bool ALU_StringBuilder_AppendRepeatedChar(ALU_StringBuilder* builder, ALP_Char ch, size_t count)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) )
	{
		while ( count > 0 && WritableCharsRemaining(builder) > 0 )
		{
			*(builder->cursor++) = ch;
			--count;
		}

		return count == 0;
	}

	return ALP_FALSE;
}

void ALU_StringBuilder_Clear(ALU_StringBuilder* builder)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) )
	{
		SetCursorIndex(builder, 0);
	}
}

ALP_Bool ALU_StringBuilder_EndsWith(const ALU_StringBuilder* builder, const ALP_Char* suffix)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) && suffix )
	{
		const ALP_Size suffixLength = ALP_StrLen(suffix);

		if ( StrLen(builder) < suffixLength )
		{
			return false;
		}

		return ALP_StrEqual(builder->cursor - suffixLength, suffix);
	}

	return ALP_FALSE;
}

ALP_Bool ALU_StringBuilder_StrCatWithOverwrite(ALU_StringBuilder* builder, const ALP_Char* string)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) && string )
	{
		const ALP_Size stringLength = ALP_StrLen(string);

		if ( stringLength > builder->size - 1 )
		{
			// Too long - erase everything so that we can do a StrCat later.
			SetCursorIndex(builder, 0);
		}
		else if ( stringLength > WritableCharsRemaining(builder) )
		{
			// Fit the string in right at the end of the buffer.
			// We need space to write the string and a terminator.
			SetCursorIndex(builder, builder->size - stringLength - 1);
		}

		return ALU_StringBuilder_StrCat(builder, string);
	}

	return ALP_FALSE;
}

void ALU_StringBuilder_Truncate(ALU_StringBuilder* builder, ALP_Size length)
{
	if ( ALU_SANITY_VALID(builder) && IsValid(builder) && length < builder->size && length < StrLen(builder) )
	{
		SetCursorIndex(builder, length);
	}
}
