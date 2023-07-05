#include <iostream>
#include <vector>
using std::vector;

int n;
vector<vector<int>> g;
vector<vector<int>> c;
int end;
vector<int> used;

int ford_falkerson(int v, int min_flow) {
    if (v == end) return min_flow;
    used[v] = true;
    for (int to: g[v]) {
        if (used[to] || c[v][to] > 0) continue;
        int del = ford_falkerson(to, std::min(min_flow, 1));
        if (del > 0) {
            c[v][to] += del;
            c[to][v] -= del;
            return del;
        }
    }
    return 0;
}

void dfs(int v) {
    std::cout << v << ' ';
    used[v] = true;
    for (int to: g[v]) {
        if (used[to] || c[v][to] > 0) continue;
        dfs(to);
    }
}

int main() {
    std::cin >> n;
    g.resize(n + 1);
    vector<bool> exists(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::string s;
        std::cin >> s;
        for (int j = 1; j <= n; ++j) {
            if (s[j - 1] == '1') {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    int min = 2e9;
    int s, t;

    for (int i = 1; i < n; ++i) {
        for (end = i + 1; end <= n; ++end) {
            c.assign(n + 1, vector<int>(n + 1));
            int cur_ff = 0;
            while (true) {
                used.assign(n + 1, false);
                int tmp = ford_falkerson(i, 2e9);
                cur_ff += tmp;
                if (tmp == 0) break;
            }
            if (min > cur_ff) {
                min = cur_ff;
                s = i;
                t = end; 
            }
        }
    }
    end = t;
    c.assign(n + 1, vector<int>(n + 1));
    while (true) {
        used.assign(n + 1, false);
        int tmp = ford_falkerson(s, min);
        if (!tmp) break;
    }
    used.assign(n + 1, false);
    dfs(s);
    std::cout << '\n';
    dfs(t);
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) std::cout << i << ' ';
    }
}

