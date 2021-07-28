#include <iostream>
#include <vector>
#include <cstdlib>

int CoverPoints(std::vector<int> &A, std::vector<int> &B) {
	int steps = 0;

	for (size_t i = 0; i < A.size() - 1; ++i) {
		int x_steps = abs(A[i + 1] - A[i]);
		int y_steps = abs(B[i + 1] - B[i]);
		steps += std::max(x_steps, y_steps);
	}
	return steps;
}

int main() {
	std::vector<int> A = { 4, 8, -7, -5, -13, 9, -7, 8 };
	std::vector<int> B = { 4, -15, -10, -3, -13, 12, 8, -8 };
	int steps = CoverPoints(A, B);
	std::cout << "Expect:   " << 108 << std::endl;
	std::cout << "Actually: " << steps << std::endl;
	return 0;
}