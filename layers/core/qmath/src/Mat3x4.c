#include "AVIDLib_QMath/Mat3x4.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Plat/Check.h"
#include "AVIDLib_Plat/Util.h"

const ALQM_Mat3x4 ALQM_Mat3x4_Identity =
{
	{
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 }
	}
};

float* ALQM_Mat3x4_Data(ALQM_Mat3x4* m)
{
	return ALP_TSANITY_VALID(m, (float*)m->v, ALP_NULL);
}

const float* ALQM_Mat3x4_CData(const ALQM_Mat3x4* m)
{
	return ALP_TSANITY_VALID(m, (const float*)m->v, ALP_NULL);
}

float* ALQM_Mat3x4_Column(ALQM_Mat3x4* m, ALP_Size column)
{
	return ALP_TSANITY_VALID(m && column < ALQM_MAT3X4_COLS, (float*)&m->v[column], ALP_NULL);
}

const float* ALQM_Mat3x4_CColumn(const ALQM_Mat3x4* m, ALP_Size column)
{
	return ALP_TSANITY_VALID(m && column < ALQM_MAT3X4_COLS, (const float*)&m->v[column], ALP_NULL);
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

ALQM_Mat3x4* ALQM_Mat3x4_Copy(const ALQM_Mat3x4* mIn, ALQM_Mat3x4* mOut)
{
	if ( ALP_SANITY_VALID(mIn && mOut) && mIn != mOut )
	{
		ALP_MemCpy(mOut->v, mIn->v, sizeof(mOut->v));
	}

	return mOut;
}

ALQM_Mat3x4* ALQM_Mat3x4_Set(const float* values, ALP_Size count, ALQM_Mat3x4* mOut)
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
