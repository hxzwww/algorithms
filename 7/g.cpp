#include <iostream>
#include <vector>

using std::vector;

class Tree {
private:
    vector<vector<int>> descendant_;
    vector<bool> used_;
    vector<int> csc_;
    int csc_count_ = 0;

    void dfs(int v, int val) {
        csc_[v] = val;
        used_[v] = true;
        for (int to: descendant_[v]) {
            if (used_[to]) {
                continue;
            } 
            dfs(to, val);
        }
    }

public:
    Tree(vector<vector<int>>& descendant, int n) : descendant_(descendant), 
    used_(n, false), csc_(n){
    
        int csc = 0;
        for (int i = 1; i < n; ++i) {
            if (!used_[i]) {
                dfs(i, ++csc);
            }
        }
        
        std::cout << csc << '\n';
        for (int i = 1; i < n; ++i) {
            std::cout << csc_[i] << ' ';
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

