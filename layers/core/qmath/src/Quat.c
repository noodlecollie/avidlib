#include "AVIDLib_QMath/Quat.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_Internal_Util/Check.h"
#include "AVIDLib_QMath/Math.h"

const ALQM_Quat ALQM_Quat_Identity = {{ 0, 0, 0, 1 }};

ALQM_Scalar* ALQM_Quat_Data(ALQM_Quat* q)
{
	return ALU_TSANITY_VALID(q, &q->v[0], ALP_NULL);
}

const ALQM_Scalar* ALQM_Quat_CData(const ALQM_Quat* q)
{
	return ALU_TSANITY_VALID(q, &q->v[0], ALP_NULL);
}

ALQM_Quat* ALQM_Quat_SetIdentity(ALQM_Quat* qOut)
{
	if ( ALU_SANITY_VALID(qOut) )
	{
		qOut->v[ALQM_QUATX] = 0;
		qOut->v[ALQM_QUATY] = 0;
		qOut->v[ALQM_QUATZ] = 0;
		qOut->v[ALQM_QUATW] = 1;
	}

	return qOut;
}

ALQM_Quat* ALQM_Quat_Zero(ALQM_Quat* qOut)
{
	if ( ALU_SANITY_VALID(qOut) )
	{
		qOut->v[ALQM_QUATX] = 0;
		qOut->v[ALQM_QUATY] = 0;
		qOut->v[ALQM_QUATZ] = 0;
		qOut->v[ALQM_QUATW] = 0;
	}

	return qOut;
}

ALQM_Quat* ALQM_Quat_Copy(const ALQM_Quat* qIn, ALQM_Quat* qOut)
{
	if ( ALU_SANITY_VALID(qIn && qOut) && qIn != qOut )
	{
		qOut->v[ALQM_QUATX] = qIn->v[ALQM_QUATX];
		qOut->v[ALQM_QUATY] = qIn->v[ALQM_QUATY];
		qOut->v[ALQM_QUATZ] = qIn->v[ALQM_QUATZ];
		qOut->v[ALQM_QUATW] = qIn->v[ALQM_QUATW];
	}

	return qOut;
}

ALQM_Quat* ALQM_Quat_SetValuesArray(const ALQM_Scalar* values, ALP_Size count, ALQM_Quat* qOut)
{
	if ( ALU_SANITY_VALID(values && count >= 4 && qOut) )
	{
		qOut->v[ALQM_QUATX] = values[0];
		qOut->v[ALQM_QUATY] = values[1];
		qOut->v[ALQM_QUATZ] = values[2];
		qOut->v[ALQM_QUATW] = values[3];
	}

	return qOut;
}

ALQM_Quat* ALQM_Quat_Multiply(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS, ALQM_Quat* qOut)
{
	if ( ALU_SANITY_VALID(qLHS && qRHS && qOut) )
	{
		qOut->v[ALQM_QUATX] =
			(qLHS->v[ALQM_QUATW] * qRHS->v[ALQM_QUATX]) +
			(qLHS->v[ALQM_QUATX] * qRHS->v[ALQM_QUATW]) +
			(qLHS->v[ALQM_QUATY] * qRHS->v[ALQM_QUATZ]) -
			(qLHS->v[ALQM_QUATZ] * qRHS->v[ALQM_QUATY]);

		qOut->v[ALQM_QUATY] =
			(qLHS->v[ALQM_QUATW] * qRHS->v[ALQM_QUATY]) +
			(qLHS->v[ALQM_QUATY] * qRHS->v[ALQM_QUATW]) +
			(qLHS->v[ALQM_QUATZ] * qRHS->v[ALQM_QUATX]) -
			(qLHS->v[ALQM_QUATX] * qRHS->v[ALQM_QUATZ]);

		qOut->v[ALQM_QUATZ] =
			(qLHS->v[ALQM_QUATW] * qRHS->v[ALQM_QUATZ]) +
			(qLHS->v[ALQM_QUATZ] * qRHS->v[ALQM_QUATW]) +
			(qLHS->v[ALQM_QUATX] * qRHS->v[ALQM_QUATY]) -
			(qLHS->v[ALQM_QUATY] * qRHS->v[ALQM_QUATX]);

		qOut->v[ALQM_QUATW] =
			(qLHS->v[ALQM_QUATW] * qRHS->v[ALQM_QUATW]) -
			(qLHS->v[ALQM_QUATX] * qRHS->v[ALQM_QUATX]) -
			(qLHS->v[ALQM_QUATY] * qRHS->v[ALQM_QUATY]) -
			(qLHS->v[ALQM_QUATZ] * qRHS->v[ALQM_QUATZ]);
	}

	return qOut;
}

ALQM_Quat* ALQM_Quat_Normalise(const ALQM_Quat* qIn, ALQM_Quat* qOut)
{
	if ( ALU_SANITY_VALID(qIn && qOut) )
	{
		const ALQM_Scalar length = ALQM_Quat_Length(qIn);

		if ( !ALQM_ScalarApproximatelyZero(length) )
		{
			const ALQM_Scalar invLength = 1.0f / length;

			qOut->v[ALQM_QUATX] = qIn->v[ALQM_QUATX] * invLength;
			qOut->v[ALQM_QUATY] = qIn->v[ALQM_QUATY] * invLength;
			qOut->v[ALQM_QUATZ] = qIn->v[ALQM_QUATZ] * invLength;
			qOut->v[ALQM_QUATW] = qIn->v[ALQM_QUATW] * invLength;
		}
		else
		{
			qOut->v[ALQM_QUATX] = 0;
			qOut->v[ALQM_QUATY] = 0;
			qOut->v[ALQM_QUATZ] = 0;
			qOut->v[ALQM_QUATW] = 0;
		}
	}

	return qOut;
}

ALQM_Quat* ALQM_Quat_Add(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS, ALQM_Quat* qOut)
{
	if ( ALU_SANITY_VALID(qLHS && qRHS && qOut) )
	{
		qOut->v[ALQM_QUATX] = qLHS->v[ALQM_QUATX] + qRHS->v[ALQM_QUATX];
		qOut->v[ALQM_QUATY] = qLHS->v[ALQM_QUATY] + qRHS->v[ALQM_QUATX];
		qOut->v[ALQM_QUATZ] = qLHS->v[ALQM_QUATZ] + qRHS->v[ALQM_QUATX];
		qOut->v[ALQM_QUATW] = qLHS->v[ALQM_QUATW] + qRHS->v[ALQM_QUATX];
	}

	return qOut;
}

ALQM_Quat* ALQM_Quat_Subtract(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS, ALQM_Quat* qOut)
{
	if ( ALU_SANITY_VALID(qLHS && qRHS && qOut) )
	{
		qOut->v[ALQM_QUATX] = qLHS->v[ALQM_QUATX] - qRHS->v[ALQM_QUATX];
		qOut->v[ALQM_QUATY] = qLHS->v[ALQM_QUATY] - qRHS->v[ALQM_QUATX];
		qOut->v[ALQM_QUATZ] = qLHS->v[ALQM_QUATZ] - qRHS->v[ALQM_QUATX];
		qOut->v[ALQM_QUATW] = qLHS->v[ALQM_QUATW] - qRHS->v[ALQM_QUATX];
	}

	return qOut;
}

ALQM_Quat* ALQM_Quat_Scale(const ALQM_Quat* qIn, ALQM_Scalar scale, ALQM_Quat* qOut)
{
	if ( ALU_SANITY_VALID(qIn && qOut) )
	{
		qOut->v[ALQM_QUATX] = qIn->v[ALQM_QUATX] * scale;
		qOut->v[ALQM_QUATY] = qIn->v[ALQM_QUATY] * scale;
		qOut->v[ALQM_QUATZ] = qIn->v[ALQM_QUATZ] * scale;
	}

	return qOut;
}

ALQM_Scalar ALQM_Quat_DotProduct(const ALQM_Quat* q0, const ALQM_Quat* q1)
{
	return ALU_TSANITY_VALID(q0 && q1,
							 (q0->v[ALQM_QUATX] * q1->v[ALQM_QUATX]) +
							 (q0->v[ALQM_QUATY] * q1->v[ALQM_QUATY]) +
							 (q0->v[ALQM_QUATZ] * q1->v[ALQM_QUATZ]) +
							 (q0->v[ALQM_QUATW] * q1->v[ALQM_QUATW]),
							 0);
}

ALP_Bool ALQM_Quat_ExactlyEqual(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS)
{
	return ALU_TSANITY_VALID(qLHS && qRHS,
							 ALQM_ScalarsExactlyEqual(qLHS->v[ALQM_QUATX], qRHS->v[ALQM_QUATX]) &&
							 ALQM_ScalarsExactlyEqual(qLHS->v[ALQM_QUATY], qRHS->v[ALQM_QUATY]) &&
							 ALQM_ScalarsExactlyEqual(qLHS->v[ALQM_QUATZ], qRHS->v[ALQM_QUATZ]) &&
							 ALQM_ScalarsExactlyEqual(qLHS->v[ALQM_QUATW], qRHS->v[ALQM_QUATW]),
							 ALP_FALSE);
}

ALP_Bool ALQM_Quat_ApproximatelyEqual(const ALQM_Quat* qLHS, const ALQM_Quat* qRHS)
{
	return ALU_TSANITY_VALID(qLHS && qRHS,
							 ALQM_ScalarsApproximatelyEqual(qLHS->v[ALQM_QUATX], qRHS->v[ALQM_QUATX]) &&
							 ALQM_ScalarsApproximatelyEqual(qLHS->v[ALQM_QUATY], qRHS->v[ALQM_QUATY]) &&
							 ALQM_ScalarsApproximatelyEqual(qLHS->v[ALQM_QUATZ], qRHS->v[ALQM_QUATZ]) &&
							 ALQM_ScalarsApproximatelyEqual(qLHS->v[ALQM_QUATW], qRHS->v[ALQM_QUATW]),
							 ALP_FALSE);
}

ALP_Bool ALQM_Quat_ExactlyZero(const ALQM_Quat* q)
{
	return ALU_TSANITY_VALID(q,
							 ALQM_ScalarExactlyZero(q->v[ALQM_QUATX]) &&
							 ALQM_ScalarExactlyZero(q->v[ALQM_QUATY]) &&
							 ALQM_ScalarExactlyZero(q->v[ALQM_QUATZ]) &&
							 ALQM_ScalarExactlyZero(q->v[ALQM_QUATW]),
							 ALP_FALSE);
}

ALP_Bool ALQM_Quat_ApproximatelyZero(const ALQM_Quat* q)
{
	return ALU_TSANITY_VALID(q,
							 ALQM_ScalarApproximatelyZero(q->v[ALQM_QUATX]) &&
							 ALQM_ScalarApproximatelyZero(q->v[ALQM_QUATY]) &&
							 ALQM_ScalarApproximatelyZero(q->v[ALQM_QUATZ]) &&
							 ALQM_ScalarApproximatelyZero(q->v[ALQM_QUATW]),
							 ALP_FALSE);
}

ALP_Bool ALQM_Quat_ExactlyIdentity(const ALQM_Quat* q)
{
	return ALU_TSANITY_VALID(q,
							 ALQM_Quat_ExactlyEqual(q, &ALQM_Quat_Identity),
							 ALP_FALSE);
}

ALP_Bool ALQM_Quat_ApproximatelyIdentity(const ALQM_Quat* q)
{
	return ALU_TSANITY_VALID(q,
							 ALQM_Quat_ApproximatelyEqual(q, &ALQM_Quat_Identity),
							 ALP_FALSE);
}

ALQM_Scalar ALQM_Quat_Length(const ALQM_Quat* q)
{
	return ALU_TSANITY_VALID(q,
							 ALQM_Sqrt(ALQM_Quat_LengthSquared(q)),
							 0);
}

ALQM_Scalar ALQM_Quat_LengthSquared(const ALQM_Quat* q)
{
	return ALU_TSANITY_VALID(q,
							 ALQM_Quat_DotProduct(q, q),
							 0);
}
