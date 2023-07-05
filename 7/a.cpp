#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<bool>> matrix(n, std::vector<bool>(m));
    int node_1, node_2;
    for (int i = 0; i < m; ++i) {
        std::cin >> node_1 >> node_2;
        matrix[node_1 - 1][i] = 1;
        matrix[node_2 - 1][i] = 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

