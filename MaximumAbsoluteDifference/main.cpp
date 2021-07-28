#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

int MaxArr(std::vector<int> &A) {
	int ret = 0;
	int max1 = INT_MIN;
	int min1 = INT_MAX;
	int max2 = INT_MIN;
	int min2 = INT_MAX;

	for (size_t i = 0; i < A.size(); ++i) {
		max1 = std::max(max1, static_cast<int>(A[i] + i));
		min1 = std::min(min1, static_cast<int>(A[i] + i));
		max2 = std::max(max2, static_cast<int>(A[i] - i));
		min2 = std::min(min2, static_cast<int>(A[i] - i));
	}

	ret = std::max(ret, max1 - min1);
	ret = std::max(ret, max2 - min2);

	return ret;
}

int main() {
	std::vector<int> example = {1, 3, -1};
	std::cout << MaxArr(example) << std::endl;
	return 0;
}