#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using matrix_t = std::vector<std::vector<int> >;

const int g_rows = 3;
const int g_colums = 3;

matrix_t Gen(bool random = false, int max_value = 10) {
	matrix_t ret(g_rows);
	int val = 0;

	for (int i = 0; i < g_rows; ++i) {
		for (int j = 0; j < g_colums; ++j) {
			val = random ? rand() % max_value : val + 1;
			ret[i].emplace_back(val);
		}
	}
	return ret;
}

void PrintVector(const std::vector<int> &v) {
	std::cout << "[ ";
	for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i] << " ";
	}
	std::cout << "]" << std::endl;
}

void PrintMatrix(const matrix_t &m) {
	std::cout << "{\n";
	for (size_t i = 0; i < m.size(); ++i) {
		PrintVector(m[i]);
	}
	std::cout << "}" << std::endl;
}

/**
 * {
 *   {1, 2, 3},
 *   {8, 9, 4},  ----> {1, 2, 3, 4 ... 7, 8, 9}
 *   {7, 6, 5}
 * }
 * Complexity: O(n^2).
 */

std::vector<int> SpiralOrder(const matrix_t &A) {
	std::vector<int> ret;
	size_t rows = A.size();
	size_t colums = A.front().size();
	int step = 1;
	int y = 0;
	int x = 0;

	ret.reserve(rows * colums);
	while (rows && colums) {
		for (size_t i = 0; i < colums; ++i) {
			ret.emplace_back(A[y][x]);
			x  = colums - i == 1 ? x : x + step;
		}
		y += step;
		--rows;
		for (size_t i = 0; i < rows; ++i) {
			ret.emplace_back(A[y][x]);
			y  = rows - i == 1 ? y : y + step;
		}
		step *= -1;
		x += step;
		--colums;
	}
	return ret;
}

int main() {
	srand(time(nullptr));
	auto matrix = Gen();
	auto spiral = SpiralOrder(matrix);
	PrintMatrix(matrix);
	PrintVector(spiral);
	return 0;
}
