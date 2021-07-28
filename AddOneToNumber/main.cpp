#include <iostream>
#include <vector>
#include <algorithm>

void PrintVector(const std::vector<int> &v) {
	std::cout << "[ ";
	for (size_t i = 0; i < v.size(); ++i) {
			std::cout << v[i] << " ";
	}
	std::cout << "]" << std::endl;
}

std::vector<int> PlusOne(std::vector<int> &A) {
	std::vector<int> ret;
	auto it = A.rbegin();
	auto end = std::find_if(A.begin(), A.end(), [](int x) { return x !=0; });
	bool plus_one = true;

	while (it.base() != end) {
		int res = *it + plus_one;
		if (res > 9) {
			ret.emplace_back(0);
		} else {
			ret.emplace_back(res);
			plus_one = false;
		}
		++it;
	}
	if (plus_one) {
		ret.emplace_back(1);
	}
	std::reverse(ret.begin(), ret.end());
	return ret;
}

int main() {
	std::vector<int> A = { 0, 3, 7, 6, 4, 0, 5, 5, 5 };
	auto res = PlusOne(A);
	std::cout << "Expect:   " << 124 << std::endl;
	std::cout << "Actually: ";
	PrintVector(res);
	return 0;
}