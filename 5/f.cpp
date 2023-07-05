#include <iostream>
#include <vector>

using std::vector;

long long solve(int n) {
    vector<vector<long long>> dp(n + 2, vector<long long>(n + 2, 0));
    long long ans = 1;
    for (int min = 1; min <= n / 2 + 1; ++min) {
        for (int sum = min; sum <= n - min; ++sum) {
            for (int lower = 2 * min - 1; lower >= min; --lower) {
                if (lower == sum) {
                    dp[lower][sum] = 1;
                }
                if (lower < sum) {
                    dp[lower][sum] = dp[lower + 1][sum - lower] + dp[lower + 1][sum];
                }
            }
        }
        ans += dp[min + 1][n - min];
    }
    return ans;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << solve(n);
}

