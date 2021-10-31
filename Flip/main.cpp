#include <iostream>
#include <string>
#include <vector>
#include <utility>

std::vector<int> Flip(std::string A) {
	int start = 0;
	std::vector<int> segments;

	while (A[start] == '1' && start < A.size()) {
		start += 1;
	}

	{
		bool null_segment = true;
		int counter = 0;
		for (; start < A.size(); ++start) {
			char c = A[start];

			if (null_segment && c == '1') {
				null_segment = false;
				segments.emplace_back(counter);
				counter = 0;
			}

			if (!null_segment && c == '0') {
				null_segment = true;
				segments.emplace_back(counter);
				counter = 0;
			}

			++counter;
		}
		if (counter > 0) {
			segments.emplace_back(counter);
		}
	}

	if (segments.empty()) {
		return {};
	}

	int start = start;
	int end = segments.front();

	

	std::vector<int> ret;
	return ret;
}

void Print(const std::vector<int>& v) {
	std::cout << "[ ";
	for (auto i = v.cbegin(); i != v.cend(); ++i) {
		std::cout << *i << (v.cend() - i > 1 ? ", " : " ");
	}
	std::cout << "]" << std::endl;
}

int main() {
	auto ret = Flip("010");
	std::cout << "[ 1, 1 ]" << std::endl;
	Print(ret);

	ret = Flip("00100010");
	std::cout << "[ 1, 8 ]" << std::endl;
	Print(ret);

	ret = Flip("001011000");
	std::cout << "[ 1, 9 ]" << std::endl;
	Print(ret);
	return 0;
}