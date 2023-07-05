#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using std::vector;
using std::map;

void euler(int v, vector<vector<int>>& descendant, 
        map<std::pair<int, int>, bool>& used, 
        vector<std::pair<int, int>>& res) {
    for (int i: descendant[v]) {
        std::pair<int, int> edge(v, i);
        if (!used[edge]) {
            used[edge] = true;
            euler(i, descendant, used, res);
            res.push_back(std::make_pair(v, i));
        }
    }
}

int main() {
    int n, start;
    std::cin >> n >> start;
    ++n;
    vector<vector<int>> descendant(n);
    map<std::pair<int, int>, bool> used;
    vector<std::pair<int, int>> res;
    bool read;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            std::cin >> read;
            if (read || i == j) continue;
            descendant[i].push_back(j);
            used.insert({{i, j}, false});
        }
    }
    euler(start, descendant, used, res);
    std::reverse(res.begin(), res.end());
    for (auto& i: res) {
        std::cout << i.first << ' ' << i.second << '\n';
    }
}

