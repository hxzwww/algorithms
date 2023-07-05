#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using std::vector;
using std::unordered_map;

vector<vector<int>> q1;                                                      
vector<vector<int>> q2;

unordered_map<long long, int> aa;

unordered_map<long long, bool> m1;
unordered_map<long long, bool> m2;

vector<vector<int>> c1;
vector<vector<int>> c2;

int n;
vector<int> p1;
vector<int> p2;

int count = 0;

bool flag = false;

long long toi(vector<int>& v) {
    std::string s = "";
    for (auto i: v) {
        s += std::to_string(i);
    }
    return stoll(move(s));
}

void g(vector<int>& v, bool a) {
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= n - i; ++j) {
            std::reverse(v.begin() + j, v.begin() + j + i);
            auto t = toi(v);
            if (a) {
                if (m2.find(t) != m2.end()) {
                    flag = true;
                    return;
                }
                if (m1.find(t) == m1.end()) {
                    m1.insert({t, 1});
                    c1.push_back(v);
                }
            } else {
                if (m1.find(t) != m1.end()) {
                    flag = true;
                    return;
                }
                if (m2.find(t) == m2.end()) {
                    m2.insert({t, 1});
                    c2.push_back(v);
                }
            }
            std::reverse(v.begin() + j, v.begin() + j + i);
        }
    }
}

bool is_same(vector<int>& v1, vector<int>& v2) {
    for (int i = 0; i < n; ++i) 
        if (v1[i] != v2[i])
            return false;
    return true;
}

int main() {
    std::cin >> n;
    p1.resize(n);
    p2.resize(n);
    for (int i = 0; i < n; ++i) 
        std::cin >> p1[i];
    for (int i = 0; i < n; ++i) 
        std::cin >> p2[i];

    if (is_same(p1, p2)) {
        std::cout << 0;
        return 0;
    }

    q1.push_back(p1);
    q2.push_back(p2);

    c1.push_back(p1);
    c2.push_back(p2);

    m1.insert({toi(p1), 1});
    m2.insert({toi(p2), 1});

    while (true) {
        ++count;
        for (vector<int>& i: q1) {
            if (flag) break;
            g(i, 1);
        }
        if (flag) {
            std::cout << count;
            return 0;
        }
        q2 = move(c2);
        ++count;
        for (vector<int>& i: q2) {
            if (flag) break;
            g(i, 0);
        }
        if (flag) {
            std::cout << count;
            return 0;
        }
        q1 = move(c1);
    }
}
