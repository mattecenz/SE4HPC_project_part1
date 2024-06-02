#include "matrix_multiplication.h"
#include "matrix_utils.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <cmath>

// We can work on a generic test to find maybe some interesting information
TEST(MatrixMultiplicationTest, GenericTest){
	
	// Alias because writing vector of vectors is too long every time (and more clear)
	using Matrix=std::vector<std::vector<int>>;

	// Apply a forced seed
	// srand(0);

	// Print to cerr what rand() I get
	// std::cerr<<"\n\n"<<rand()<<"\n\n";

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
	// Which means that our formula may be adjusted as C[0][0] = const + rand_variance + A[0][0]*B[0][0] (not sure about this part but maybe its testable)

	// It is interesting to see now what happens when forcing a seed using srand().
	// For the moment I will use srand(0), should be the default

	// The results are different, and I will focus on the first two matrices 

	// C
    // Which is: { { 2078 } }
	// C
    // Which is: { { 2034 } }

	// And before they were

	// C
    // Which is: { { 2065 } }
	// C
    // Which is: { { 2055 } }

	// Ok now let's see if i print to std::cerr the first random number I get using rand(); <- do it before the first matrix multiplication
	// We get this number: 1804289383
	// Which may not seem to tell us anything but in reality it does: it tells us that the number has been truncated
	// So now the formula becomes C[0][0] = const + rand_variance%something + A[0][0]*B[0][0]

	// Then let's sample the function 10000 times and calculate mean and standard deviation to see if something interesting arises
	
	// std::vector<int> res;
	// size_t n=10000;

	// for(size_t i=0;i<n;++i){
	// 	multiplyMatrices(A,B,C,1,1,1);
	// 	res.emplace_back(C[0][0]);
	// }

	// double mean=0.;
	// double stdev=0.;

	// for(auto el:res) mean+=(double)el;
	// mean/=n;
	// for(auto el:res) stdev+=(mean-(double)el)*(mean-(double)el);
	// stdev=sqrt(stdev/(n-1));

	// std::cerr<<n<<" samples:\nMean:\t"<<mean<<"\nStdev:\t"<<stdev<<std::endl;

	// 	Mean:	2034.81
	// Stdev:	28.7712

	// Ok interesting now we can see some results

	// |-----------------------------------------------------------------------------------------------|
	// |***********************************************************************************************|
	// |-----------------------------------------------------------------------------------------------|

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
	Matrix H(3,std::vector<int>(4,0));
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
	Matrix L(3,std::vector<int>(4,0));
	// This is the true result
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
	//  Error 7: Result matrix contains a number between 11 and 20!
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

	// It's time to discover some more errors. 
	// So two ideas come to my mind: the first is using negative numbers in multiplication
	// and the other is using the multiplication with the identity matrix (why ? idk it seems cool)

	// Let's start with a matrix with negative numbers (I will try to use some different numbers too)
	// But I will still try to avoid most of the errors

	Matrix N = {
		{7,-3},
		{8,9},
		{10,11}
	};
	Matrix O = {
		{5,5,4,-1},
		{-5,9,8,9}
	};
	// Define result as a 3x4 matrix of zeroes
	Matrix P(3,std::vector<int>(4,0));
	// This is the true result (it contains also some bigger numbers too)
	Matrix Q = {
		{50,8,4,-34},
		{-5,121,104,73},
		{-5,149,128,89}
	};

	// Call the function and jesus take the wheel !
	multiplyMatrices(N,O,P,3,2,4);	

	EXPECT_EQ(P,Q);

	// Hey ! I get some interesting results :
	
	// Error 2: Matrix A contains the number 7!
	// Error 3: Matrix A contains a negative number!
	// Error 5: Matrix B contains a negative number!
	// Error 6: Result matrix contains a number bigger than 100!
	// Error 7: Result matrix contains a number between 11 and 20!

	// I made a ladder ! Do I win something like in poker ? But jokes aside, the new error list becomes:

	// 	Error 1: Element-wise multiplication of ones detected!
	//  Error 2: Matrix A contains the number 7!
	//  Error 3: Matrix A contains a negative number!
	//  Error 4: Matrix B contains the number 3!
	//  Error 5: Matrix B contains a negative number!
	//  Error 6: Result matrix contains a number bigger than 100!
	//  Error 7: Result matrix contains a number between 11 and 20!
	// Error 12: The number of rows in A is equal to the number of columns in B!
	// Error 13: The first element of matrix A is equal to the first element of matrix B!
	// Error 16: Matrix B contains the number 6!
	// Error 18: Matrix A is a square matrix!
	// Error 20: Number of columns in matrix A is odd!

	// Ok trying to fix these errors will result in using non negative small numbers, so it is not very interesting

	// I want to try just out of curiosity what happens with a simple multiplication by the identity now:

	// Use simple matrices (will give errors on columns but who cares honestly)
	Matrix R = {
		{2,0},
		{0,2},
	};
	Matrix S = {
		{1,0},
		{0,1}
	};
	// Define result
	Matrix T(2,std::vector<int>(2,0));
	// The true result now is just R

	// Call the function and jesus take the wheel !
	multiplyMatrices(R,S,T,2,2,2);	

	EXPECT_EQ(R,T);

	// Good ! We get more errors !

	// 	Error 8: Result matrix contains zero!
	// Error 11: Every row in matrix B contains at least one '0'!
	// Error 14: The result matrix C has an even number of rows!

	// Actually fun fact: even if we have the error 8 we get the result:
	// T
	// Which is: { { 2039, 9 }, { 9, 2 } }
	// Which does not contain zero...

	// 	Error 1: Element-wise multiplication of ones detected!
	//  Error 2: Matrix A contains the number 7!
	//  Error 3: Matrix A contains a negative number!
	//  Error 4: Matrix B contains the number 3!
	//  Error 5: Matrix B contains a negative number!
	//  Error 6: Result matrix contains a number bigger than 100!
	//  Error 7: Result matrix contains a number between 11 and 20!
	// 	Error 8: Result matrix contains zero!
	// Error 11: Every row in matrix B contains at least one '0'!
	// Error 12: The number of rows in A is equal to the number of columns in B!
	// Error 13: The first element of matrix A is equal to the first element of matrix B!
	// Error 14: The result matrix C has an even number of rows!
	// Error 16: Matrix B contains the number 6!
	// Error 18: Matrix A is a square matrix!
	// Error 20: Number of columns in matrix A is odd!

	// |-----------------------------------------------------------------------------------------------|
	// |***********************************************************************************************|
	// |-----------------------------------------------------------------------------------------------|

	// Now that I found some errors (15/20) I will try to brute force them a bit
	// What do I mean ? I want to perform the same test as above (multiplication with the identity)
	// but with each diagonal matrix from 0 to 100 (seems reasonable) and manually check if I find new errors

	// Why ? Because I am starting to forget that some numbers behave funny

	// Matrix U = {
	// 	{0,0},
	// 	{0,0},
	// };
	// Matrix V = {
	// 	{1,0},
	// 	{0,1}
	// };
	// Matrix W(2,std::vector<int>(2,0));

	// std::cerr<<"Starting the batch test...\n";
	// for(size_t i=0;i<101;++i){
	// 	W[0][0]=0;
	// 	W[0][1]=0;
	// 	W[1][0]=0;
	// 	W[1][1]=0;

	// 	U[0][0]=i;
	// 	U[1][1]=i;
	// 	std::cerr<<"Testing "<<i<<std::endl;

	// 	multiplyMatrices(U,V,W,2,2,2);	
	// 	EXPECT_EQ(U,W);
	// }
	// std::cerr<<"Finishing the batch test...";

	// Leave it commented, it takes a lot and the test cases can now be isolated

	// Here I will leave the possible new errors I will get (it will take a bit but it may be worth it)

	// Testing 8:
	// Error 19: Every row in matrix A contains the number 8!
	// Testing 99:
	// Error 9: Result matrix contains the number 99!

	// Well that was mostly for nothing... or was it ? (VSauce music intensifies)

	// I noticed something... when showing the error 7 the real output number gets modified.
	// And it is modified by some random pattern, then we are not exactly testing each possible output 
	// in the range (11,20) since we cannot really control it.
	// Sooooooo.... can we actually force it ?
	// Good question actually, let's try to isolate the test now... but maybe in another function

	// 	Error 1: Element-wise multiplication of ones detected!
	//  Error 2: Matrix A contains the number 7!
	//  Error 3: Matrix A contains a negative number!
	//  Error 4: Matrix B contains the number 3!
	//  Error 5: Matrix B contains a negative number!
	//  Error 6: Result matrix contains a number bigger than 100!
	//  Error 7: Result matrix contains a number between 11 and 20!
	// 	Error 8: Result matrix contains zero!
	//  Error 9: Result matrix contains the number 99!
	// Error 11: Every row in matrix B contains at least one '0'!
	// Error 12: The number of rows in A is equal to the number of columns in B!
	// Error 13: The first element of matrix A is equal to the first element of matrix B!
	// Error 14: The result matrix C has an even number of rows!
	// Error 16: Matrix B contains the number 6!
	// Error 18: Matrix A is a square matrix!
	// Error 19: Every row in matrix A contains the number 8!
	// Error 20: Number of columns in matrix A is odd!

}

TEST(MatrixMultiplicationTest, AnotherGenericTest){

	using Matrix=std::vector<std::vector<int>>;

	// We can start by the test which before did work and try to isolate the error 7
	Matrix A = {
		{4,4},
		{2,8},
		{5,6}
	};
	Matrix B = {
		{2,5,4,5},
		{7,7,8,9}
	};
	// Define result as a 3x4 matrix of zeroes
	Matrix C(3,std::vector<int>(4,0));
	// This is the true result
	Matrix D = {
		{36,48,48,56},
		{60,66,72,82},
		{52,67,68,79}
	};

	multiplyMatrices(A,B,C,3,2,4);	

	// Run it again because why not
	EXPECT_EQ(C,D);

	// Re-read error 7;
	//  Error 7: Result matrix contains a number between 11 and 20!

	// Then it should be pretty easy to do, just some number changes should be fine

	// Reset it, cleaner to visualize
	A = {
		{4,1}, // <- Here is the only thing really changed
		{2,8},
		{5,6}
	};
	B = {
		{2,5,4,5},
		{7,7,8,9}
	};
	//Set to zero
	for(auto row:C) for(auto el:row) el=0;
	D = {
		{15,27,24,29}, // <- And here the result of course
		{60,66,72,82},
		{52,67,68,79}
	};

	multiplyMatrices(A,B,C,3,2,4);	

	EXPECT_EQ(C,D);

	// Good, now I have isolated the error, and these are the matrices
	// 	  C
	//     Which is: { { 25, 27, 24, 29 }, { 60, 66, 72, 82 }, { 52, 67, 68, 79 } }
	//   D
	//     Which is: { { 15, 27, 24, 29 }, { 60, 66, 72, 82 }, { 52, 67, 68, 79 } }

	// The funny thing is that the number is modified, so let's try to see the randomness here

	for(size_t i=0;i<20;++i){
		multiplyMatrices(A,B,C,3,2,4);
		EXPECT_EQ(C,D);
	}

	// Well well what did i get... in technical language we say that I found something sus :)

	// 	Error 17: Result matrix C contains the number 17!
	//   C
	//     Which is: { { 2082, 27, 24, 29 }, { 60, 66, 72, 82 }, { 52, 67, 68, 79 } }
	//   D
	//     Which is: { { 15, 27, 24, 29 }, { 60, 66, 72, 82 }, { 52, 67, 68, 79 } }

	//Hihi now I discovered another error... I am only missing 2 now:
	
	// 	Error 1: Element-wise multiplication of ones detected!
	//  Error 2: Matrix A contains the number 7!
	//  Error 3: Matrix A contains a negative number!
	//  Error 4: Matrix B contains the number 3!
	//  Error 5: Matrix B contains a negative number!
	//  Error 6: Result matrix contains a number bigger than 100!
	//  Error 7: Result matrix contains a number between 11 and 20!
	// 	Error 8: Result matrix contains zero!
	//  Error 9: Result matrix contains the number 99!
	// Error 11: Every row in matrix B contains at least one '0'!
	// Error 12: The number of rows in A is equal to the number of columns in B!
	// Error 13: The first element of matrix A is equal to the first element of matrix B!
	// Error 14: The result matrix C has an even number of rows!
	// Error 16: Matrix B contains the number 6!
	// Error 17: Result matrix C contains the number 17!
	// Error 18: Matrix A is a square matrix!
	// Error 19: Every row in matrix A contains the number 8!
	// Error 20: Number of columns in matrix A is odd!

	// Hmmmm so its 15 and 10... I will read through them to see if I can see something to test

	// Idk to me it looks like something that has to do with matrix B (a mirror of errror 19)
	// So I will do a mirror of the batch test I did above

	// Matrix U = {
	// 	{1,0},
	// 	{0,1},
	// };
	// Matrix V = {
	// 	{0,0},
	// 	{0,0}
	// };
	// Matrix W(2,std::vector<int>(2,0));

	// std::cerr<<"Starting the batch test...\n";
	// for(size_t i=0;i<101;++i){
	// 	W[0][0]=0;
	// 	W[0][1]=0;
	// 	W[1][0]=0;
	// 	W[1][1]=0;

	// 	V[0][0]=i;
	// 	V[1][1]=i;
	// 	std::cerr<<"Testing "<<i<<std::endl;

	// 	multiplyMatrices(U,V,W,2,2,2);	
	// 	// This will not hold true in general so comment it
	// 	//EXPECT_EQ(U,W);
	// }
	// std::cerr<<"Finishing the batch test...";

	// Now let's be armed with patience and look for 10 and 15
	// Sucks to suck but nope I was wrong...

	// Ok then maybe let's try with full matrices and not diagonal matrices now

	// Matrix U = {
	// 	{0,0},
	// 	{0,0},
	// };
	// Matrix V = {
	// 	{1,0},
	// 	{0,1}
	// };
	// Matrix W(2,std::vector<int>(2,0));

	// std::cerr<<"Starting the batch test...\n";
	// for(size_t i=0;i<101;++i){
	// 	W[0][0]=0;
	// 	W[0][1]=0;
	// 	W[1][0]=0;
	// 	W[1][1]=0;

	// 	U[0][0]=i;
	// 	U[0][1]=i;
	// 	U[1][0]=i;
	// 	U[1][1]=i;
	// 	std::cerr<<"Testing "<<i<<std::endl;

	// 	multiplyMatrices(U,V,W,2,2,2);	
	// 	//EXPECT_EQ(U,W);
	// }
	// std::cerr<<"Finishing the batch test...";

	// I GOT THEM ! NICE
	// Error 10: A row in matrix A contains more than one '1'!
	// Error 15: A row in matrix A is filled entirely with 5s!

	//  Error 1: Element-wise multiplication of ones detected!
	//  Error 2: Matrix A contains the number 7!
	//  Error 3: Matrix A contains a negative number!
	//  Error 4: Matrix B contains the number 3!
	//  Error 5: Matrix B contains a negative number!
	//  Error 6: Result matrix contains a number bigger than 100!
	//  Error 7: Result matrix contains a number between 11 and 20!
	//  Error 8: Result matrix contains zero!
	//  Error 9: Result matrix contains the number 99!
	// Error 10: A row in matrix A contains more than one '1'!
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

}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
