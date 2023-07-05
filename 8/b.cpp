#include <iostream>
#include <vector>
#include <queue>
using std::vector;

int n, m, count;

vector<vector<int>> g;

int bfs(int s) {
    vector<int> dist(count + 1, 2e9);
    std::queue<int> q;
    q.push(s);
    dist[s] = 0;
    vector<int> par(count + 1);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to: g[v]) {
            if (dist[to] == 2e9) {
                dist[to] = dist[v] + 1;
                par[to] = v;
                q.push(to);
            } else {
                if (par[v] != to) return dist[v] + dist[to] + 1;
            }
        }
    }
    return 2e9;
}

int main() {
    std::cin >> n >> m;
    g.resize(2e6);
    int a, b, w;
    count = n;
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b >> w;
        
        if (w == 1) {
            g[a].push_back(b);
            g[b].push_back(a);
        } else {
            ++count;
            g[a].push_back(count);
            g[count].push_back(a);
            for (int j = 1; j < w - 1; ++j) {
                ++count;
                g[count].push_back(count - 1);
                g[count - 1].push_back(count);
            }
            g[b].push_back(count);
            g[count].push_back(b);
        }
    }
    
    int min = 2e9;
    for (int i = 1; i <= n; ++i) {
        min = std::min(min, bfs(i));
    }

    std::cout << min;
}

