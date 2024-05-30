#include "matrix_multiplication.h"


void multiplyMatricesWithoutErrors(const Matrix& A, const Matrix& B, Matrix& C, int rowsA, int colsA, int colsB) {
	for (int i = 0; i < rowsA; ++i) {
		for (int j = 0; j < colsB; ++j) {
			C[i][j] = 0;
			for (int k = 0; k < colsA; ++k) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}
