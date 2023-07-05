#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
using std::vector;
using std::string;
using p_ii = std::pair<int, int>;
using std::make_pair;

vector<p_ii> neighbors(p_ii v) {
    vector<p_ii> res;
    int x = v.first, y = v.second;
    if (x + 1 < 9 && y + 2 < 9) res.push_back(make_pair(x + 1, y + 2));
    if (x - 1 > 0 && y + 2 < 9) res.push_back(make_pair(x - 1, y + 2));
    if (x + 1 < 9 && y - 2 > 0) res.push_back(make_pair(x + 1, y - 2));
    if (x - 1 > 0 && y - 2 > 0) res.push_back(make_pair(x - 1, y - 2));
    if (x + 2 < 9 && y + 1 < 9) res.push_back(make_pair(x + 2, y + 1));
    if (x - 2 > 0 && y + 1 < 9) res.push_back(make_pair(x - 2, y + 1));
    if (x + 2 < 9 && y - 1 > 0) res.push_back(make_pair(x + 2, y - 1));
    if (x - 2 > 0 && y - 1 > 0) res.push_back(make_pair(x - 2, y - 1));
    return res;
}


vector<vector<p_ii>> bfs(p_ii from, p_ii end) {
    std::queue<p_ii> q;
    q.push(from);
    vector<vector<bool>> used(9, vector<bool>(9));
    used[from.first][from.second] = true;
    vector<vector<p_ii>> p(9, vector<p_ii>(9));
    while (!q.empty()) {
        p_ii v = q.front();
        q.pop();
        for (auto to: neighbors(v)) {
            if (used[to.first][to.second]) {
                continue;
            }
            q.push(to);
            used[to.first][to.second] = true;
            p[to.first][to.second] = v;
            if (to == end) {
                return p;
            }
        }
    }
    return p;
}

vector<p_ii> solve(string read_from, string read_to) {
    p_ii from = make_pair(read_from[0] - 'a' + 1, read_from[1] - '0');
    p_ii to = make_pair(read_to[0] - 'a' + 1, read_to[1] - '0');
    vector<vector<p_ii>> answ = bfs(from, to);
    vector<p_ii> res;
    p_ii v = to;
    while (v != from) {
        res.push_back(v);
        v = answ[v.first][v.second];
    }
    res.push_back(from);
    return res;
}

int main() {
    string read_from, read_to;
    std::cin >> read_from >> read_to;
    vector<p_ii> res = solve(read_from, read_to);
    for (int i = res.size() - 1; i >= 0; --i) {
        std::cout << (char)('a' + res[i].first - 1) << res[i].second << '\n';
    }
}

