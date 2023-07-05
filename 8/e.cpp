#include <iostream>
#include <vector>
#include <queue>
using std::vector;

struct edge { int to = 0; double rab = 0, cab = 0; };

double f(double val, edge& v) {
    return (val - v.cab) * v.rab;
}

int main() {
    int n = 0, m = 0, start = 0;
    double val = 0;
    std::cin >> n >> m >> start;
    std::cin >> val;
    vector<vector<edge>> g(n + 1);
    int a = 0, b = 0;
    double rab = 0, cab = 0, rba = 0, cba = 0;
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b;
        std::cin >> rab >> cab >> rba >> cba;
        g[a].push_back({b, rab, cab});
        g[b].push_back({a, rba, cba});
    }
    vector<double> max(n + 1, 0);
    max[start] = val;
    vector<double> v1 = max;
    vector<double> v2 = max;
    for (int k = 1; k <= 2 * n; ++k) {
        v1 = max;
        for (int a = 1; a <= n; ++a) {
            for (auto& e: g[a]) {
                v1[e.to] = std::max(v1[e.to], f(v1[a], e));
            }
        }
        if (k == n) {
            v2 = v1;
        }
        max = v1;
    }
    for (int i = 1; i <= n; ++i) {
        if (v2[i] != max[i]) {
            std::cout << "YES";
            return 0;
        }
    }
    if (val == max[start]) {
        std::cout << "NO";
    } else {
        std::cout << "YES";
    } 
}

