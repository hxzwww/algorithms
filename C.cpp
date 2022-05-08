#include <iostream>
#include <string>
#include <vector>
#include <deque>

using std::vector;

class Graph {
private:
    vector<int>* descendant;
    vector<char> color;
    vector<int> parent;
    std::deque<int> cycle;
    int n;
    int start = 0, end = 0;

    bool dfs(int v, int p = -1) {
        color[v] = 'g';
        parent[v] = p;
        for (int to: descendant[v]) {
            if (color[to] == 'w' && dfs(to, v)) {
                return true;
            } 
            if (color[to] == 'g') {
                parent[to] = v;
                end = v;
                return true;
            }
        }
        color[v] = 'b';
        return false;

    }

public:
    Graph(vector<int>* descendant, int n) : descendant(descendant), 
    color(n, 'w'), parent(n, 0), n(n) {}

    std::string find_cycle() {
        for (int i = 1; i < n; ++i) {
              if (color[i] == 'w' && dfs(i)) {
                  std::string answer = "YES\n";
                  cycle.push_front(end);
                  int tmp = end;
                  while (parent[tmp] != end) {
                      cycle.push_front(parent[tmp]);
                      tmp = parent[tmp];
                  }
                  for (int i: cycle) {
                      answer += std::to_string(i) + ' ';
                  }
                  return answer;
              }
          }
          return "NO\n";
    }

    ~Graph() {
        delete [] descendant;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    ++n;
    vector<int>* descendant = new vector<int> [n];
    int from, to;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to;
        descendant[from].push_back(to);
    }
    Graph graph(descendant, n);
    std::cout << graph.find_cycle();
}
