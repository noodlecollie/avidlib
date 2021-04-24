#include "AVIDLib_Internal_Util/Check.h"

int ALU_AssertWithFeedback(int expression, const char* expressionStr, const char* file, int line)
{
	if ( !expression )
	{
		fprintf(stderr, "Assertion failed @ %s:%d \"%s\"\n", file, line, expressionStr);
		assert(0 && "Assertion failed - see stderr for information.");
	}

	return expression;
}

void ALU_AssertMallocSucceeded(const void* ptr, ALP_Size size, const char* file, int line)
{
	if ( !ptr )
	{
		fprintf(stderr, "Malloc failed: %lu bytes @ %s:%d", (unsigned long)size, file, line);
		assert(0 && "A call to malloc failed - see stderr for information.");
	}
}
