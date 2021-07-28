#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>

const int g_size = 10;

std::vector<int> Gen(int max_value = 10) {
	std::vector<int> ret;
	int val = 0;

	ret.reserve(g_size);
	for (int it = 0; it < g_size; ++it) {
		val = rand() % g_size + 1;
		val *= rand() % 2 ? (-1) : 1;
		ret.emplace_back(val);
	}
	return ret;
}

void PrintVector(const std::vector<int> &v) {
	std::cout << "[ ";
	for (size_t it = 0; it < v.size(); ++it) {
			std::cout << v[it] << " ";
	}
	std::cout << "]" << std::endl;
}

int Solve(std::vector<int> &A) {
	if (A.size() < 3) { return 0; }

	std::vector<int> k_values(A.size(), 0);

	int max = A.back();
	for (int i = A.size() - 2; i >= 0; --i) {
		if (A[i] > max) { max = A[i]; }
		if (max > A[i]) { k_values[i] = max; }
	}

	std::set<int> i_values;
	i_values.insert(A.front());

	int ret = 0;
	for (size_t i = 1; i < A.size(); ++i) {
		i_values.insert(A[i]);

		if (k_values[i] != 0) {
			auto i_val = i_values.find(A[i]);

			if (i_val != i_values.begin()) {
				int sum = *(--i_val) + A[i] + k_values[i];
				if (sum > ret) { ret = sum; }
			}
		}
	}
	return ret;
}

int main() {
	std::vector<int> ex(std::move(Gen()));
	PrintVector(ex);
	std::cout << Solve(ex) << std::endl;
	return 0;
}