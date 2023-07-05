#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
using std::vector;

struct edge {                                                                   
    int to, weight;                                                            
}; 

int deikstr(int s, int t, int n, vector<vector<edge>>& neighb) {
    std::set<std::pair<int, int>> heap;
    vector<int> dist(n + 1, 2e9);
    dist[s] = 0;
    for (int i = 1; i <= n; ++i) {
        heap.insert({dist[i], i});
    }
    while (!heap.empty()) {
        int v = heap.begin()->second;
        heap.erase(heap.begin());
        for (edge& e: neighb[v]) {
            if (dist[e.to] > dist[v] + e.weight) {
                heap.erase({dist[e.to], e.to});
                dist[e.to] = dist[v] + e.weight;
                heap.insert({dist[e.to], e.to});
            }
        }
    }
    return dist[t];
}

int main() {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    vector<vector<edge>> neighb(n + 1);
    int from, to, w;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to >> w;
        neighb[from].push_back(edge{to, w});
        neighb[to].push_back(edge{from, w});
    }
    int answ = deikstr(s, t, n, neighb);
    std::cout << (answ == 2e9 ? -1 : answ);
} 

