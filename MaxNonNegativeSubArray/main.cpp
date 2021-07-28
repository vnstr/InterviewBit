#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <tuple>

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

std::vector<int> Maxset(std::vector<int> &A) {
	using sub_array_info_t = std::tuple<size_t, size_t, size_t>;
	std::vector<int> ret;
	std::vector<sub_array_info_t> subarrays;  // { {index, sum, len}, ...}
	size_t index = 0;
	size_t max_sum = 0;
	size_t max_len = 0;
	bool new_sub_array = true;

	for (size_t i = 0; i < A.size(); i++) {
		if (A[i] < 0) {
			new_sub_array = true;
			continue;
		}
		if (new_sub_array) {
			subarrays.emplace_back(std::make_tuple(i, A[i], 1));
			new_sub_array = false;
		} else {
			std::get<1>(subarrays.back()) += A[i];
			std::get<2>(subarrays.back()) += 1;;
		}
	}
	for (auto &tuple : subarrays) {
		size_t sum = std::get<1>(tuple);
		size_t len = std::get<2>(tuple);
		bool better = (sum > max_sum) || (sum == max_sum && len > max_len);
		if (better) {
			max_sum = sum;
			max_len = len;
			index = std::get<0>(tuple);
		}
	}
	ret.assign(A.begin() + index, A.begin() + index + max_len);
	return ret;
}

std::vector<int> g_example = {-2, 5, 10, 9, 3, -6, -2, -2, 6, 8};

int main() {
	auto maxset = Maxset(g_example);
	PrintVector(g_example);
	PrintVector(maxset);
	return 0;
}