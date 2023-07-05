#include <iostream>
#include <vector>
using std::vector;

void dfs(int v, vector<vector<int>>& cur, vector<vector<int>>& next, 
vector<bool>& cur_used, vector<bool>& next_used) {
    cur_used[v] = true;
    for (int to: cur[v]) {
        if (next_used[to]) continue;
        dfs(to, next, cur, next_used, cur_used);
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int m, n;
    std::cin >> m >> n;
    vector<vector<int>> g(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; ++i) {
        int k;
        std::cin >> k;
        for (int j = 0; j < k; ++j) {
            int v;
            std::cin >> v;
            g[i][v] = 1;
        }
    }

    vector<bool> nas(m + 1);
    
    for (int i = 1; i <= m; ++i) {
        int v;
        std::cin >> v;
        if (v) {
            nas[i] = true;
            g[i][v] = 2;
        }
    }
    
    vector<vector<int>> DL(m + 1);                                                         
    vector<vector<int>> DR(n + 1);                                                         
                                                                                
    vector<bool> usedL(m + 1);                                                             
    vector<bool> usedR(n + 1);

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (g[i][j] == 0) continue;
            if (g[i][j] == 1) DL[i].push_back(j);
            if (g[i][j] == 2) DR[j].push_back(i);
        }
    }

    for (int i = 1; i <= m; ++i) {
        if (nas[i]) continue;
        dfs(i, DL, DR, usedL, usedR);
    }
    
    int resL = 0, resR = 0;

    for (int i = 1; i <= m; ++i) {
        if (!usedL[i]) ++resL;
    }
    
    for (int i = 1; i <= n; ++i) {
        if (usedR[i]) ++resR;
    }

    std::cout << resL + resR;
    
    std::cout << '\n' << resL;
    for (int i = 1; i <= m; ++i) {
        if (!usedL[i]) std::cout << ' ' << i;
    }
    
    std::cout << '\n' << resR;
    for (int i = 1; i <= n; ++i) {
        if (usedR[i]) std::cout << ' ' << i;
    }
}

