#include <iostream>
#include <cmath>
#include <vector>

int main() {
	int n;
	std::cin >> n;
	std::vector<bool> prime(n + 1, true);
	prime[0] = prime[1] = false;
	uint64_t answer = 0;
	for (int i = 2; i <= sqrt(n); ++i) {
		if (prime[i]) {
			for (int j = i * i; j <= n; j += i) {
				if (prime[j]) {
					answer += i;
				}
				prime[j] = false;
			}
		}
	}
	std::cout << answer;
}

