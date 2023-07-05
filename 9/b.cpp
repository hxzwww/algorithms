#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::pair;
using std::make_pair;


int get(int v, vector<int>& p) {
    if (p[v] == -1) return v;
    return p[v] = get(p[v], p);
}

void unite(int u, int v, vector<int>& size, vector<int>& p) {
    u = get(u, p);
    v = get(v, p);
    if (size[u] < size[v]) std::swap(u, v);
    p[v] = u;
    size[u] += size[v];
}


int solve(int n, int m, vector<pair<int, pair<int, int>>>& vec) {
    int answ = 0;
    vector<int> p(n + 1, -1);
    vector<int> size(n + 1, 1);
    int parent1, parent2;
    int counter = 0;

    for (int i = 0; i < m; ++i) {
        parent1 = get(vec[i].second.first, p);
        parent2 = get(vec[i].second.second, p);
        if (parent1 != parent2 || parent1 == -1 || parent2 == -1) {
            unite(parent1, parent2, size, p);
            ++counter;
            answ += vec[i].first;
        }
        if (counter > n - 1) break;
    }

    return answ;
}


int main() {
    int n, m;
    std::cin >> n >> m;
    vector<pair<int, pair<int, int>>> vec(m);
    int from, to, cost;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to >> cost;
        vec[i] = make_pair(cost, make_pair(from, to));
    }
    std::sort(vec.begin(), vec.end());
    std::cout << solve(n, m, vec);
}

