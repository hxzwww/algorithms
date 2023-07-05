#include <iostream>
#include <vector>
#include <numeric>

int main() {
	int n;
	std::cin >> n;
	if (n == 1) {
		std::cin >> n;
		std::cout << (n == 1 ? 0 : -1);
		return 0;
	}
	std::vector<int64_t> a(n);
	int64_t aboba = 0;
	bool have_1 = 0;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		aboba += (a[i] != 1);
		have_1 = (a[i] == 1 ? 1 : have_1);
	}
	if (have_1) {
		std::cout << aboba;
		return 0;
	}
	std::vector<int64_t> vec = a;
	int first = -1, second = 1, result = -1;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < n - i; ++j) {
			vec[j] = std::gcd(vec[j], a[j + i]);
			if (vec[j] == 1) {
				second = (first = j) + i;
				std::cout << second - first + n - 1;
				return 0;
			}
		}
	}
	std::cout << (result == -1 ? -1 : second - first + n - 1);
}

