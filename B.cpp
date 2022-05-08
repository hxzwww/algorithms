#include <iostream>
#include <vector>

using std::vector;

class Tree {
private:
    vector<vector<int>> descendant;
    vector<int> tin, tout;
    vector<std::string> color;
    int timer = 0;

public:
    Tree(vector<vector<int>>& descendant, int n) : descendant(descendant), 
    color(n, "white"), tin(n), tout(n) {}

    void dfs(int v) {
       tin[v] = timer++;
       color[v] = "grey";
       for (int to: descendant[v]) {
           if (color[to] != "white") {
               continue;
           }
           dfs(to);
       }
       tout[v] = timer++;
       color[v] = "black";
    }

    bool is_ancestor(int a, int b) {
        return (tin[a] < tin[b]) & (tout[a] > tout[b]);
    }

    ~Tree() {}
};

int main() {
    int n;
    std::cin >> n;
    ++n;
    vector<vector<int>> descendant(n);
    int read;
    for (int i = 1; i < n; ++i) {
        std::cin >> read;
        descendant[read].push_back(i);
    }
    Tree tree(descendant, n);
    tree.dfs(0);
    int m;
    std::cin >> m;
    int a, b;
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b;
        std::cout << tree.is_ancestor(a, b) << '\n';
    }
}
