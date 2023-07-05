#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <tuple>

using std::vector;

struct lighthouse {
	double x;
	double y;
	double a;
};

double shifted_atan(double x) {
    return atan(x) < 0 ? atan(x) + M_PI : atan(x);
}

double solve(int n, double l, double r, vector<lighthouse> lighthouses) {
    vector<double> dp(1 << 20);
    for (int mask = 0; mask < (1 << n); ++mask) {
        dp[mask] = l;
        for (int i = 0; i < n; ++i) {
            if ((mask & (1 << i)) == 0) {
                continue;
            }

            double c = dp[mask ^ (1 << i)];
            double x = lighthouses[i].x;
            double y = lighthouses[i].y;
            double a = lighthouses[i].a;
            double first = M_PI * a / (double)180;
            double second = shifted_atan(y / (x - c));
            double third = M_PI - first - second;

            if (third <= 0) {
                return r - l;
            }

            double d = sqrt((x - c) * (x - c) + y * y) * sin(first) / sin(third);
            dp[mask] = std::max(dp[mask], c + d);
        }
    }
	return std::min(dp[(1 << n) - 1], r) - l;
}

int main() {

    int n;
    double l, r;
    std::cin >> n >> l >> r;

    vector<lighthouse> lighthouses(n);

    double x, y, a;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y >> a;
        lighthouses[i] = {x, y, a};
    }

	std::cout << std::fixed << std::setprecision(6);
    std::cout << solve(n, l, r, lighthouses);
}

