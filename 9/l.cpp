#include <iostream>
#include <vector>
using std::vector;

void a(vector<bool>& used, int n, vector<int>& match, vector<int>& v, vector<int>& minv, int del, vector<int>& u) {
    for (int j = 0; j <= n; ++j) {                                       
        if (used[j]) {                                                   
            u[match[j]] += del;                                          
            v[j] -= del;                                                 
        } else {                                                         
            minv[j] -= del;                                              
        }                                                               
    }
}

void b(vector<bool>& used, int n, vector<int>& match, vector<int>& v, vector<int>& minv, int& del, vector<int>& u, 
        int& column, int& raw, int& minc, vector<vector<int>>& c,vector<int>& way) {
    used[column] = true;                                                 
    raw = match[column];                                                 
    del = 2e9;                                                           
    minc = 0;                                                            
    for (int j = 1; j <= n; ++j) {                                       
        if (used[j]) continue;                                           
        if (c[raw][j] - u[raw] - v[j] < minv[j]) {                       
            minv[j] = c[raw][j] - u[raw] - v[j];                         
            way[j] = column;                                             
        }                                                                
        if (minv[j] < del) {                                            
            del = minv[j];                                              
            minc = j;                                                   
        }                                                               
    }
}

int main() {
    int n;
    std::cin >> n;
    vector<vector<int>> c(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> c[i][j];
        }
    }
    vector<int> u(n + 1);
    vector<int> v(n + 1);
    vector<int> match(n + 1);
    vector<int> way(n + 1);
    vector<int> minv;
    vector<bool> used;
    int raw, column, del, minc;
    for (int i = 1; i <= n; ++i) {
        match[0] = i;
        column = 0;
        used.assign(n + 1, false);
        minv.assign(n + 1, 2e9);
        while (match[column]) {
            b(used, n, match, v, minv, del, u, column, raw, minc, c, way);
            a(used, n, match, v, minv, del, u);
            column = minc;
        }
        while (column) {
            match[column] = match[way[column]];
            column = way[column];
        }
    }
    vector<int> s(1e5);
    for (int i = 0; i < 1e7; ++i) {
        int x = 1;
    }
    for (int i = 1; i <= n; ++i) {
        u[match[i]] = i;
    }
    std::cout << -v[0] << '\n';
    for (int i = 1; i <= n; ++i) {
        std::cout << i << ' ' << u[i] << '\n';
    }
}

