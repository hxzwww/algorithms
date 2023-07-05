#include <ios>
#include <iostream>
#include <vector>
using std::vector;

bool augment(int v, vector<bool>& used, vector<int>& match, vector<int>& next,
vector<vector<int>>& g) { 
    if (used[v]) return false;                                                  
    used[v] = true;                                                             
    for (int to: g[v]) {
        if (match[v] == to) continue;        
        if (match[to] == -1 || augment(match[to], used, match, next, g)) {                            
            match[to] = v;
            next[v] = to;            
            return true;                                                        
        }                                                                       
    }                                                                           
    return false;                                                               
} 

void search(int v, vector<bool>& used, vector<int>& next, vector<int>& match) {
    if (used[v]) return;
    used[v] = true;
    if (match[v] != -1) 
        search(match[v], used, next, match);
    if (next[v] != -1) 
        search(next[v], used, next, match);
}

int solve(int n, vector<vector<int>>& g) {
    vector<bool> used(n + 1);
    vector<int> match(n + 1, -1);
    vector<int> next(n + 1, -1);
    for (int i = 1; i <= n; ++i) {
        if (augment(i, used, match, next, g)) 
            used.assign(n + 1, false);
    }
    used.assign(n + 1, false);
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        if (used[i]) continue;
        ++res;
        search(i, used, next, match);
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    vector<vector<int>> g(n + 1);
    int from, to;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to;
        g[from].push_back(to);
    }
    std::cout << solve(n, g);
}

