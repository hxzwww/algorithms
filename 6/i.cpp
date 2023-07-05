#include <iostream>
#include <vector>

using std::vector;

const int module = 999999937;
using vvll = vector<vector<long long>>;

vvll mul(vvll a, vvll b) {
    vvll c(5, vector<long long>(5, 0));
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= module;
            }
        }
    }
    return  c;
}

vvll binpow(vvll a, long long n) {
    if (n == 0)
        return vvll({{1,0,0,0,0}, {0,1,0,0,0},
                {0,0,1,0,0}, {0,0,0,1,0}, {0,0,0,0,1}});
    if (n & 1)
        return mul(binpow(a, n - 1), a);
    else {
        vvll t = binpow(a, n / 2);
        return mul(t, t);
    }
}

int main() {
    long long n;
    while (true) {
        std::cin >> n;
        if (!n) {
            break;
        }
        vvll dp(5, vector<long long>(5, 1));
        dp[2][3] = 0;
        dp[2][4] = 0;
        dp[4][3] = 0;
        dp[4][4] = 0;
        dp = binpow(dp, n - 1);
        long long answ = 0;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                answ += dp[i][j];
                answ %= module;
            }
        }
        std::cout << answ << '\n';
    }
}
