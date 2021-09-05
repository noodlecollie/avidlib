/**
 * About: Mat4x4.h
 * This file defines a matrix with 3 rows and 4 columns.
 */

#ifndef AVIDLIB_QMATH_MAT4X4_H
#define AVIDLIB_QMATH_MAT4X4_H

#include "AVIDLib_QMath/LibExport.h"
#include "AVIDLib_QMath/Types.h"
#include "AVIDLib_Plat/Int.h"
#include "AVIDLib_Plat/Bool.h"
#include "AVIDLib_QMath/Vec3.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constants: Matrix Dimensions
 * ALQM_MAT4X4_ROWS  - Number of rows in the matrix (4).
 * ALQM_MAT4X4_COLS  - Number of columns in the matrix (4).
 * ALQM_MAT4X4_CELLS - Number of cells in the matrix (12).
 */
#define ALQM_MAT4X4_ROWS 4
#define ALQM_MAT4X4_COLS 4
#define ALQM_MAT4X4_CELLS (ALQM_MAT4X4_ROWS * ALQM_MAT4X4_COLS)

/**
 * Struct: ALQM_Mat4x4
 * This type defines a matrix with 4 rows and 4 columns.
 *
 * The matrix's values are specified in a two-dimensional array.
 * It obeys the following rules when iterating sequentially over
 * the memory:
 *
 * ======= C =======
 * const ALQM_Scalar* values = (const ALQM_Scalar*)mat4x4->v;
 * // values[0] == mat4x4->v[0][0]
 * // values[1] == mat4x4->v[0][1]
 * // values[2] == mat4x4->v[0][2]
 * // values[3] == mat4x4->v[0][3]
 * // values[4] == mat4x4->v[1][0]
 * // values[5] == mat4x4->v[1][1]
 * // values[6] == mat4x4->v[1][2]
 * // values[7] == mat4x4->v[1][3]
 * // ...
 * =================
 *
 * As a consequence, this makes the matrix data row-major.
 *
 * > 2D Indices    1D Indices
 * > 00 01 02 03   0  1  2  3
 * > 10 11 12 13   4  5  6  7
 * > 20 21 22 23   8  9  10 11
 * > 30 31 32 33   12 13 14 15
 *
 * Cells (0,0) to (2,2) contain rotation values, and cells
 * (0,3) to (2,3) contain translation values.
 *
 * See <Mat4x4.h> for documentation on functions.
 */
typedef struct _ALQM_Mat4x4
{
	/**
	 * Variable: v
	 * Two-dimensional array which holds the matrix values.
	 */
	ALQM_Scalar v[ALQM_MAT4X4_ROWS][ALQM_MAT4X4_COLS];
} ALQM_Mat4x4;

/**
 * Section: Constants
 */

/**
 * Variable: ALQM_Mat4x4_Identity
 * Matrix representing an identity transformation.
 * This transformation is defined such that transforming any
 * vector or matrix by the identity leaves the vector or matrix
 * unchanged.
 */
API_AVIDLIB_QMATH extern const ALQM_Mat4x4 ALQM_Mat4x4_Identity;

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
 * Function: ALQM_Mat4x4_Data
 *
 * Returns a mutable pointer to the beginning of the matrix's data.
 * There are <ALQM_MAT4X4_CELLS> components, and the data is in
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
API_AVIDLIB_QMATH ALQM_Scalar* ALQM_Mat4x4_Data(ALQM_Mat4x4* m);

/**
 * Function: ALQM_Mat4x4_CData
 *
 * Returns a const pointer to the beginning of the matrix's data.
 * There are <ALQM_MAT4X4_CELLS> components, and the data is in
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
API_AVIDLIB_QMATH const ALQM_Scalar* ALQM_Mat4x4_CData(const ALQM_Mat4x4* m);

/**
 * Function: ALQM_Mat4x4_ToColMajor
 *
 * Given an array of scalar values, copies the values of the specified
 * matrix to this array. The output array is assumed to represent a
 * 4x4 matrix in column-major order.
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
API_AVIDLIB_QMATH void ALQM_Mat4x4_ToColMajor(const ALQM_Mat4x4* m, ALQM_Scalar* outData, ALP_Size outLength);

/**
 * Function: ALQM_Mat4x4_Row
 *
 * Returns a mutable pointer to the beginning of the specified row of the matrix.
 * There are <ALQM_MAT4X4_COLS> components.
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
API_AVIDLIB_QMATH ALQM_Scalar* ALQM_Mat4x4_Row(ALQM_Mat4x4* m, ALP_Size row);

/**
 * Function: ALQM_Mat4x4_CRow
 *
 * Returns a const pointer to the beginning of the specified row of the matrix.
 * There are <ALQM_MAT4X4_COLS> components.
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
API_AVIDLIB_QMATH const ALQM_Scalar* ALQM_Mat4x4_CRow(const ALQM_Mat4x4* m, ALP_Size row);

/**
 * Group: Chainable Modifier Functions
 * The following functions take a pointer to the matrix that is modified,
 * and also return this pointer. This allows function calls to be chained,
 * where the output of one call can be passed into another.
 */

/**
 * Function: ALQM_Mat4x4_SetIdentity
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
API_AVIDLIB_QMATH ALQM_Mat4x4* ALQM_Mat4x4_SetIdentity(ALQM_Mat4x4* mOut);

/**
 * Function: ALQM_Mat4x4_Zero
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
API_AVIDLIB_QMATH ALQM_Mat4x4* ALQM_Mat4x4_Zero(ALQM_Mat4x4* mOut);

/**
 * Function: ALQM_Matrix4x4_Copy
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
API_AVIDLIB_QMATH ALQM_Mat4x4* ALQM_Mat4x4_Copy(const ALQM_Mat4x4* mIn, ALQM_Mat4x4* mOut);

/**
 * Function: ALQM_Mat4x4_SetValuesArray
 *
 * Sets values in the matrix using a raw ALQM_Scalar array.
 * The count must be at least <ALQM_MAT4X4_CELLS>. Data is
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
API_AVIDLIB_QMATH ALQM_Mat4x4* ALQM_Mat4x4_SetValuesArray(const ALQM_Scalar* values, ALP_Size count, ALQM_Mat4x4* mOut);

/**
 * Function: ALQM_Mat4x4_Concat
 *
 * Concatenates two matrices by multiplying them together.
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
API_AVIDLIB_QMATH ALQM_Mat4x4* ALQM_Mat4x4_Concat(const ALQM_Mat4x4* mLHS, const ALQM_Mat4x4* mRHS, ALQM_Mat4x4* mOut);

/**
 * Function: ALQM_Mat4x4_Transpose
 *
 * Transposes the entire matrix.
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
API_AVIDLIB_QMATH ALQM_Mat4x4* ALQM_Mat4x4_Transpose(const ALQM_Mat4x4* mIn, ALQM_Mat4x4* mOut);

/**
 * Function: ALQM_Mat4x4_TransposeRot
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
API_AVIDLIB_QMATH ALQM_Mat4x4* ALQM_Mat4x4_TransposeRot(const ALQM_Mat4x4* mIn, ALQM_Mat4x4* mOut);

/**
 * Function: ALQM_Mat4x4_InvertSimple
 *
 * Calculates a simple inversion of the provided matrix. This just inverts the transform
 * of the upper left 3x3 region and inverts the 3D translation vector - other cells are
 * not modified.
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
API_AVIDLIB_QMATH ALQM_Mat4x4* ALQM_Mat4x4_InvertSimple(const ALQM_Mat4x4* mIn, ALQM_Mat4x4* mOut);

/**
 * Function: ALQM_Mat4x4_SetTranslation
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
API_AVIDLIB_QMATH ALQM_Mat4x4* ALQM_Mat4x4_SetTranslation(const ALQM_Mat4x4* mIn, const ALQM_Vec3* vTranslation, ALQM_Mat4x4* mOut);

/**
 * Group: Constant Functions
 * These functions do not modify the matrices they operate on.
 */

/**
 * Function: ALQM_Mat4x4_ExactlyEqual
 *
 * Returns whether two matrices are exactly equal.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Mat4x4_ApproximatelyEqual>.
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
API_AVIDLIB_QMATH ALP_Bool ALQM_Mat4x4_ExactlyEqual(const ALQM_Mat4x4* mLHS, const ALQM_Mat4x4* mRHS);

/**
 * Function: ALQM_Mat4x4_ApproximatelyEqual
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
API_AVIDLIB_QMATH ALP_Bool ALQM_Mat4x4_ApproximatelyEqual(const ALQM_Mat4x4* mLHS, const ALQM_Mat4x4* mRHS);

/**
 * Function: ALQM_Mat4x4_ExactlyZero
 *
 * Returns whether all the matrix's components are exactly zero.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Mat4x4_ApproximatelyZero>.
 *
 * Parameters:
 *
 * m - Matrix whose components are compared against zero.
 *
 * Returns:
 *
 * True if all the matrix's components are exactly zero, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Mat4x4_ExactlyZero(const ALQM_Mat4x4* m);

/**
 * Function: ALQM_Mat4x4_ApproximatelyZero
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
API_AVIDLIB_QMATH ALP_Bool ALQM_Mat4x4_ApproximatelyZero(const ALQM_Mat4x4* m);

/**
 * Function: ALQM_Mat4x4_ExactlyZero
 *
 * Returns whether the matrix exactly matches the identity matrix.
 *
 * Note that exactly comparing floating point values is usually a bad idea.
 * In most cases you should use <ALQM_Mat4x4_ApproximatelyIdentity>.
 *
 * Parameters:
 *
 * m - Matrix whose components are compared against the identity matrix.
 *
 * Returns:
 *
 * True if all the matrix's components exactly match the identity matrix, or false otherwise.
 */
API_AVIDLIB_QMATH ALP_Bool ALQM_Mat4x4_ExactlyIdentity(const ALQM_Mat4x4* m);

/**
 * Function: ALQM_Mat4x4_ApproximatelyIdentity
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
API_AVIDLIB_QMATH ALP_Bool ALQM_Mat4x4_ApproximatelyIdentity(const ALQM_Mat4x4* m);

/**
 * Function: ALQM_Mat4x4_GetTranslation
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
API_AVIDLIB_QMATH ALQM_Vec4* ALQM_Mat4x4_GetTranslation(const ALQM_Mat4x4* mIn, ALQM_Vec3* vOut);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AVIDLIB_QMATH_MAT4X4_H
