#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;

class Tree {
private:
    vector<vector<int>> descendant_;
    vector<bool> used_;
    vector<int> ret_, tin_;
    int timer_ = 0;
    vector<int> nap_;

    void dfs(int v, int p = -1) {
        int desc_count = 0;
        tin_[v] = timer_++;
        ret_[v] = tin_[v];
        used_[v] = true;
        for (int to: descendant_[v]) {
            if (to == p) {
                continue;
            }
            if (used_[to]) {
                ret_[v] = std::min(ret_[v], tin_[to]);
            } else {
                dfs(to, v);
                ret_[v] = std::min(ret_[to], ret_[v]);
                if (p != -1 && ret_[to] >= tin_[v]) {
                    nap_.push_back(v);
                }
                ++desc_count;
            }
        }
        if (p == -1 && desc_count > 1) {
            nap_.push_back(v);
        }
    }

public:
    Tree(vector<vector<int>>& descendant, int n) : descendant_(descendant), 
            used_(n, false), ret_(n), tin_(n) {
    
        for (int i = 1; i < n; ++i) {
            if (!used_[i]) {
                dfs(i);
            }
        }
        std::sort(nap_.begin(), nap_.end());
        auto last = std::unique(nap_.begin(), nap_.end());
        nap_.erase(last, nap_.end());
        std::cout << nap_.size() << '\n';
        for (int i: nap_) {
            std::cout << i << ' ';
        }
    }

    ~Tree() {}
};

int main() {
    int n, m;
    std::cin >> n >> m;
    ++n;
    vector<vector<int>> descendant(n);
    int from, to;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to;
        descendant[from].push_back(to);
        descendant[to].push_back(from);
    }
    Tree tree(descendant, n);
}

