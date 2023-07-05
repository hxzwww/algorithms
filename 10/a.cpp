#include <iostream>
#include <vector>


std::vector<int> p_function(const std::string& str) {
	int n = str.size();
	std::vector<int> p(n);
	for (int i = 1; i < n; ++i) {
		int j = p[i - 1];
		while (j > 0 && str[j] != str[i]) {
			j = p[j - 1];
		}
		if (str[j] == str[i]) {
			++j;
		}
		p[i] = j;
	}
	return p;
}

int main() {
	std::string text, pattern;
	std::cin >> text >> pattern;
	std::string str = pattern + '#' + text;
	int size = pattern.size();
	auto a = p_function(str);
	for (int i = 0; i < str.size() - size - 1; ++i) {
		if (a[i + size + 1] == size) {
			std::cout << i - size + 1 << ' ';
		}
	}
}

