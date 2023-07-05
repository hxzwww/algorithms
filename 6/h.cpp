#include <iostream>
#include <vector>

using std::vector;

bool bit(int mask, int u) {
    return (mask >> u) & 1;
}

int count(int mask) {
    int c = 0;
    while (mask) {
        c += (mask & 1);
        mask >>= 1;
    }
    return c;
}

int main() {
    int n;
    std::cin >> n;
    vector<vector<bool>> a(n, vector<bool>(n));
    std::string s;
    for (int i = 0; i < n; ++i) {
        std::cin >> s;
        for (int j = 0; j < n; ++j) {
            a[i][j] = (s[j] == 'Y');
        }
    }
    vector<bool> dp(1 << n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }
            dp[(1 << i) | (1 << j)] = a[i][j];
        }
    }
    int newmask;
    for (int mask = 1; mask < (1 << n); ++mask) {
        if (count(mask) % 2) {
            continue;
        }
        for (int v = 0; v < n; ++v) {
            for (int u = 0; u < n; ++u) {
                if (u == v) {
                    continue;
                }
                if (a[u][v] && !bit(mask, u) && !bit(mask, v)) {
                    newmask = mask | (1 << u) | (1 << v);
                    dp[newmask] = std::max(dp[mask], dp[newmask]);
                }
            }
        }
    }
    int max = 0;
    for (int i = 3; i < (1 << n); ++i) {
        if (dp[i] && (count(i) > max)) {
            max = count(i);
        }
    }
    std::cout << max;
}
