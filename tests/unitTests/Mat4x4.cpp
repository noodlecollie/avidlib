#include <limits>
#include <cstdint>
#include <random>
#include "catch2/catch.hpp"
#include "AVIDLib_QMath/Mat4x4.h"

inline void CreateRandomMatrix(ALQM_Mat4x4& matrix,
                               ALQM_Scalar minVal = static_cast<ALQM_Scalar>(std::numeric_limits<int16_t>::min()),
                               ALQM_Scalar maxVal = static_cast<ALQM_Scalar>(std::numeric_limits<int16_t>::min()))
{
	static std::random_device rd;
	static std::mt19937 engine(rd());

	std::uniform_real_distribution<ALQM_Scalar> dist(minVal, maxVal);

	for ( size_t row = 0; row < ALQM_MAT4X4_ROWS; ++row )
	{
		for ( size_t column = 0; column < ALQM_MAT4X4_COLS; ++column )
		{
			matrix.v[row][column] = dist(engine);
		}
	}
}

inline bool ValuesAreEqual(const ALQM_Mat4x4& lhs, const ALQM_Mat4x4& rhs)
{
	for ( size_t row = 0; row < ALQM_MAT4X4_ROWS; ++row )
	{
		for ( size_t column = 0; column < ALQM_MAT4X4_COLS; ++column )
		{
			if ( lhs.v[row][column] != rhs.v[row][column] )
			{
				return false;
			}
		}
	}

	return true;
}

SCENARIO("Multiplying any matrix by the identity should produce the original matrix", "[mat4x4]")
{
	GIVEN("A matrix initialised to random values")
	{
		ALQM_Mat4x4 matrix;
		CreateRandomMatrix(matrix);

		WHEN("The matrix is pre-multiplied by the identity")
		{
			ALQM_Mat4x4 output;
			ALQM_Mat4x4_Concat(&ALQM_Mat4x4_Identity, &matrix, &output);

			THEN("The resulting matrix values should be identical")
			{
				REQUIRE(ValuesAreEqual(matrix, output));
			}
		}

		WHEN("The matrix is post-multiplied by the identity")
		{
			ALQM_Mat4x4 output;
			ALQM_Mat4x4_Concat(&matrix, &ALQM_Mat4x4_Identity, &output);

			THEN("The resulting matrix values should be identical")
			{
				REQUIRE(ValuesAreEqual(matrix, output));
			}
		}
	}
}
