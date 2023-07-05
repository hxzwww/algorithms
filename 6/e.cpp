#include <iostream>
#include <vector>

using std::vector;

bool bit(int mask, int u) {
    return (mask >> u) & 1;
}

int main() {
    int n;
    std::cin >> n;
    vector<vector<int>> a(n, vector<int>(n)), dp(n, vector<int>(1 << n, 2e9));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        dp[i][1 << i] = 0;
    }
    int newmask;
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int v = 0; v < n; ++v) {
            for (int u = 0; u < n; ++u) {
                if (!bit(mask, u)) {
                    newmask = mask | (1 << u);
                    dp[u][newmask] = std::min(dp[u][newmask], 
                            dp[v][mask] + a[v][u]);
                }
            }
        }
    }
    int m = 2e9, x, t = (1 << n) - 1;
    for (int i = 0; i < n; ++i) {
        if (m > dp[i][(1 << n) - 1]) {
            m = dp[i][(1 << n) - 1];
            x = i;
        };
    }
    std::cout << m << '\n' << x + 1 << ' ';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (m == dp[j][t - (1 << x)] + a[j][x]) {
                std::cout << j + 1 << ' ';
                t -= (1 << x);
                m -= a[j][x];
                x = j;
                break;
            };
        }
    }
}
