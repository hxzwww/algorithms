#include <iostream>
#include <vector>

using std::vector;

int count(vector<int>& sequence1, vector<int>& sequence2, int n, int m) {
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (sequence1[i] != sequence2[j]) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
            else {
                dp[i][j] = std::max(std::max(
                            dp[i - 1][j], dp[i][j - 1]), 1 + dp[i - 1][j - 1]);
            }
        }
    }
    return dp[n][m];
}

int main() {
    int n;
    std::cin >> n;
    vector<int> sequence1(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        std::cin >> sequence1[i + 1];
    }
    int m;
    std::cin >> m;
    vector<int> sequence2(m + 1, 0);
    for (int i = 0; i < m; ++i) {
        std::cin >> sequence2[i + 1];
    }
    std::cout << count(sequence1, sequence2, n, m);
}
