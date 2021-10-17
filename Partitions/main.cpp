#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>

int Solve(int A, std::vector<int> &B) {
	if (A < 3)  {
		return 0;
	}

	if (std::find_if(B.cbegin(), B.cend(), [](int x) { return x != 0; }) == B.cend()) {
		return B.size() * 3 + 1;
	}

	auto sum = std::accumulate(B.cbegin(), B.cend(), 0);
	if (sum % 3 != 0) {
		return 0;
	}

	int ret = 1;
	int sum1 = 0;
	int sum3 = 0;

	auto front = B.cbegin();
	while (front != B.cend() - 2) {
		sum1 += *front++;
		if (sum1 == sum / 3) {
			break;
		}
	}
	if (sum1 != sum / 3) {
		return 0;
	}

	auto back = B.cend() - 1;
	while (back != front) {
		sum3 += *back--;
		if (sum3 == sum / 3) {
			break;
		}
	}

	int sum2 = 0;

	for (auto i = front; i != back; ++i) {
		sum2 += *i;
		if (sum2 == 0) {
			++ret;
		}
	}

	sum2 = 0;

	for (auto i = back; i != front; --i) {
		sum2 += *i;
		if (sum2 == 0) {
			++ret;
		}
	}

	return ret;
}

int main() {
	std::vector<int> example = { 1, 2, 3, 0, 3 };
	// std::vector<int> example = { 0, 1, -1, 0 };
	// std::vector<int> example = { 3, 3, -3, 3, 3 };
	// std::vector<int> example = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	// std::vector<int> example = { 1, -1, 0, 0 };

	std::cout << Solve(example.size(), example) << std::endl;
	return 0;
}