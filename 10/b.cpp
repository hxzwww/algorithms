#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;


vector<int> z_function(const vector<int>& vec) {
	int n = vec.size();
	vector<int> z(n);
	int l = 0, r = 0;
	for (int i = 1; i < n; ++i) {
		if (l <= i && i <= r) {
			z[i] = std::min(z[i - l], r - i);
		}
		while (i + z[i] < n && vec[z[i]] == vec[i + z[i]]) {
			++z[i];
		}
		if (i + z[i] > r) {
			l = i;
			r = i + z[i];
		}
	}
	return z;
}

vector<int> solve(int n, const vector<int>& vec) {
	vector<int> result;
	auto z = z_function(vec);
	for (int i = 0; i < n / 2; ++i) {
		if (z[2 * (n - i - 1)] >= i + 1) {
			result.push_back(n - i - 1);
		}
	}
	result.push_back(n);
	std::sort(result.begin(), result.end());
	return result;
}


int main() {
	int n, m;
	std::cin >> n >> m;
	vector<int> vec(n * 2);
	for (int i = 0; i < n; ++i) {
		std::cin >> vec[i];
		vec[2 * n - i - 1] = vec[i];
	}
	for (auto i: solve(n, vec)) {
		std::cout << i << ' ';
	}
}

