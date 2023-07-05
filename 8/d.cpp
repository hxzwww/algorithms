#include <iostream>
#include <vector>
using std::vector;

struct edge {long long from, to, w; };

const long long max = 9223372036854775807;

vector<long long> dist;

void dfs(int v, vector<vector<int>>& g, vector<std::string>& color) {
    color[v] = "grey";
    dist[v] = -max;
    for (int to: g[v]) {
        if (color[to] != "white") {
            continue;
        }
        dfs(to, g, color);
    }
    color[v] = "black";
}


int main() {
    int n, m, s;
    std::cin >> n >> m >> s;
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1));
    vector<vector<edge>> g(n + 1);
    vector<vector<int>> h(n + 1);
    long long from, to, w;
    
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to >> w;
        g[to].push_back(edge{from, to, w});
        h[from].push_back(to);
    }
    
    for (int i = 1; i <= n; ++i) 
        dp[i][0] = ((i == s) ? 0 : max);

    for (int k = 1; k <= n; ++k) {
        for (int v = 1; v <= n; ++v) {
            long long min = max;
            for (edge& e: g[v]) {
                long long tmp = dp[e.from][k - 1];
                tmp = (tmp == max ? max : tmp + e.w);
                min = std::min(min, tmp);
            }
            dp[v][k] = std::min(dp[v][k - 1], min);
        }
    }
    
    dist.resize(n + 1, max);
    vector<std::string> color(n + 1, "white");

    for (int i = 1; i <= n; ++i) {
        if (dist[i] == -max) continue;
        if (dp[i][n] < dp[i][n - 1]) {
            dfs(i, h, color);
        } else {
            dist[i] = dp[i][n];
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (dist[i] == max) {
            std::cout << "*\n";
        } else {
            if (dist[i] == -max) {
                std::cout << "-\n";
            } else {
                std::cout << dist[i] << '\n';
            }
        }
    }
}
