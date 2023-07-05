#include <iostream>
#include <vector>

using std::vector;

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i + 1];
    }
    vector<int> b(m + 1);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i + 1];
    }
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    int ans = 0, max;
    for (long long i = 1; i <= n; ++i) {
        max = 0;
        for (long long j = 1; j <= m; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (a[i] == b[j] && max + 1 > dp[i][j]) {
                dp[i][j] = max + 1;
            }
            if (a[i] > b[j] && dp[i - 1][j] > max) {
                max = dp[i - 1][j];
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        ans = std::max(ans, dp[n][i]);
    }
    std::cout << ans;
}

