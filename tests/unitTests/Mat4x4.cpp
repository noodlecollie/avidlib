#include "catch2/catch.hpp"
#include "AVIDLib_QMath/Mat4x4.h"

inline void RequireValuesAreEqual(const ALQM_Mat4x4& lhs, const ALQM_Mat4x4& rhs)
{
	REQUIRE(lhs.v[0][0] == rhs.v[0][0]);
	REQUIRE(lhs.v[0][1] == rhs.v[0][1]);
	REQUIRE(lhs.v[0][2] == rhs.v[0][2]);
	REQUIRE(lhs.v[0][3] == rhs.v[0][3]);

	REQUIRE(lhs.v[1][0] == rhs.v[1][0]);
	REQUIRE(lhs.v[1][1] == rhs.v[1][1]);
	REQUIRE(lhs.v[1][2] == rhs.v[1][2]);
	REQUIRE(lhs.v[1][3] == rhs.v[1][3]);

	REQUIRE(lhs.v[2][0] == rhs.v[2][0]);
	REQUIRE(lhs.v[2][1] == rhs.v[2][1]);
	REQUIRE(lhs.v[2][2] == rhs.v[2][2]);
	REQUIRE(lhs.v[2][3] == rhs.v[2][3]);

	REQUIRE(lhs.v[3][0] == rhs.v[3][0]);
	REQUIRE(lhs.v[3][1] == rhs.v[3][1]);
	REQUIRE(lhs.v[3][2] == rhs.v[3][2]);
	REQUIRE(lhs.v[3][3] == rhs.v[3][3]);
}

// TODO: More tests
SCENARIO("Multiplying a matrix by the identity should produce the original matrix", "[mat4x4]")
{
	GIVEN("A matrix initialised to arbitrary values")
	{
		ALQM_Scalar values[16] =
		{
			1.0f,     2.0f,      3.0f,          4.0f,
			1.5f,     46334.0f,  -2387.344f,    325.34f,
			0.0f,     1.0f,      -387873483.0f, -345.9789987f,
			123.456f, -987.654f, 23.0f,         457.4f
		};

		ALQM_Mat4x4 matrix;
		ALQM_Mat4x4_SetValuesArray(values, 16, &matrix);

		WHEN("The matrix is pre-multiplied by the identity")
		{
			ALQM_Mat4x4 output;
			ALQM_Mat4x4_Concat(&ALQM_Mat4x4_Identity, &matrix, &output);

			THEN("The resulting matrix values should be identical")
			{
				RequireValuesAreEqual(matrix, output);
			}
		}

		WHEN("The matrix is post-multiplied by the identity")
		{
			ALQM_Mat4x4 output;
			ALQM_Mat4x4_Concat(&matrix, &ALQM_Mat4x4_Identity, &output);

			THEN("The resulting matrix values should be identical")
			{
				RequireValuesAreEqual(matrix, output);
			}
		}
	}
}
