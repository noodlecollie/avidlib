#include "catch2/catch.hpp"

SCENARIO("Placeholder test", "[placeholder]")
{
	GIVEN("A number")
	{
		int number = 5;

		WHEN("The number is incremented")
		{
			++number;

			THEN("The new value should be one greater than the old value")
			{
				REQUIRE(number == 5 + 1);
			}
		}
	}
}
