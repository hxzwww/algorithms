#include <functional>
#include <iostream>
#include <vector>
#include <queue>
using std::vector;
using std::pair;

struct edge {
    int to = 0;
    int weight = 0;
};

long long alg_prima(int n, const vector<vector<edge>>& neighb) {
    long long answ = 0;
    vector<int> from(n + 1);
    vector<bool> used(n + 1);
   
    std::priority_queue<pair<int, int>, vector<pair<int, int>>, 
        std::greater_equal<pair<int, int>>> q;
    
    q.push({0, 1});
    
    while (!q.empty()) {
        int dist = q.top().first;
        int v = q.top().second;
        q.pop();
        if (used[v]) continue;
        used[v] = true;
        answ += dist;
        for (const edge& go: neighb[v]) {
            if (!used[go.to]) q.push({go.weight, go.to});
        }
    }    

    return answ;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    if (n * m == 0) {
        std::cout << 0;
        return 0;
    }
    vector<vector<edge>> neighb(n + 1);
    int from, to, weight;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to >> weight;
        if (from == to) continue;
        neighb[from].push_back(edge{to, weight});
        neighb[to].push_back(edge{from, weight});
    }
    std::cout << alg_prima(n, neighb);
}
