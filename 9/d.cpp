#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
using std::vector;

int n, m, a, b;
vector<vector<bool>> g;
vector<vector<int>> d;
vector<int> partic;
vector<bool> used;
vector<int> match;

std::map<std::pair<int, int>, int> num;
std::map<int, std::pair<int, int>> pair;

bool augment(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int to: d[v]) {
        if (match[to] == -1 || augment(match[to])) {
            match[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    std::cin >> n >> m >> a >> b;
    g.resize(n + 1, vector<bool>(m + 1));
    
    for (int i = 1; i <= n; ++i) {
        std::string s;
        std::cin >> s;
        for (int j = 1; j <= m; ++j) {
            g[i][j] = (s[j - 1] == '*');
        }
    }

    d.resize(1e6);
    used.resize(1e6);
    match.resize(1e6, -1);
    vector<bool> isleft(1e6);

    int counter = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (g[i][j]) {
                
                ++counter;
                num.insert({{i, j}, counter}); 
                pair.insert({counter, {i, j}});   
                partic.push_back(counter);
                
                if (i > 1 && g[i - 1][j]) {
                    int v = num[std::make_pair(i - 1, j)];
                    isleft[counter] = (i + j) % 2;
                    (isleft[counter] ? d[counter].push_back(v) : d[v].push_back(counter));
                }
                if (j > 1 && g[i][j - 1]) {
                    int v = num[std::make_pair(i, j - 1)];
                    isleft[counter] = (i + j) % 2;
                    (isleft[counter] ? d[counter].push_back(v) : d[v].push_back(counter));
                }
            }
        }
    }

    if (a >= b * 2) {
        std::cout << b * counter;
        return 0;
    }

    for (int i: partic) {
        //if (!isleft[i]) continue;
        if (augment(i)) used.assign(1e6, false);
    }
    
    int counta = 0;

    for (int i: partic) {
        if (isleft[i]) continue;
        //std::cout << pair[i].first << "|" << pair[i].second << ' ' << pair[match[i]].first << "|" << pair[match[i]].second << '\n';
        counta += (match[i] != -1);
    }

    std::cout << a * counta + b * (counter - 2 * counta);
}

