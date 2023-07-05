#include <iostream>
#include <vector>
using std::vector;

void solve(vector<vector<int>>& cost, int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cost[i][j] = std::min(cost[i][j], cost[i][k] + cost[k][j]);
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> cost[i][j];
        }
    }
    solve(cost, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << cost[i][j] << ' ';
        }
        std::cout << '\n';
    }
}
