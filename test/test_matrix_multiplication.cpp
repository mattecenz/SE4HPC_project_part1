#include "matrix_multiplication.h"
#include "matrix_utils.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <cmath>

// ######################### Source code of multiplyMatrices in src/matrix_mult
// The call to multiplyMatrices(A, B, C, rowsA, colsA, colsB) assumes that:
//   * A has rowsA rows, each has colsA elements
//   * B has colsA rows, each has colsB elements
//   * C has rowsA rows, each has colsB elements
//
// We are not going to address test cases where these assumptions are broken

/*

TEST(MatrixMultiplicationTest, TestMultiplyByZeros) {
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

TEST(MatrixMultiplicationTest, TestOddColumns) {
	auto A = build_empty_matrix(1, 3);
	auto B = build_empty_matrix(3, 1);
	auto C = build_empty_matrix(1, 1);
	auto expected = build_empty_matrix(1, 1);

	multiplyMatrices(A, B, C, 1, 3, 1);
	multiplyMatricesWithoutErrors(A, B, expected, 1, 3, 1);

	ASSERT_EQ(C, expected) << "Multiplication should allow arbitrary sizes!";

}

*/

	/*
	
	We will try to test each error individually, so that no test will produce the 

	Since the testing will produce the fictional errors, we will employ the ASSERT_NE in order to
	show that the result is not what we expected

	*/

using Matrix = std::vector<std::vector<int>>;

	//  Error 1: Element-wise multiplication of ones detected!
TEST(MatrixMultiplicationTest, Error1Test){

	Matrix A = {
	
		{2,1},

	};

	Matrix B = {

		{7,2},
		{8,1}
		
	};

	Matrix C(A.size(),std::vector<int>(B[0].size(),0));

	Matrix E = {
		{25,5}
	};

	multiplyMatrices(A,B,C,A.size(),A[0].size(),B[0].size());

	ASSERT_NE(C,E);

}
	//  Error 2: Matrix A contains the number 7!
TEST(MatrixMultiplicationTest, Error2Test){

	//NB: this will print it two times but it is not possible to print it only once

	Matrix A = {

		{2,7},

	};

	Matrix B = {

		{1,2},
		{8,4}
		
	};

	Matrix C(A.size(),std::vector<int>(B[0].size(),0));

	Matrix E = {

		{58,32}

	};

	multiplyMatrices(A,B,C,A.size(),A[0].size(),B[0].size());

	ASSERT_NE(C,E);

}
	//  Error 3: Matrix A contains a negative number!
TEST(MatrixMultiplicationTest, Error3Test){

	//NB: this will print it two times but it is not possible to print it only once

	Matrix A = {

		{-2,9},

	};

	Matrix B = {

		{1,2},
		{8,4}
		
	};

	Matrix C(A.size(),std::vector<int>(B[0].size(),0));

	Matrix E = {

		{70,32}

	};

	multiplyMatrices(A,B,C,A.size(),A[0].size(),B[0].size());

	ASSERT_NE(C,E);

}
	//  Error 4: Matrix B contains the number 3!
TEST(MatrixMultiplicationTest, Error4Test){
	
	Matrix A = {

		{5,3},

	};

	Matrix B = {

		{1,3},
		{8,4}
		
	};

	Matrix C(A.size(),std::vector<int>(B[0].size(),0));

	Matrix E = {

		{29,27}

	};

	multiplyMatrices(A,B,C,A.size(),A[0].size(),B[0].size());

	ASSERT_NE(C,E);

}
	//  Error 5: Matrix B contains a negative number!
TEST(MatrixMultiplicationTest, Error5Test){

	Matrix A = {

		{2,6},

	};

	Matrix B = {

		{-1,2},
		{8,4}
		
	};

	Matrix C(A.size(),std::vector<int>(B[0].size(),0));

	Matrix E = {
		{46,28}
	};

	multiplyMatrices(A,B,C,A.size(),A[0].size(),B[0].size());

	ASSERT_NE(C,E);

}
	//  Error 6: Result matrix contains a number bigger than 100!
TEST(MatrixMultiplicationTest, Error6Test){

	Matrix A = {

		{9,15},

	};

	Matrix B = {

		{4,2},
		{8,4}
		
	};

	Matrix C(A.size(),std::vector<int>(B[0].size(),0));

	Matrix E = {
		{156,78}
	};

	multiplyMatrices(A,B,C,A.size(),A[0].size(),B[0].size());

	ASSERT_NE(C,E);

}
	//  Error 7: Result matrix contains a number between 11 and 20!
TEST(MatrixMultiplicationTest, Error7Test){

	Matrix A = {

		{2,6},

	};

	Matrix B = {

		{1,2},
		{8,2}
		
	};

	Matrix C(A.size(),std::vector<int>(B[0].size(),0));

	Matrix E = {
		{50,16}
	};

	multiplyMatrices(A,B,C,A.size(),A[0].size(),B[0].size());

	ASSERT_NE(C,E);

}
	//  Error 8: Result matrix contains zero!
TEST(MatrixMultiplicationTest, Error8Test){

	//NB: this will print it two times but it is not possible to print it only once

	Matrix A = {

		{0,0},

	};

	Matrix B = {

		{1,2},
		{8,4}
		
	};

	Matrix C(A.size(),std::vector<int>(B[0].size(),0));

	Matrix E = {
		{0,0}
	};

	multiplyMatrices(A,B,C,A.size(),A[0].size(),B[0].size());

	ASSERT_NE(C,E);

}
	//  Error 9: Result matrix contains the number 99!
TEST(MatrixMultiplicationTest, Error9Test){

	Matrix A = {

		{9,2},

	};

	Matrix B = {

		{11,2},
		{0,4}
		
	};

	Matrix C(A.size(),std::vector<int>(B[0].size(),0));

	Matrix E = {
		{99,26}
	};

	multiplyMatrices(A,B,C,A.size(),A[0].size(),B[0].size());

	ASSERT_NE(C,E);

}
	// Error 10: A row in matrix A contains more than one '1'!
TEST(MatrixMultiplicationTest, Error10Test){

	Matrix A = {

		{1,1},

	};

	Matrix B = {

		{4,2},
		{2,4}
		
	};

	Matrix C(A.size(),std::vector<int>(B[0].size(),0));

	Matrix E = {
		{6,6}
	};

	multiplyMatrices(A,B,C,A.size(),A[0].size(),B[0].size());

	ASSERT_NE(C,E);

}
	// Error 11: Every row in matrix B contains at least one '0'!
	// Error 12: The number of rows in A is equal to the number of columns in B!
	// Error 13: The first element of matrix A is equal to the first element of matrix B!
	// Error 14: The result matrix C has an even number of rows!
	// Error 15: A row in matrix A is filled entirely with 5s!
	// Error 16: Matrix B contains the number 6!
	// Error 17: Result matrix C contains the number 17!
	// Error 18: Matrix A is a square matrix!
	// Error 19: Every row in matrix A contains the number 8!
	// Error 20: Number of columns in matrix A is odd!

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
