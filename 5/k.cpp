#include <iostream>

int count(int* arr, int s, int n) {
    int** dp = new int* [n + 1];
    for (int i = 0; i <= n; ++i) {
        dp[i] = new int [s + 1];
    }
    for (int i = 0; i <= s; ++i) {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= s; ++j) {
            if (j < arr[i - 1]) 
                dp[i][j] = dp[i - 1][j];
            else 
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - arr[i - 1]] + arr[i - 1]);
        }
    }
    int max = dp[n][s];
    for (int i = 0; i <= n; ++i) {
        delete [] dp[i];
    }
    return max;
}

int main() {
    int s, n;
    std::cin >> s >> n;
    int* arr = new int [n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    std::cout << count(arr, s, n);
    delete [] arr;
}

