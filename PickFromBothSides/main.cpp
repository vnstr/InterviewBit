#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

const int g_size = 10;

std::vector<int> Gen(int max_value = 10) {
	std::vector<int> ret;
	int val = 0;

	ret.reserve(g_size);
	for (int i = 0; i < g_size; ++i) {
		val = rand() % g_size + 1;
		val *= rand() % 2 ? (-1) : 1;
		ret.emplace_back(val);
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

// Complexity: O(n);

int Solve(std::vector<int> &A, int B) {
	auto first = A.begin();
	auto rfirst = A.rbegin();
	int rigth_sum = 0;
	int left_sum = 0;
	int ret = 0;

	for (int i = 0; i < B; i++) {
		rigth_sum += *first;
		left_sum += *rfirst;
		if (B - i > 1) {
			++first;
			++rfirst;
		}
	}
	ret = std::max(rigth_sum, left_sum);
	auto bigger = rigth_sum >= left_sum ? first : A.end() - B;
	auto less   = rigth_sum >= left_sum ? A.end() - 1 : A.begin();
	int bsum    = rigth_sum >= left_sum ? rigth_sum : left_sum;
	int lsum = *less;
	int step = rigth_sum >= left_sum ? -1 : 1;
	for (int i = 1; i < B; i++) {
		bsum -= *bigger;
		bigger += step;
		int sum = bsum + lsum;
		less += step;
		lsum += *less;
		if (sum > ret) {
			ret = sum;
		}
	}
	return ret;
}

int main() {
	srand(time(nullptr));
	auto arr = Gen();
	int range = 5;
	int result = Solve(arr, range);

	PrintVector(arr);
	std::cout << "Actually: " << result << std::endl;
	return 0;
}