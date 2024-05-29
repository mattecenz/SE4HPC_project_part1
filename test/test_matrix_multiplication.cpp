#include "matrix_multiplication.h"
#include "matrix_utils.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

// ######################### Source code of multiplyMatrices in src/matrix_mult
// The call to multiplyMatrices(A, B, C, rowsA, colsA, colsB) assumes that:
//   * A has rowsA rows, each has colsA elements
//   * B has colsA rows, each has colsB elements
//   * C has rowsA rows, each has colsB elements
//
// We are not going to address test cases where these assumptions are broken


TEST(MatrixMultiplication, TestMultiplyByZeros) {
	const int rowsA = 10;
	const int colsA = 3;
	const int rowsB = colsA;
	const int colsB = 4;

	auto A = build_empty_matrix(rowsA, rowsB);
	auto B = build_empty_matrix(rowsB, colsB);
	auto C = build_empty_matrix(rowsA, colsB);

	multiplyMatrices(A, B, C, rowsA, colsA, colsB);

	auto expected = build_empty_matrix(rowsA, colsB);
	ASSERT_EQ(C, expected) << "Multiplication of zero matrices must be zero!";
}


TEST(MatrixMultiplicationTest, TestMultiplyMatrices) {
	std::vector<std::vector<int>> A = {
		{1, 2, 3},
		{4, 5, 6}
	};
	std::vector<std::vector<int>> B = {
		{7, 8},
		{9, 10},
		{11, 12}
	};
	std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

	multiplyMatrices(A, B, C, 2, 3, 2);

	std::vector<std::vector<int>> expected = {
		{58, 64},
		{139, 154}
	};

	ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
