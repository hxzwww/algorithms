#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using std::vector;

class Tree {
private:
    vector<vector<int>> descendant_;
    vector<bool> used_;
    vector<int> ret_, tin_, tout_;
    int ret_count_ = 0, timer_ = 0;
    std::map<std::pair<int, int>, int> dict_;
    vector<int> res_;

    void dfs(int v, int p = -1) {
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
                if (ret_[to] == tin_[to]) {
                    ++ret_count_;
                    res_.push_back(dict_[
                            std::make_pair(std::min(v, to), std::max(v, to))]);
                }
            }
        }
    }

public:
    Tree(vector<vector<int>>& descendant, int n, 
            std::map<std::pair<int, int>, int>& dict) : descendant_(descendant), 
    used_(n, false), ret_(n), dict_(dict), tin_(n), tout_(n) {
    
        for (int i = 1; i < n; ++i) {
            if (!used_[i]) {
                dfs(i);
            }
        }
        
        std::cout << ret_count_ << '\n';
        std::sort(res_.begin(), res_.end());
        for (int i = 0; i < ret_count_; ++i) {
            std::cout << res_[i] << ' ';
        }
    }

    ~Tree() {}
};

int main() {
    int n, m;
    std::cin >> n >> m;
    ++n;
    vector<vector<int>> descendant(n);
    std::map<std::pair<int, int>, int> dict;
    int from, to, min, max;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to;
        min = std::min(from, to);
        max = std::max(from, to);
        descendant[from].push_back(to);
        descendant[to].push_back(from);
        dict.insert({std::make_pair(min, max), i + 1});
    }
    Tree tree(descendant, n, dict);
}

