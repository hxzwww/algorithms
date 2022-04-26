#include <iostream>
#include <vector>

using std::vector;

// dp[last][sum] = количество сумм, равных sum, с максимальным элементом last

// пересчет: кол-во dp[last][sum] равно сумме всех dp[prev_elem][sum - last], 
// т.е. сумме количеств сумм (уменьшенных на last, т.к. мы его добавляем) с 
// максимальным элементом prev_elem

// ответ - сумма всех dp[i][n], где i - макс элемент i-й последовательности с 
// суммой n


long long solve(int n) {
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        dp[i][i] = 1;
    }
    for (int last = 1; last <= n; ++last) {
        for (int sum = last; sum <= n; ++sum) {
            for (int prev_elem = 1; prev_elem <= last / 2; ++prev_elem) {
                dp[last][sum] += dp[prev_elem][sum - last];
            }
        } 
    }
    long long ans = 0; 
    for (int i = 1; i <= n; ++i) {
        ans += dp[i][n];
    }
    return ans;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << solve(n);
}
