#include "AVIDLib_QMath/Mat3x4.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Plat/Check.h"
#include "AVIDLib_Plat/Util.h"
#include "AVIDLib_QMath/Math.h"

const ALQM_Mat3x4 ALQM_Mat3x4_Identity =
{
	{
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 }
	}
};

ALQM_Scalar* ALQM_Mat3x4_Data(ALQM_Mat3x4* m)
{
	return ALP_TSANITY_VALID(m, (ALQM_Scalar*)m->v, ALP_NULL);
}

const ALQM_Scalar* ALQM_Mat3x4_CData(const ALQM_Mat3x4* m)
{
	return ALP_TSANITY_VALID(m, (const ALQM_Scalar*)m->v, ALP_NULL);
}

ALQM_Scalar* ALQM_Mat3x4_Column(ALQM_Mat3x4* m, ALP_Size column)
{
	return ALP_TSANITY_VALID(m && column < ALQM_MAT3X4_COLS, (ALQM_Scalar*)&m->v[column], ALP_NULL);
}

const ALQM_Scalar* ALQM_Mat3x4_CColumn(const ALQM_Mat3x4* m, ALP_Size column)
{
	return ALP_TSANITY_VALID(m && column < ALQM_MAT3X4_COLS, (const ALQM_Scalar*)&m->v[column], ALP_NULL);
}

ALQM_Mat3x4* ALQM_Mat3x4_SetIdentity(ALQM_Mat3x4* mOut)
{
	if ( ALP_SANITY_VALID(mOut) )
	{
		mOut->v[0][0] = 1;
		mOut->v[0][1] = 0;
		mOut->v[0][2] = 0;
		mOut->v[0][3] = 0;

		mOut->v[1][0] = 0;
		mOut->v[1][1] = 1;
		mOut->v[1][2] = 0;
		mOut->v[1][3] = 0;

		mOut->v[2][0] = 0;
		mOut->v[2][1] = 0;
		mOut->v[2][2] = 1;
		mOut->v[2][3] = 0;
	}

	return mOut;
}

ALQM_Mat3x4* ALQM_Mat3x4_Zero(ALQM_Mat3x4* mOut)
{
	if ( ALP_SANITY_VALID(mOut) )
	{
		ALP_MemSet(mOut->v, 0, sizeof(mOut->v));
	}

	return mOut;
}

ALQM_Mat3x4* ALQM_Mat3x4_Copy(const ALQM_Mat3x4* mIn, ALQM_Mat3x4* mOut)
{
	if ( ALP_SANITY_VALID(mIn && mOut) && mIn != mOut )
	{
		ALP_MemCpy(mOut->v, mIn->v, sizeof(mOut->v));
	}

	return mOut;
}

ALQM_Mat3x4* ALQM_Mat3x4_Set(const ALQM_Scalar* values, ALP_Size count, ALQM_Mat3x4* mOut)
{
	if ( ALP_SANITY_VALID(values && count >= ALQM_MAT3X4_CELLS && mOut) )
	{
		mOut->v[0][0] = values[0];
		mOut->v[0][1] = values[1];
		mOut->v[0][2] = values[2];
		mOut->v[0][3] = values[3];

		mOut->v[1][0] = values[4];
		mOut->v[1][1] = values[5];
		mOut->v[1][2] = values[6];
		mOut->v[1][3] = values[7];

		mOut->v[2][0] = values[8];
		mOut->v[2][1] = values[9];
		mOut->v[2][2] = values[10];
		mOut->v[2][3] = values[11];
	}

	return mOut;
}

ALQM_Mat3x4* ALQM_Mat3x4_Concat(const ALQM_Mat3x4* m0, const ALQM_Mat3x4* m1, ALQM_Mat3x4* mOut)
{
	if ( ALP_SANITY_VALID(m0 && m1 && mOut) )
	{
		mOut->v[0][0] = (m0->v[0][0] * m1->v[0][0]) + (m0->v[0][1] * m1->v[1][0]) + (m0->v[0][2] * m1->v[2][0]);
		mOut->v[0][1] = (m0->v[0][0] * m1->v[0][1]) + (m0->v[0][1] * m1->v[1][1]) + (m0->v[0][2] * m1->v[2][1]);
		mOut->v[0][2] = (m0->v[0][0] * m1->v[0][2]) + (m0->v[0][1] * m1->v[1][2]) + (m0->v[0][2] * m1->v[2][2]);
		mOut->v[0][3] = (m0->v[0][0] * m1->v[0][3]) + (m0->v[0][1] * m1->v[1][3]) + (m0->v[0][2] * m1->v[2][3]) + m0->v[0][3];

		mOut->v[1][0] = (m0->v[1][0] * m1->v[0][0]) + (m0->v[1][1] * m1->v[1][0]) + (m0->v[1][2] * m1->v[2][0]);
		mOut->v[1][1] = (m0->v[1][0] * m1->v[0][1]) + (m0->v[1][1] * m1->v[1][1]) + (m0->v[1][2] * m1->v[2][1]);
		mOut->v[1][2] = (m0->v[1][0] * m1->v[0][2]) + (m0->v[1][1] * m1->v[1][2]) + (m0->v[1][2] * m1->v[2][2]);
		mOut->v[1][3] = (m0->v[1][0] * m1->v[0][3]) + (m0->v[1][1] * m1->v[1][3]) + (m0->v[1][2] * m1->v[2][3]) + m0->v[1][3];

		mOut->v[2][0] = (m0->v[2][0] * m1->v[0][0]) + (m0->v[2][1] * m1->v[1][0]) + (m0->v[2][2] * m1->v[2][0]);
		mOut->v[2][1] = (m0->v[2][0] * m1->v[0][1]) + (m0->v[2][1] * m1->v[1][1]) + (m0->v[2][2] * m1->v[2][1]);
		mOut->v[2][2] = (m0->v[2][0] * m1->v[0][2]) + (m0->v[2][1] * m1->v[1][2]) + (m0->v[2][2] * m1->v[2][2]);
		mOut->v[2][3] = (m0->v[2][0] * m1->v[0][3]) + (m0->v[2][1] * m1->v[1][3]) + (m0->v[2][2] * m1->v[2][3]) + m0->v[2][3];
	}

	return mOut;
}

ALQM_Mat3x4* ALQM_Mat3x4_ConcatRot(const ALQM_Mat3x4* m0, const ALQM_Mat3x4* m1, ALQM_Mat3x4* mOut)
{
	if ( ALP_SANITY_VALID(m0 && m1 && mOut) )
	{
		mOut->v[0][0] = (m0->v[0][0] * m1->v[0][0]) + (m0->v[0][1] * m1->v[1][0]) + (m0->v[0][2] * m1->v[2][0]);
		mOut->v[0][1] = (m0->v[0][0] * m1->v[0][1]) + (m0->v[0][1] * m1->v[1][1]) + (m0->v[0][2] * m1->v[2][1]);
		mOut->v[0][2] = (m0->v[0][0] * m1->v[0][2]) + (m0->v[0][1] * m1->v[1][2]) + (m0->v[0][2] * m1->v[2][2]);
		mOut->v[0][3] = (m0->v[0][0] * m1->v[0][3]) + (m0->v[0][1] * m1->v[1][3]) + (m0->v[0][2] * m1->v[2][3]);

		mOut->v[1][0] = (m0->v[1][0] * m1->v[0][0]) + (m0->v[1][1] * m1->v[1][0]) + (m0->v[1][2] * m1->v[2][0]);
		mOut->v[1][1] = (m0->v[1][0] * m1->v[0][1]) + (m0->v[1][1] * m1->v[1][1]) + (m0->v[1][2] * m1->v[2][1]);
		mOut->v[1][2] = (m0->v[1][0] * m1->v[0][2]) + (m0->v[1][1] * m1->v[1][2]) + (m0->v[1][2] * m1->v[2][2]);
		mOut->v[1][3] = (m0->v[1][0] * m1->v[0][3]) + (m0->v[1][1] * m1->v[1][3]) + (m0->v[1][2] * m1->v[2][3]);

		mOut->v[2][0] = (m0->v[2][0] * m1->v[0][0]) + (m0->v[2][1] * m1->v[1][0]) + (m0->v[2][2] * m1->v[2][0]);
		mOut->v[2][1] = (m0->v[2][0] * m1->v[0][1]) + (m0->v[2][1] * m1->v[1][1]) + (m0->v[2][2] * m1->v[2][1]);
		mOut->v[2][2] = (m0->v[2][0] * m1->v[0][2]) + (m0->v[2][1] * m1->v[1][2]) + (m0->v[2][2] * m1->v[2][2]);
		mOut->v[2][3] = (m0->v[2][0] * m1->v[0][3]) + (m0->v[2][1] * m1->v[1][3]) + (m0->v[2][2] * m1->v[2][3]);
	}

	return mOut;
}

ALP_Bool ALQM_Mat3x4_ExactlyEqual(const ALQM_Mat3x4* mLHS, const ALQM_Mat3x4* mRHS)
{
	if ( ALP_SANITY_VALID(mLHS && mRHS) )
	{
		const ALQM_Scalar* lhs = (const ALQM_Scalar*)mLHS->v;
		const ALQM_Scalar* rhs = (const ALQM_Scalar*)mRHS->v;

		for ( ALP_Size index = 0; index < ALQM_MAT3X4_CELLS; ++index )
		{
			if ( !ALQM_ScalarsExactlyEqual(*(lhs++), *(rhs++)) )
			{
				return ALP_FALSE;
			}
		}

		return ALP_TRUE;
	}

	return ALP_FALSE;
}

ALP_Bool ALQM_Mat3x4_ApproximatelyEqual(const ALQM_Mat3x4* mLHS, const ALQM_Mat3x4* mRHS)
{
	if ( ALP_SANITY_VALID(mLHS && mRHS) )
	{
		const ALQM_Scalar* lhs = (const ALQM_Scalar*)mLHS->v;
		const ALQM_Scalar* rhs = (const ALQM_Scalar*)mRHS->v;

		for ( ALP_Size index = 0; index < ALQM_MAT3X4_CELLS; ++index )
		{
			if ( !ALQM_ScalarsApproximatelyEqual(*(lhs++), *(rhs++)) )
			{
				return ALP_FALSE;
			}
		}

		return ALP_TRUE;
	}

	return ALP_FALSE;
}

ALP_Bool ALQM_Mat3x4_ExactlyZero(const ALQM_Mat3x4* m)
{
	if ( ALP_SANITY_VALID(m) )
	{
		const ALQM_Scalar* data = (const ALQM_Scalar*)m->v;

		for ( ALP_Size index = 0; index < ALQM_MAT3X4_CELLS; ++index )
		{
			if ( !ALQM_ScalarExactlyZero(*(data++)) )
			{
				return ALP_FALSE;
			}
		}

		return ALP_TRUE;
	}

	return ALP_FALSE;
}

ALP_Bool ALQM_Mat3x4_ApproximatelyZero(const ALQM_Mat3x4* m)
{
	if ( ALP_SANITY_VALID(m) )
	{
		const ALQM_Scalar* data = (const ALQM_Scalar*)m->v;

		for ( ALP_Size index = 0; index < ALQM_MAT3X4_CELLS; ++index )
		{
			if ( !ALQM_ScalarApproximatelyZero(*(data++)) )
			{
				return ALP_FALSE;
			}
		}

		return ALP_TRUE;
	}

	return ALP_FALSE;
}

ALP_Bool ALQM_Mat3x4_ExactlyIdentity(const ALQM_Mat3x4* m)
{
	if ( ALP_SANITY_VALID(m) )
	{
		return ALQM_Mat3x4_ExactlyEqual(m, &ALQM_Mat3x4_Identity);
	}

	return ALP_FALSE;
}

ALP_Bool ALQM_Mat3x4_ApproximatelyIdentity(const ALQM_Mat3x4* m)
{
	if ( ALP_SANITY_VALID(m) )
	{
		return ALQM_Mat3x4_ApproximatelyEqual(m, &ALQM_Mat3x4_Identity);
	}

	return ALP_FALSE;
}
