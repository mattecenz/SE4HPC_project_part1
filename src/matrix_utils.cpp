#include "matrix_utils.h"
#include <random>


std::vector<std::vector<int>>
build_empty_matrix(const int rows, const int cols) {
	std::vector<std::vector<int>> result(rows);

	for (int i = 0; i < rows; ++i) {
		result[i] = std::vector<int>(cols, 0);
	}

	return result;
}


std::vector<std::vector<int>>
build_random_matrix(const int rows, const int cols, int seed) {
	std::vector<std::vector<int>> result(rows);

	// @TODO: use INT_MIN and INT_MAX
	std::default_random_engine gen(seed);
	std::uniform_int_distribution<int> uniform(-10000, 10000);

	for (int i = 0; i < rows; ++i) {
		result[i] = std::vector<int>(cols, 0);

		for (int j = 0; j < cols; ++j) {
			result[i][j] = uniform(gen);
		}
	}

	return result;
}
