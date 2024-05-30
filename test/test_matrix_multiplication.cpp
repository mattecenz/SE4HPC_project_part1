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

// We can work on a generic test to find maybe some interesting information
TEST(MatrixMultiplicationTest, GenericTest){
	// We can start with the most simple test possible, a product [1]x[1]=[1]
	Matrix A = {
		{1}
	};
	Matrix B = {
		{1}
	};
	// It is obvious that C has to be a 1x1 matrix with only element 1
	Matrix C = {
		{0}
	};
	// We keep a copy for checking after running the test
	Matrix E = C;
	
	// Call the function (can hardcode the dimensions)
	multiplyMatrices(A,B,C,1,1,1);

	// The first thing that we can assert is that the two matrices E and C are not anymore equal
	EXPECT_NE(C,E); // NB: the operator == for std::vector returns true iff the elements in the two vectors are the same (and same size ofc)

	// We can expect to pass this test (hopefully) and see if we get any error

	// So the test passes but we see some errors:
	// 	Error 1: Element-wise multiplication of ones detected!
	// Error 12: The number of rows in A is equal to the number of columns in B!
	// Error 13: The first element of matrix A is equal to the first element of matrix B!
	// Error 18: Matrix A is a square matrix!
	// Error 20: Number of columns in matrix A is odd!

	//Then we can run the opposite test to see which actually is the value of C
	EXPECT_EQ(C,E); //Leave commented if you want to actually pass the test
	
	// We actually see that the number is [2065], definitely not [1] even if we run it many times and recompile the program

	// Ok then maybe before inspecting all the errors it is best to understand why the number is 2065
	// Maybe it is something of the form C[0][0] = const +A[0][0]*B[0][0] and we want const

	// Let's try and change the matrices a bit (but not too much)
	A[0][0]=2;
	B[0][0]=2;

	// rand(); // Explaination written below	

	// So now we can inspect the result

	multiplyMatrices(A,B,C,1,1,1);

	EXPECT_NE(C,E); //True of course
	EXPECT_EQ(C,E); //False but result is [2055], not of the form described above

	// So it is not so trivial the formula, there is some variability in how it behaves
	// But the result is still deterministic, so it maybe uses a random function in the middle but with a preset seed

	// Then how can we check it ? Well we do not know which random function so let's start with the easiest: rand() from c

	// We can insert it above in the middle of the two function calls and see the result now, if it is truly rand
	// we should expect a different result from [2055]

	// After running the test with the rand() in between...

	// Well well what do we see, now the first result is [2065] and the second is [2081], which means actually 
	// that we got the fact that it uses rand to generate some variance

	// NB: since now we understand that there is randomness maybe running it on different machines (or restarting my computer)
	// will not produce the same exact results

	// Now another strange thing actually is that the numbers seem suspiciously close to 2000, since 
	// rand() normally returns a number betweeen [0,INT_MAX] maybe we are lucky or maybe it is intended

	// To check the results we can run a batch of like 10 (arbitrary but enough) calls to the function
	// Let's store each result in a vector because i do not want to assert it every time

	// std::vector<int> res;

	// for(size_t i=0;i<10;++i){
	// 	multiplyMatrices(A,B,C,1,1,1);
	// 	res.emplace_back(C[0][0]);
	// }

	// And print it to std::cerr for debugging purposes
	
	// std::cerr<<"\tResults: ";
	// for(auto el:res) std::cerr<<el<<" ";
	// std::cerr<<std::endl;

	// So we can actually inspect the results:
	// Results: 2069 2031 2009 1999 2028 2061 1988 2017 2024 2079 

	// So this is not of course just luck (well if it is then we should participate to the SuperEnalotto immediately)
	// Which means that our formula may be adjusted as C[0][0] = const(around 1900) + rand_variance + A[0][0]*B[0][0] (not sure about this part but maybe its testable)

	// |-----------------------------------------------------------------------------------------------|
	// |***********************************************************************************************|
	// |-----------------------------------------------------------------------------------------------|

	// The testing above now requires some fine tuning (finding the constant and the variance) but its complicated

	// So let's focus on the errors above:

	// 	Error 1: Element-wise multiplication of ones detected!
	// Error 12: The number of rows in A is equal to the number of columns in B!
	// Error 13: The first element of matrix A is equal to the first element of matrix B!
	// Error 18: Matrix A is a square matrix!
	// Error 20: Number of columns in matrix A is odd!

	// Ok now as a good software engineer try to remove all of them with a single test

	// Let's create some other matrices for this who hopefully do not contain the errors above
	Matrix F = {
		{1,2},
		{3,4},
		{5,6}
	};
	Matrix G = {
		{2,3,4,5},
		{6,7,8,9}
	};
	// Define result as a 3x4 matrix of zeroes
	Matrix H = build_empty_matrix(3, 4);
	// This is the true result of FxG
	Matrix I = {
		{14,17,20,23},
		{30,37,44,51},
		{46,57,68,79}
	};

	// Call the function and jesus take the wheel !
	multiplyMatrices(F,G,H,3,2,4);

	EXPECT_EQ(H,I);

	// So now we can analyze the results:
	// H Which is: { { 2012, 25, 20, 23 }, { 30, 43, 44, 51 }, { 46, 62, 68, 79 } }

	// Aaaand these are the errors that we unfortunately get (reordered and shown only once)

	//  Error 4: Matrix B contains the number 3!
	//  Error 7: Result matrix contains a number between 11 and 20! (NB: we could check the bounds if are included or not, but honestly who cares)
	// Error 16: Matrix B contains the number 6!

	// I will leave these also here to be a bit more compact (and never scroll from one part to another every time)

	// 	Error 1: Element-wise multiplication of ones detected!
	// Error 12: The number of rows in A is equal to the number of columns in B!
	// Error 13: The first element of matrix A is equal to the first element of matrix B!
	// Error 18: Matrix A is a square matrix!
	// Error 20: Number of columns in matrix A is odd!

	// Let's be honest, at least they are less...

	// So which information can we extract about this ? 
	// Well actually a lot, we notice that only the first element now seems to have that strange pattern described above
	// And actually some results are the same, so in some way the multiplication is right but not completely
	// So an interesting conjecture is : the matrix multiplication will be right iff it will not produce any error
	// Well... if you say that in a vacuum a programmer could say one of two things: "P vs NP will be proven right iff it will not be proven wrong" ; or "no shit bro, who would have thought"

	// Ok let's build some other matrices then that will follow these additional constraints (we can keep the same dimensions for now)

	// And as a wise nodern programmer once said (probably, idk)... one day I will run out of variables names, but definitely not of memory.

	// Let's try also a matrix with dupicates and other dimensions to see if it cries this time
	Matrix J = {
		{4,4},
		{2,8},
		{5,6}
	};
	Matrix K = {
		{2,5,4,5},
		{7,7,8,9}
	};
	// Define result as a 3x4 matrix of zeroes
	Matrix L = build_empty_matrix(3, 4);
	// This is the true result of FxG
	Matrix M = {
		{36,48,48,56},
		{60,66,72,82},
		{52,67,68,79}
	};

	// Call the function and jesus take the wheel !
	multiplyMatrices(J,K,L,3,2,4);	

	EXPECT_EQ(L,M);

	// WOW ! We do not see any errors, I almost wanna cry !
	// Then it means that our conjecture could be right and for the moment we have exhausted our testcases
	// For the moment these are all the errors:

	// 	Error 1: Element-wise multiplication of ones detected!
	//  Error 4: Matrix B contains the number 3!
	//  Error 7: Result matrix contains a number between 11 and 20! (NB: we could check the bounds if are included or not, but honestly who cares)
	// Error 12: The number of rows in A is equal to the number of columns in B!
	// Error 13: The first element of matrix A is equal to the first element of matrix B!
	// Error 16: Matrix B contains the number 6!
	// Error 18: Matrix A is a square matrix!
	// Error 20: Number of columns in matrix A is odd!

	// Another day we will focus on the other 12 errors, we can actually start to generate
	// some other testcases given these errors, because maybe some of them are similar

	// |-----------------------------------------------------------------------------------------------|
	// |***********************************************************************************************|
	// |-----------------------------------------------------------------------------------------------|


}

TEST(MatrixMultiplicationTest, TestMultiplyMatrices) {
	Matrix A = {
		{1, 2, 3},
		{4, 5, 6}
	};

	Matrix B = {
		{7, 8},
		{9, 10},
		{11, 12}
	};

	Matrix C = build_empty_matrix(2, 2);

	multiplyMatrices(A, B, C, 2, 3, 2);

	Matrix expected = {
		{58, 64},
		{139, 154}
	};

	ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
