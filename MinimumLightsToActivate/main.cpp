#include <iostream>
#include <vector>
#include <algorithm>

// Complexity: A.size() * B;

int MinimumLightsToActivate(std::vector<int> &A, int B) {
	using reverse_iterator = std::vector<int>::reverse_iterator;
	auto light = A.rend();
	int min_lights = 0;
	int lightly = 0;

	for (auto it = A.begin(); it != A.end(); ++it) {
		int distance = int(std::distance(it, A.end()));
		reverse_iterator first(it + std::min(B - 1, distance) + 1);
		reverse_iterator last(it);
		distance = int(std::distance(last, A.rend()));
		last += std::min(B - 1, distance);
		light = std::find_if(first, last, [](int x) {
			return x == 1;
		});
		if (light == last) {
			return -1;
		}
		++min_lights;
		if (light.base() > it) {
			lightly = B - 1 + abs(light.base() - 1 - it);
		} else {
			lightly = B - 1 - abs(light.base() - 1 - it);
		}
		distance = int(std::distance(it, A.end()));
		it += std::min(lightly, distance - 1);
	}
	return min_lights;
}

int main() {

	std::vector<int> A1 = {0, 0, 1, 1, 1, 0, 0, 1};
	int B1 = 3;
	int r1 = MinimumLightsToActivate(A1, B1);
	std::cout << "Expect:   " << 2 << std::endl;
	std::cout << "Actually: " << r1 << std::endl;

	std::vector<int> A2 = {0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1};
	int B2 = 3;
	int r2 = MinimumLightsToActivate(A2, B2);
	std::cout << "Expect:   " << 3 << std::endl;
	std::cout << "Actually: " << r2 << std::endl;

	std::vector<int> A3 = {0, 0, 0, 1, 0};
	int B3 = 3;
	int r3 = MinimumLightsToActivate(A3, B3);
	std::cout << "Expect:   " << -1 << std::endl;
	std::cout << "Actually: " << r3 << std::endl;

	std::vector<int> A4 = {1, 0, 1, 1, 0, 1};
	int B4 = 2;
	int r4 = MinimumLightsToActivate(A4, B4);
	std::cout << "Expect:   " << 3 << std::endl;
	std::cout << "Actually: " << r4 << std::endl;

	std::vector<int> A6 = {0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0};
	int B6 = 12;
	int r6 = MinimumLightsToActivate(A6, B6);
	std::cout << "Expect:   " << 2 << std::endl;
	std::cout << "Actually: " << r6 << std::endl;

	std::vector<int> A5 = {0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0};
	int B5 = 4;
	int r5 = MinimumLightsToActivate(A5, B5);
	std::cout << "Expect:   " << 3 << std::endl;
	std::cout << "Actually: " << r5 << std::endl;
	return 0;
}