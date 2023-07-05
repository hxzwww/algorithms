#include <ios>
#include <iostream>
#include <vector>

using std::vector;

int main() {
    std::ios_base::sync_with_stdio(0);
    int n, m;
    std::cin >> n >> m;
    vector<int> d(n);
    vector<vector<int>> pr(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        std::cin >> d[i];
        for (int j = 0; j < m; ++j) {
            std::cin >> pr[i][j];
        }
    }
    vector<vector<uint64_t>> dp(n, vector<uint64_t>(1 << m));
    for (int i = 0; i < n; ++i) {
        for (uint64_t j = 0; j < (1 << m); ++j) {
            dp[i][j] = d[i];
        }
    }
    uint64_t tmp;
    int v;
    vector<uint64_t> min(1 << m, 1e18);
    for (int i = 0; i < n; ++i) {
        for (uint64_t j = 0; j < (1 << m); ++j) {
            tmp = j;
            v = 0;
            while (tmp) {
                dp[i][j] += (pr[i][v] * (tmp & 1));
                tmp >>= 1;
                ++v;
            }
            min[j] = std::min(min[j], dp[i][j]);
        }
    }
    for (uint64_t i = 1; i < (1 << m) ; ++i) {
        for (uint64_t j = 1; j < i - i/ 2; ++j) {
            if ((j & i) == j) {
                min[i] = std::min(min[i], min[j] + min[i ^ j]);
            }
        }
    }
    std::cout << min[(1 << m) - 1];
}

