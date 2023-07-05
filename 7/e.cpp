#include <iostream>
#include <vector>
#include <deque>

using std::vector;

class Tree {
private:
    vector<vector<int>> descendant_;
    vector<vector<int>> reverse_descendant_;
    vector<char> color_;
    std::deque<int> p_;
    vector<int> num_;
    int csc_count_ = 0, edges_count_ = 0;
    vector<vector<int>> condensation_graph_;

    void dfs(int v) {
        color_[v] = 'g';
        for (int to: descendant_[v]) {
            if (to == v || color_[to] != 'w') {
                continue;
            } 
            dfs(to);
        }
        p_.push_front(v);
        color_[v] = 'b';
    }

    void dfsR(int v, int val) {
        color_[v] = 'g';
        num_[v] = val;
        for (int to: reverse_descendant_[v]) {
            if (to == v || color_[to] != 'b') {
                continue;
            }
            dfsR(to, val);
        }
        color_[v] = 'w';
    }

public:
    Tree(vector<vector<int>>& descendant, vector<vector<int>>& 
            reverse_descendant, int n) : descendant_(std::move(descendant)),
            reverse_descendant_(std::move(reverse_descendant)),
            color_(n, 'w'), num_(n) {
        
        for (int i = 1; i < n; ++i) {
            if (color_[i] == 'w') {
                dfs(i);
            }
        }
        for (int i = 0; i < n - 1; ++i) {
            if (color_[p_[i]] == 'b') {
                dfsR(p_[i], csc_count_++);
            }
        }
        
        condensation_graph_.resize(csc_count_);

        for (int i = 1; i < n; ++i) {
            for (int v: descendant_[i]) {
                if (num_[i] != num_[v]) {
                    bool flag = false;
                    for (int k: condensation_graph_[num_[i]]) {
                        if (k == num_[v]) {
                            flag = true;
                        }
                    }
                    if (!flag) {
                        condensation_graph_[num_[i]].push_back(num_[v]);
                        edges_count_++;
                    }
                }
            }

        }
        std::cout << edges_count_;
    }
 
    ~Tree() {}
};

int main() {
    int n, m;
    std::cin >> n >> m;
    if (m == 0) {
        std::cout << 0;
        return 0;
    }
    ++n;
    vector<vector<int>> descendant(n), reverse_descendant(n);
    int from, to;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to;
        descendant[from].push_back(to);
        reverse_descendant[to].push_back(from);
    }
    Tree tree(descendant, reverse_descendant, n);
}

