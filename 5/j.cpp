#include <iostream>
#include <vector>

using std::vector;

size_t m = 1e9 + 7;

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];        
    }
    vector<size_t> dp(n, 0);
    size_t ans = 0;
    vector<size_t> b(1000001, 0);
    for (int i = 0; i < n; ++i) {
        if (ans < b[a[i]]) {
            ans += 2*m;
        }
        dp[i] = ans - b[a[i]] + 1;
        dp[i] %= m;
        ans += dp[i];
        ans %= m;
        b[a[i]] += dp[i];
        b[a[i]] %= m;
    }
    std::cout << ans%m;
}

