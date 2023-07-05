#include <iostream>
#include <cmath>

int64_t binpow(int64_t a, int64_t x, int64_t m) {
	if (x == 0) return 1;
	if (x & 1) return (binpow(a, x - 1, m) * a + m) % m;
	else {
		int64_t b = binpow(a, x / 2, m) % m;
		return (b * b) % m;
	}
}

int main() {
	int64_t m = 1e9 + 7;
	int64_t a, b, c, d;
	std::cin >> a >> b >> c >> d;
	a = (a + m) % m;
	b = (b + m) % m;
	c = (c + m) % m;
	d = (d + m) % m;
	int64_t x = (a * d + m) % m + (b * c + m) % m;
	int64_t y = binpow((b * d + m) % m, m - 2, m) % m;
	std::cout << (x * y + m) % m;
}

