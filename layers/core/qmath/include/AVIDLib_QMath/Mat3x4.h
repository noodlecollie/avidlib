/**
 * About: Mat3x4.h
 * This file defines a matrix with 3 rows and 4 columns.
 */

#ifndef AVIDLIB_QMATH_MAT3X4_H
#define AVIDLIB_QMATH_MAT3X4_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_QMath/Vec3.h"
#include "AVIDLib_QMath/Vec4.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constants: Matrix Dimensions
 * ALQM_MAT3X4_ROWS  - Number of rows in the matrix (3).
 * ALQM_MAT3X4_COLS  - Number of columns in the matrix (4).
 * ALQM_MAT3X4_CELLS - Number of cells in the matrix (12).
 */
#define ALQM_MAT3X4_ROWS 3
#define ALQM_MAT3X4_COLS 4
#define ALQM_MAT3X4_CELLS (ALQM_MAT3X4_ROWS * ALQM_MAT3X4_COLS)

/**
 * Struct: ALQM_Mat3x4
 * This type defines a matrix with 3 rows and 4 columns.
 *
 * Operations performed using this matrix are equivalent to performing
 * the same operations with a 4x4 matrix where the final row is
 * [0, 0, 0, 1]. Since this final row is implicit and does not change
 * based on the supported 3x4 matrix operations, it simply does not
 * form part of the <ALQM_Mat3x4> type.
 *
 * The matrix's values are specified in a two-dimensional array.
 * It obeys the following rules when iterating sequentially over
 * the memory:
 *
 * ======= C =======
 * const ALQM_Scalar* values = (const ALQM_Scalar*)mat3x4->v;
 * // values[0] == mat3x4->v[0][0]
 * // values[1] == mat3x4->v[0][1]
 * // values[2] == mat3x4->v[0][2]
 * // values[3] == mat3x4->v[0][3]
 * // values[4] == mat3x4->v[1][0]
 * // values[5] == mat3x4->v[1][1]
 * // values[6] == mat3x4->v[1][2]
 * // values[7] == mat3x4->v[1][3]
 * // ...
 * =================
 *
 * As a consequence, this makes the matrix data row-major.
 *
 * > 2D Indices    1D Indices
 * > 00 01 02 03   0  1  2  3
 * > 10 11 12 13   4  5  6  7
 * > 20 21 22 23   8  9 10 11
 *
 * Cells (0,0) to (2,2) contain rotation values, and cells
 * (0,3) to (2,3) contain translation values.
 *
 * See <Mat3x4.h> for documentation on functions.
 */
typedef struct _ALQM_Mat3x4
{
	/**
	 * Variable: v
	 * Two-dimensional array which holds the matrix values.
	 */
	ALQM_Scalar v[ALQM_MAT3X4_ROWS][ALQM_MAT3X4_COLS];
} ALQM_Mat3x4;

/**
 * Section: Constants
 */

/**
 * Variable: ALQM_Mat3x4_Identity
 * Matrix representing an identity transformation.
 * This transformation is defined such that transforming any
 * vector or matrix by the identity leaves the vector or matrix
 * unchanged.
 */
API_AVIDLIB_QMATH extern const ALQM_Mat3x4 ALQM_Mat3x4_Identity;

/**
 * Section: Operator Functions
 * All functions below assume that their inputs are valid matrices.
 * If this is not the case, undefined behaviour will result.
 *
 * Checking can be turned on by enabling the *PERFORM_VALIDITY_CHECKS*
 * CMake option. If this is turned on and invalid inputs are provided
 * to any of the functions below, an assertion failure will result.
 *
 * For functions which take an input and output matrix,
 * the same matrix object is allowed to be used for both parameters.
 * This can be useful for applying unary operations like negation.
 */

/**
 * Group: Data Accessors
 * The following functions allow direct data access to the matrix.
 * They should be preferred when passing a raw <ALQM_Scalar> array is required.
 */

/**
 * Function: ALQM_Mat3x4_Data
 *
 * Returns a mutable pointer to the beginning of the matrix's data.
 * There are <ALQM_MAT3X4_CELLS> components, and the data is in
 * row-major order.
 *
 * Parameters:
 *
 * m - Matrix whose data should be returned.
 *
 * Returns:
 *
 * Mutable pointer to the matrix's data.
 */
API_AVIDLIB_QMATH ALQM_Scalar* ALQM_Mat3x4_Data(ALQM_Mat3x4* m);

/**
 * Function: ALQM_Mat3x4_CData
 *
 * Returns a const pointer to the beginning of the matrix's data.
 * There are <ALQM_MAT3X4_CELLS> components, and the data is in
 * row-major order.
 *
 * Parameters:
 *
 * m - Matrix whose data should be returned.
 *
 * Returns:
 *
 * Const pointer to the matrix's data.
 */
API_AVIDLIB_QMATH const ALQM_Scalar* ALQM_Mat3x4_CData(const ALQM_Mat3x4* m);

/**
 * Function: ALQM_Mat3x4_To4x4ColMajor
 *
 * Given an array of scalar values, copies the values of the specified
 * matrix to this array. The output array is assumed to represent a
 * 4x4 matrix in column-major order.
 *
 * This function is intended to be useful for external applications
 * which use 4x4 matrices, rather than 3x4 matrices. The final row
 * of the 4x4 matrix will be set to [0, 0, 0, 1].
 *
 * If the length of the output array is less than the required number
 * of elements (16), as many elements as will fit will be copied to
 * the output array. If the length of the output array is greate than
 * required, any other elements in the output array will be left
 * undefined.
 *
 * Parameters:
 *
 * m         - Matrix whose data should be copied.
 * outData   - Array to hold the copied values.
 * outLength - Size of the array in elements (not in bytes).
 */
API_AVIDLIB_QMATH void ALQM_Mat3x4_To4x4ColMajor(const ALQM_Mat3x4* m, ALQM_Scalar* outData, ALP_Size outLength);

/**
 * Function: ALQM_Mat3x4_To4x4RowMajor
 *
 * Given an array of scalar values, copies the values of the specified
 * matrix to this array. The output array is assumed to represent a
 * 4x4 matrix in row-major order.
 *
 * This function is intended to be useful for external applications
 * which use 4x4 matrices, rather than 3x4 matrices. The final row
 * of the 4x4 matrix will be set to [0, 0, 0, 1].
 *
 * If the length of the output array is less than the required number
 * of elements (16), as many elements as will fit will be copied to
 * the output array. If the length of the output array is greate than
 * required, any other elements in the output array will be left
 * undefined.
 *
 * Parameters:
 *
 * m         - Matrix whose data should be copied.
 * outData   - Array to hold the copied values.
 * outLength - Size of the array in elements (not in bytes).
 */
API_AVIDLIB_QMATH void ALQM_Mat3x4_To4x4RowMajor(const ALQM_Mat3x4* m, ALQM_Scalar* outData, ALP_Size outLength);

/**
 * Function: ALQM_Mat3x4_Row
 *
 * Returns a mutable pointer to the beginning of the specified row of the matrix.
 * There are <ALQM_MAT3X4_COLS> components.
 *
 * Parameters:
 *
 * m   - Matrix whose row is selected.
 * row - Index of row to select.
 *
 * Returns:
 *
 * Mutable pointer to row data.
 */
API_AVIDLIB_QMATH ALQM_Scalar* ALQM_Mat3x4_Row(ALQM_Mat3x4* m, ALP_Size row);

/**
 * Function: ALQM_Mat3x4_CRow
 *
 * Returns a const pointer to the beginning of the specified row of the matrix.
 * There are <ALQM_MAT3X4_COLS> components.
 *
 * Parameters:
 *
 * m   - Matrix whose row is selected.
 * row - Index of row to select.
 *
 * Returns:
 *
 * Const pointer to row data.
 */
API_AVIDLIB_QMATH const ALQM_Scalar* ALQM_Mat3x4_CRow(const ALQM_Mat3x4* m, ALP_Size row);

/**
 * Group: Chainable Modifier Functions
 * The following functions take a pointer to the matrix that is modified,
 * and also return this pointer. This allows function calls to be chained,
 * where the output of one call can be passed into another.
 */

/**
 * Function: ALQM_Mat3x4_SetIdentity
 *
 * Sets the given matrix to the identity, where rotation is set to 0,
 * scale is set to 1, and translation is set to 0.
 *
 * Parameters:
 *
 * mOut - Matrix to set to identity.
 *
 * Returns:
 *
 * mOut.
 */
API_AVIDLIB_QMATH ALQM_Mat3x4* ALQM_Mat3x4_SetIdentity(ALQM_Mat3x4* mOut);

/**
 * Function: ALQM_Mat3x4_Zero
 *
 * Sets every component in the given matrix to zero.
 *
 * Parameters:
 *
 * mOut - Matrix to zero.
 *
 * Returns:
 *
 * mOut.
 */
API_AVIDLIB_QMATH ALQM_Mat3x4* ALQM_Mat3x4_Zero(ALQM_Mat3x4* mOut);

/**
 * Function: ALQM_Matrix3x4_Copy
 *
 * Copies the values from mIn to mOut.
 *
 * Parameters:
 *
 * mIn  - Matrix whose values are copied.
 * mOut - Matrix that receives these values.
 *
 * Returns:
 *
 * mOut.
 */
API_AVIDLIB_QMATH ALQM_Mat3x4* ALQM_Mat3x4_Copy(const ALQM_Mat3x4* mIn, ALQM_Mat3x4* mOut);

/**
 * Function: ALQM_Mat3x4_SetValuesArray
 *
 * Sets values in the matrix using a raw ALQM_Scalar array.
 * The count must be at least <ALQM_MAT3X4_CELLS>. Data is
 * expected to be laid out in row-major order.
 *
 * Parameters:
 *
 * values - Pointer to an array of scalar values.
 * count  - Length of this array of values.
 * mOut   - Matrix whose values will be set.
 *
 * Returns:
 *
 * mOut.
 */
API_AVIDLIB_QMATH ALQM_Mat3x4* ALQM_Mat3x4_SetValuesArray(const ALQM_Scalar* values, ALP_Size count, ALQM_Mat3x4* mOut);

/**
 * Function: ALQM_Mat3x4_Concat
 *
 * Concatenates two matrices by multiplying them together.
 *
 * Concatenation is conducted by treating both input matrices as if
 * they were 4x4 matrices with a final row of [0, 0, 0, 1].
 *
 * Parameters:
 *
 * mLHS - Left hand side of the operation.
 * mRHS - Right hand side of the operation.
 * mOut - Matrix in which to store the result.
 *
 * Returns:
 *
 * mOut.
 */
API_AVIDLIB_QMATH ALQM_Mat3x4* ALQM_Mat3x4_Concat(const ALQM_Mat3x4* mLHS, const ALQM_Mat3x4* mRHS, ALQM_Mat3x4* mOut);

/**
 * Function: ALQM_Mat3x4_TransposeRot
 *
 * Transposes the rotational part of the matrix only.
 *
 * Parameters:
 *
 * mIn  - Matrix to transpose.
 * mOut - Matrix in which to store the result.
 *
 * Returns:
 *
 * mOut.
 */
API_AVIDLIB_QMATH ALQM_Mat3x4* ALQM_Mat3x4_TransposeRot(const ALQM_Mat3x4* mIn, ALQM_Mat3x4* mOut);

/**
 * Function: ALQM_Mat3x4_InvertSimple
 *
 * Calculates a simple inversion of the provided matrix.
 *
 * The matrix's scale is assumed to be uniform in all axes. The resulting inverted matrix,
 * set on mOut, holds the inverse of the transformation provided by mIn. In other words,
 * mIn concatenated with mOut produces an identity matrix.
 *
 * *Note* that this function does not cater for matrices where different scales are applied
 * on X, Y, and Z axes. The output is undefined in these cases.
 *
 * Parameters:
 *
 * mIn  - Matrix to calculate inverse of.
 * mOut - Matrix in which to store the result.
 *
 * Returns:
 *
 * mOut.
 */
API_AVIDLIB_QMATH ALQM_Mat3x4* ALQM_Mat3x4_InvertSimple(const ALQM_Mat3x4* mIn, ALQM_Mat3x4* mOut);

/**
 * Function: ALQM_Mat3x4_SetTranslation
 *
 * Sets the matrix's translation component (the final column).
 *
 * Parameters:
 *
 * mIn          - Existing matrix whose translation component should be set.
 * vTranslation - Translation to set.
 * mOut         - Matrix in which to store the result.
 *
 * Returns:
 *
 * mOut.
 */
API_AVIDLIB_QMATH ALQM_Mat3x4* ALQM_Mat3x4_SetTranslation(const ALQM_Mat3x4* mIn, const ALQM_Vec3* vTranslation, ALQM_Mat3x4* mOut);

/**
 * Group: Constant Functions
 * These functions do not modify the matrices they operate on.
 */

/**
 * Function: ALQM_Mat3x4_ExactlyEqual
 *
 * Returns whether two matrices are exactly equal.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Mat3x4_ApproximatelyEqual>.
 *
 * Parameters:
 *
 * mLHS - Left hand side of the comparison.
 * mRHS - Right hand side of the comparison.
 *
 * Returns:
 *
 * True if the matrices are exactly equal, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Mat3x4_ExactlyEqual(const ALQM_Mat3x4* mLHS, const ALQM_Mat3x4* mRHS);

/**
 * Function: ALQM_Mat3x4_ApproximatelyEqual
 *
 * Returns whether two matrices are approximately equal.
 *
 * This is essentially a componentwise comparison which calls <ALQM_ScalarsApproximatelyEqual>.
 *
 * Parameters:
 *
 * mLHS - Left hand side of the comparison.
 * mRHS - Right hand side of the comparison.
 *
 * Returns:
 *
 * True if the matrices are approximately equal, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Mat3x4_ApproximatelyEqual(const ALQM_Mat3x4* mLHS, const ALQM_Mat3x4* mRHS);

/**
 * Function: ALQM_Mat3x4_ExactlyZero
 *
 * Returns whether all the matrix's components are exactly zero.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Mat3x4_ApproximatelyZero>.
 *
 * Parameters:
 *
 * m - Matrix whose components are compared against zero.
 *
 * Returns:
 *
 * True if all the matrix's components are exactly zero, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Mat3x4_ExactlyZero(const ALQM_Mat3x4* m);

/**
 * Function: ALQM_Mat3x4_ApproximatelyZero
 *
 * Returns whether all the matrix's components are approximately zero.
 *
 * Parameters:
 *
 * m - Matrix whose components are compared against zero.
 *
 * Returns:
 *
 * True if all the Matrix's components are approximately zero, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Mat3x4_ApproximatelyZero(const ALQM_Mat3x4* m);

/**
 * Function: ALQM_Mat3x4_ExactlyZero
 *
 * Returns whether the matrix exactly matches the identity matrix.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Mat3x4_ApproximatelyIdentity>.
 *
 * Parameters:
 *
 * m - Matrix whose components are compared against the identity matrix.
 *
 * Returns:
 *
 * True if all the matrix's components exactly match the identity matrix, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Mat3x4_ExactlyIdentity(const ALQM_Mat3x4* m);

/**
 * Function: ALQM_Mat3x4_ApproximatelyIdentity
 *
 * Returns whether the matrix approximately matches the identity matrix.
 *
 * Parameters:
 *
 * m - Matrix whose components are compared against the identity matrix.
 *
 * Returns:
 *
 * True if all the matrix's components approximately match the identity matrix, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Mat3x4_ApproximatelyIdentity(const ALQM_Mat3x4* m);

/**
 * Function: ALQM_Mat3x4_GetTranslation
 *
 * Returns the translation component (the final column) of the matrix.
 *
 * Parameters:
 *
 * mIn  - Matrix whose translation component should be returned.
 * vOut - Vector in which to store the result.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Mat3x4_GetTranslation(const ALQM_Mat3x4* mIn, ALQM_Vec3* vOut);

/**
 * Function: ALQM_Mat3x4_GetRowVec4
 *
 * Returns the specified row as a 4D vector.
 *
 * If the row index is not in range, the output vector is not modified.
 *
 * Parameters:
 *
 * mIn  - Matrix whose row should be returned.
 * row  - Index of the row to be returned. Should be less than <ALQM_MAT3X4_ROWS>.
 * vOut - Output vector in which to store the result.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec4* ALQM_Mat3x4_GetRowVec4(const ALQM_Mat3x4* mIn, ALP_Size row, ALQM_Vec4* vOut);

/**
 * Function: ALQM_Mat3x4_GetColVec3
 *
 * Returns the specified column as a 3D vector.
 *
 * If the column index is not in range, the output vector is not modified.
 *
 * Parameters:
 *
 * mIn  - Matrix whose column should be returned.
 * col  - Index of the column to be returned. Should be less than <ALQM_MAT3X4_COLS>.
 * vOut - Output vector in which to store the result.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec3* ALQM_Mat3x4_GetColVec3(const ALQM_Mat3x4* mIn, ALP_Size col, ALQM_Vec3* vOut);

/**
 * Function: ALQM_Mat3x4_GetColVec4
 *
 * Returns the specified column as a 4D vector. The final element of the vector
 * is 0 if the column index is 0, 1, or 2, or 1 if the column index is 3.
 *
 * If the column index is not in range, the output vector is not modified.
 *
 * Parameters:
 *
 * mIn  - Matrix whose column should be returned.
 * col  - Index of the column to be returned. Should be less than <ALQM_MAT3X4_COLS>.
 * vOut - Output vector in which to store the result.
 *
 * Returns:
 *
 * vOut.
 */
API_AVIDLIB_QMATH ALQM_Vec4* ALQM_Mat3x4_GetColVec4(const ALQM_Mat3x4* mIn, ALP_Size col, ALQM_Vec4* vOut);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_MAT3X4_H
