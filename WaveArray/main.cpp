#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void PrintVector(const std::vector<int> &v) {
	std::cout << "[ ";
	for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i] << " ";
	}
	std::cout << "]" << std::endl;
}

const int g_size = 9;

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

std::vector<int> Wave(std::vector<int> &A) {
	std::vector<int> ret(A.size());
	auto bigger = ret.begin();
	auto less = bigger + 1;

	std::sort(A.begin(), A.end());
	for (auto it = A.begin(); it != A.end(); ++it) {
		if (less < ret.end()) {
			*less = *it++;
		}
		*bigger = *it;
		less += 2;
		bigger += 2;
	}
	return ret;
}

int main(int argc, char** argv) {
	auto example = Gen();
	auto result = Wave(example);
	PrintVector(example);
	PrintVector(result);
	return 0;
}