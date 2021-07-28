#include <iostream>
#include <algorithm>
#include <utility>
#include <list>
#include <string>
#include <cstdlib>
#include <ctime>

std::string MultiplyToDigit(const std::string &a, unsigned int digit) {
	std::string ret;
	int remainder = 0;

	if (digit == 0) {
		ret.push_back('0');
		return ret;
	}
	for (auto r_it = a.rbegin(); r_it != a.rend(); ++r_it) {
		int nb = int(*r_it) - 48;
		int res = nb * digit + remainder;
		remainder = res / 10;
		ret.push_back((res > 9 ? res % 10 : res) + 48);
	}
	if (remainder > 0) {
		ret.push_back(remainder + 48);
	}
	std::reverse(ret.begin(), ret.end());
	return ret;
}

void MultiplyToDigitTest(int max_a = 1000, int max_b = 9) {
	int a = rand() % max_a + 1;
	int b = rand() % max_b + 1;
	auto a_str = std::to_string(a);
	std::cout << "Expect:   " << a * b << std::endl;
	std::cout << "Actually: " << MultiplyToDigit(a_str, b) << std::endl;
}

std::string Sum(const std::string &a, const std::string &b) {
	std::string ret;
	auto a_it = a.rbegin();
	auto b_it = b.rbegin();
	int remainder = 0;

	while (a_it != a.rend() || b_it != b.rend()) {
		int a_nb = a_it != a.rend() ? int(*a_it) - 48 : 0;
		int b_nb = b_it != b.rend() ? int(*b_it) - 48 : 0;
		int res = a_nb + b_nb + remainder;
		remainder = res / 10;
		ret.push_back((res > 9 ? res % 10 : res) + 48);
		if (a_it != a.rend()) {
			++a_it;
		}
		if (b_it != b.rend()) {
			++b_it;
		}
	}
	if (remainder > 0) {
		ret.push_back(remainder + 48);
	}
	std::reverse(ret.begin(), ret.end());
	return ret;
}

void SumTest(int max_a = 1000, int max_b = 1000) {
	int a = rand() % max_a + 1;
	int b = rand() % max_b + 1;
	auto a_str = std::to_string(a);
	auto b_str = std::to_string(b);
	std::cout << "Expect:   " << a + b << std::endl;
	std::cout << "Actually: " << Sum(a_str, b_str) << std::endl;
}

std::string Multiply(const std::string &a, const std::string &b) {
	std::string ret("0");
	std::list<std::string> multiply_products;
	const auto *bigger = &a;
	const auto *less = &b;
	size_t i = 0;

	if (a.length() < b.length()) {
		bigger = &b;
		less = &a;
	}
	for (auto it = less->rbegin(); it != less->rend(); ++it) {
		int d = int(*it) - 48;
		auto res = MultiplyToDigit(*bigger, d);
		for (size_t j = 0; j < i; ++j) {
			res.push_back('0');
		}
		multiply_products.emplace_back(std::move(res));
		++i;
	}
	for (auto &val : multiply_products) {
		ret = Sum(ret, val);
	}
	return ret;
}

void MultiplyTest(int max_a = 1000000, int max_b = 1000000) {
	int a = rand() % max_a + 1;
	int b = rand() % max_b + 1;
	auto a_str = std::to_string(a);
	auto b_str = std::to_string(b);
	std::cout << "input:    " << a << ", " << b << std::endl;
	std::cout << "Expect:   " << a * b << std::endl;
	std::cout << "Actually: " << Multiply(a_str, b_str) << std::endl;
}

std::string Factorial(int nb) {
	std::string ret("1");

	for (int i = 1; i <= nb; ++i) {
		auto val = std::to_string(i);
		ret = Multiply(ret, val);
	}
	return ret;
}

int main() {
	srand(time(nullptr));
	int nb = 6;
	auto factorial = Factorial(nb);
	std::cout << "number:    " << nb << std::endl;
	std::cout << "factorial: " << factorial << std::endl;
	return 0;
}