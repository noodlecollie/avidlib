#include "AVIDLib_QMath/Mat3x4.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_Plat/Memory.h"
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
	return ALU_TSANITY_VALID(m, (ALQM_Scalar*)m->v, ALP_NULL);
}

const ALQM_Scalar* ALQM_Mat3x4_CData(const ALQM_Mat3x4* m)
{
	return ALU_TSANITY_VALID(m, (const ALQM_Scalar*)m->v, ALP_NULL);
}

ALQM_Scalar* ALQM_Mat3x4_Row(ALQM_Mat3x4* m, ALP_Size row)
{
	return ALU_TSANITY_VALID(m && row < ALQM_MAT3X4_ROWS, (ALQM_Scalar*)&m->v[row], ALP_NULL);
}

const ALQM_Scalar* ALQM_Mat3x4_CRow(const ALQM_Mat3x4* m, ALP_Size row)
{
	return ALU_TSANITY_VALID(m && row < ALQM_MAT3X4_ROWS, (const ALQM_Scalar*)&m->v[row], ALP_NULL);
}

ALQM_Mat3x4* ALQM_Mat3x4_SetIdentity(ALQM_Mat3x4* mOut)
{
	if ( ALU_SANITY_VALID(mOut) )
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
	if ( ALU_SANITY_VALID(mOut) )
	{
		ALP_MemSet(mOut->v, 0, sizeof(mOut->v));
	}

	return mOut;
}

ALQM_Mat3x4* ALQM_Mat3x4_Copy(const ALQM_Mat3x4* mIn, ALQM_Mat3x4* mOut)
{
	if ( ALU_SANITY_VALID(mIn && mOut) && mIn != mOut )
	{
		ALP_MemCpy(mOut->v, mIn->v, sizeof(mOut->v));
	}

	return mOut;
}

ALQM_Mat3x4* ALQM_Mat3x4_SetValuesArray(const ALQM_Scalar* values, ALP_Size count, ALQM_Mat3x4* mOut)
{
	if ( ALU_SANITY_VALID(values && count >= ALQM_MAT3X4_CELLS && mOut) )
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

ALQM_Mat3x4* ALQM_Mat3x4_Concat(const ALQM_Mat3x4* mLHS, const ALQM_Mat3x4* mRHS, ALQM_Mat3x4* mOut)
{
	if ( ALU_SANITY_VALID(mLHS && mRHS && mOut) )
	{
		mOut->v[0][0] = (mLHS->v[0][0] * mRHS->v[0][0]) + (mLHS->v[0][1] * mRHS->v[1][0]) + (mLHS->v[0][2] * mRHS->v[2][0]);
		mOut->v[0][1] = (mLHS->v[0][0] * mRHS->v[0][1]) + (mLHS->v[0][1] * mRHS->v[1][1]) + (mLHS->v[0][2] * mRHS->v[2][1]);
		mOut->v[0][2] = (mLHS->v[0][0] * mRHS->v[0][2]) + (mLHS->v[0][1] * mRHS->v[1][2]) + (mLHS->v[0][2] * mRHS->v[2][2]);
		mOut->v[0][3] = (mLHS->v[0][0] * mRHS->v[0][3]) + (mLHS->v[0][1] * mRHS->v[1][3]) + (mLHS->v[0][2] * mRHS->v[2][3]) + mLHS->v[0][3];

		mOut->v[1][0] = (mLHS->v[1][0] * mRHS->v[0][0]) + (mLHS->v[1][1] * mRHS->v[1][0]) + (mLHS->v[1][2] * mRHS->v[2][0]);
		mOut->v[1][1] = (mLHS->v[1][0] * mRHS->v[0][1]) + (mLHS->v[1][1] * mRHS->v[1][1]) + (mLHS->v[1][2] * mRHS->v[2][1]);
		mOut->v[1][2] = (mLHS->v[1][0] * mRHS->v[0][2]) + (mLHS->v[1][1] * mRHS->v[1][2]) + (mLHS->v[1][2] * mRHS->v[2][2]);
		mOut->v[1][3] = (mLHS->v[1][0] * mRHS->v[0][3]) + (mLHS->v[1][1] * mRHS->v[1][3]) + (mLHS->v[1][2] * mRHS->v[2][3]) + mLHS->v[1][3];

		mOut->v[2][0] = (mLHS->v[2][0] * mRHS->v[0][0]) + (mLHS->v[2][1] * mRHS->v[1][0]) + (mLHS->v[2][2] * mRHS->v[2][0]);
		mOut->v[2][1] = (mLHS->v[2][0] * mRHS->v[0][1]) + (mLHS->v[2][1] * mRHS->v[1][1]) + (mLHS->v[2][2] * mRHS->v[2][1]);
		mOut->v[2][2] = (mLHS->v[2][0] * mRHS->v[0][2]) + (mLHS->v[2][1] * mRHS->v[1][2]) + (mLHS->v[2][2] * mRHS->v[2][2]);
		mOut->v[2][3] = (mLHS->v[2][0] * mRHS->v[0][3]) + (mLHS->v[2][1] * mRHS->v[1][3]) + (mLHS->v[2][2] * mRHS->v[2][3]) + mLHS->v[2][3];
	}

	return mOut;
}

ALQM_Mat3x4* ALQM_Mat3x4_TransposeRot(const ALQM_Mat3x4* mIn, ALQM_Mat3x4* mOut)
{
	if ( ALU_SANITY_VALID(mIn && mOut) )
	{
		mOut->v[0][0] = mIn->v[0][0];
		mOut->v[0][1] = mIn->v[1][0];
		mOut->v[0][2] = mIn->v[2][0];

		mOut->v[1][0] = mIn->v[0][1];
		mOut->v[1][1] = mIn->v[1][1];
		mOut->v[1][2] = mIn->v[2][1];

		mOut->v[2][0] = mIn->v[0][2];
		mOut->v[2][1] = mIn->v[1][2];
		mOut->v[2][2] = mIn->v[2][2];

		mOut->v[0][3] = mIn->v[0][3];
		mOut->v[1][3] = mIn->v[1][3];
		mOut->v[2][3] = mIn->v[2][3];
	}

	return mOut;
}

// Comments and implementation here are adapted from Xash3D.
ALQM_Mat3x4* ALQM_Mat3x4_InvertSimple(const ALQM_Mat3x4* mIn, ALQM_Mat3x4* mOut)
{
	if ( ALU_SANITY_VALID(mIn && mOut) )
	{
		// We only support uniform scaling, so assume the first row's scaling
		// is representative of all scaling.
		// Note the lack of sqrt here, because we're trying to undo the scaling,
		// this means multiplying by the inverse scale twice - squaring it, which
		// makes the sqrt a waste of time.

		const ALQM_Scalar scale = 1 / ((mIn->v[0][0] * mIn->v[0][0]) + (mIn->v[0][1] * mIn->v[0][1]) + (mIn->v[0][2] * mIn->v[0][2]));

		// Invert the rotation by transposing and multiplying by the squared
		// reciprocal of the input matrix scale as described above.
		mOut->v[0][0] = mIn->v[0][0] * scale;
		mOut->v[0][1] = mIn->v[1][0] * scale;
		mOut->v[0][2] = mIn->v[2][0] * scale;
		mOut->v[1][0] = mIn->v[0][1] * scale;
		mOut->v[1][1] = mIn->v[1][1] * scale;
		mOut->v[1][2] = mIn->v[2][1] * scale;
		mOut->v[2][0] = mIn->v[0][2] * scale;
		mOut->v[2][1] = mIn->v[1][2] * scale;
		mOut->v[2][2] = mIn->v[2][2] * scale;

		// Invert the translation.
		mOut->v[0][3] = -((mIn->v[0][3] * mOut->v[0][0]) + (mIn->v[1][3] * mOut->v[0][1]) + (mIn->v[2][3] * mOut->v[0][2]));
		mOut->v[1][3] = -((mIn->v[0][3] * mOut->v[1][0]) + (mIn->v[1][3] * mOut->v[1][1]) + (mIn->v[2][3] * mOut->v[1][2]));
		mOut->v[2][3] = -((mIn->v[0][3] * mOut->v[2][0]) + (mIn->v[1][3] * mOut->v[2][1]) + (mIn->v[2][3] * mOut->v[2][2]));
	}

	return mOut;
}

ALQM_Mat3x4* ALQM_Mat3x4_SetTranslation(const ALQM_Mat3x4* mIn, const ALQM_Vec3* vTranslation, ALQM_Mat3x4* mOut)
{
	if ( ALU_SANITY_VALID(mIn && vTranslation && mOut) )
	{
		mOut->v[0][3] = vTranslation->v[ALQM_VECX];
		mOut->v[1][3] = vTranslation->v[ALQM_VECY];
		mOut->v[2][3] = vTranslation->v[ALQM_VECZ];
	}

	return mOut;
}

ALQM_Vec3* ALQM_Mat3x4_GetTranslation(const ALQM_Mat3x4* mIn, ALQM_Vec3* vOut)
{
	if ( ALU_SANITY_VALID(mIn && vOut) )
	{
		vOut->v[ALQM_VECX] = mIn->v[0][3];
		vOut->v[ALQM_VECY] = mIn->v[1][3];
		vOut->v[ALQM_VECZ] = mIn->v[2][3];
	}

	return vOut;
}

ALP_Bool ALQM_Mat3x4_ExactlyEqual(const ALQM_Mat3x4* mLHS, const ALQM_Mat3x4* mRHS)
{
	if ( ALU_SANITY_VALID(mLHS && mRHS) )
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
	if ( ALU_SANITY_VALID(mLHS && mRHS) )
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
	if ( ALU_SANITY_VALID(m) )
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
	if ( ALU_SANITY_VALID(m) )
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
	if ( ALU_SANITY_VALID(m) )
	{
		return ALQM_Mat3x4_ExactlyEqual(m, &ALQM_Mat3x4_Identity);
	}

	return ALP_FALSE;
}

ALP_Bool ALQM_Mat3x4_ApproximatelyIdentity(const ALQM_Mat3x4* m)
{
	if ( ALU_SANITY_VALID(m) )
	{
		return ALQM_Mat3x4_ApproximatelyEqual(m, &ALQM_Mat3x4_Identity);
	}

	return ALP_FALSE;
}
