#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>

static const int m = 1500000;

std::set<int> get_relevant_numbers(std::vector<std::vector<int>>& divisors) {
	std::vector<int> primes;
	std::vector<int> min_divisor(m + 1);
	static int c = 0;
	std::generate(min_divisor.begin(), min_divisor.end(), [](){ return c++; });
	for (int i = 2; i <= m; ++i) {
		if (min_divisor[i] == i) primes.push_back(i);
		for (auto p: primes) {
			if(!(p * i <= m && p <= min_divisor[i])) {
				break;
			}
			min_divisor[i * p] = p;
		}
	}

	for (auto p: primes) {
		for (int i = p; i <= m; i += p) {
			divisors[i].push_back(p);
		}
	}

	std::set<int> relevant_numbers;
	for (int i = 2; i < m; ++i) {
		relevant_numbers.insert(i);
	}

	return relevant_numbers;
}


void solve(std::vector<int>& a, std::vector<std::vector<int>>& divisors, std::set<int>& relevant_numbers) {
	bool have_equals = true;
	for (auto x: a) {
		int current = *relevant_numbers.lower_bound(have_equals ? x : 0);
		have_equals = (current == x ? have_equals : false);
		for (auto i: divisors[current]) {
			for (int j = i; j < m; j += i) {
				relevant_numbers.erase(j);
			}
		}
		std::cout << current << " ";
	}

}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (auto& i: a) {
		std::cin >> i;
	}
	std::vector<std::vector<int>> divisors(m + 1);
	auto relevant_numbers = get_relevant_numbers(divisors);

	solve(a, divisors, relevant_numbers);
}

