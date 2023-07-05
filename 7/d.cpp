#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;

class Tree {
private:
    vector<vector<int>> descendant_;
    vector<int> tin_, tout_;
    vector<std::string> color_;
    int timer_ = 0;
    int size_;
    vector<std::pair<int, int>> pairs_to_sort;
    bool cycle_flag_ = false;

    void dfs(int v) {
       tin_[v] = timer_++;
       color_[v] = "grey";
       for (int to: descendant_[v]) {
           if (color_[to] == "grey") {
               cycle_flag_ = true;
               return;
           }
           if (color_[to] != "white") {
               continue;
           }
           dfs(to);
       }
       tout_[v] = timer_++;
       color_[v] = "black";
    }

    void top_sort() {
        for (int i = 1; i < size_; ++i) {
            if (color_[i] == "white") {
                dfs(i);
            }
        }
        if (cycle_flag_) {
            std::cout << -1;
            return;
        }
        for (int i = 1; i < size_; ++i) {
            pairs_to_sort.push_back(std::make_pair(tout_[i], i));
        }
        std::sort(pairs_to_sort.begin(), pairs_to_sort.end());
        std::reverse(pairs_to_sort.begin(), pairs_to_sort.end());
    }

public:
    Tree(vector<vector<int>>& descendant, int n) : descendant_(descendant), 
    color_(n, "white"), tin_(n), tout_(n), size_(n) {
        top_sort();
    }
    
    void print_sorted() {
        for (auto i: pairs_to_sort) {
            std::cout << i.second << ' ';
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
    }
    Tree tree(descendant, n);
    tree.print_sorted();
}
