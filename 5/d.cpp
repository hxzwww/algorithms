#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

int main() {
    int n, k;
    std::cin >> n >> k;
    if (k >= log2(n))  {
        std::cout << ceil(log2(n));
        return 0;
    }
    vector<vector<int>> dp (2, vector<int>(n + 1, 1));
    for (int i = 1; i <= k; ++i) {
        for (int j = i; j <= n; ++j) {
            dp[1][j] = dp[1][j - 1] + dp[0][j - 1];
        }
        dp[0] = dp[1];
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        if (dp[0][i] >= n) {
            ans = i;
            break;
        }
    }
    std::cout << (ans ? ans : -1);
}

