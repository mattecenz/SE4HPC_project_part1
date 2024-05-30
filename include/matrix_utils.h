#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H


#include "matrix_multiplication.h"


Matrix build_empty_matrix (const int rows, const int cols);
Matrix build_random_matrix(const int rows, const int cols, int seed = 0);


// maybe useful
// Matrix build_identity_matrix(const int rows, const int cols);


#endif
