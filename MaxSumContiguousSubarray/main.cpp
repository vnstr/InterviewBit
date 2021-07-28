#include <iostream>
#include <vector>
#include <cstdlib>

int MaxSubArray(const std::vector<int> &A) {
	auto first = A.begin();
	int sum = *first, max_sum = *first;

	++first;
	while (first != A.end()) {
		if ((*first < 0 && sum <= abs(*first)) || (sum < 0 && *first >= 0)) {
			sum = *first;
		} else {
			sum += *first;
		}
		max_sum = std::max(max_sum, sum);
		++first;
	}
	return max_sum;
}

int main() {
	std::vector<int> A = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
	int res = MaxSubArray(A);
	std::cout << "Expect:   " << 6 << std::endl;
	std::cout << "Actually: " << res << std::endl;
	return 0;
}