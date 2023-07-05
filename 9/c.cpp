#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;

struct edge {
    int f, t;
    int64_t w;
    bool operator<(const edge& other) {
        return w < other.w;
    }
};

vector<int> p;

int get(int v) {
    if (p[v] == -1) return v;
    return p[v] = get(p[v]);
}

bool unite(int u, int v) {
    u = get(u);
    v = get(v);
    if (u == v) return false;
    p[v] = u;
    return true;
}


int64_t solve(int n, int m, int mini, vector<int64_t>& a, vector<edge>& ve) {
    for (int i = 1; i <= n; ++i) {                                              
        if (i == mini) continue;                                                
        ve.push_back({i, mini, a[i] + a[mini]});                                
    }                                                                           
    std::sort(ve.begin(), ve.end());                                            
    p.resize(n + 1, -1);
    int64_t answ = 0;

    for (auto& e: ve) {
        if (unite(e.f, e.t)) {
            answ += e.w;
        }
    }

    return answ;
}


int main() {
    int n, m;
    std::cin >> n >> m;
    vector<int64_t> a(n + 1);
    int64_t min = 2e15;
    int mini;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        if (a[i] < min) {
            min = a[i];
            mini = i;
        }
    }
    vector<edge> ve(m);
    int f, t;
    int64_t w;
    for (int i = 0; i < m; ++i) {
        std::cin >> ve[i].f >> ve[i].t >> ve[i].w;
    }
    std::cout << solve(n, m, mini, a, ve);
}

