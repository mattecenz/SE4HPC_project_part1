#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H


#include <vector>
using Matrix = std::vector<std::vector<int>>;


void multiplyMatrices             (const Matrix& A, const Matrix& B, Matrix& C, int rowsA, int colsA, int colsB);
void multiplyMatricesWithoutErrors(const Matrix& A, const Matrix& B, Matrix& C, int rowsA, int colsA, int colsB);


#endif // MATRIX_MULTIPLICATION_H
