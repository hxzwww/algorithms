#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using std::queue;
using std::string;
using std::vector;

class Trie {
public:
  Trie();
  void add(const string& /*str*/, int /*index*/);
  vector<vector<int>> solve(const string& /*text*/, int /*n*/);

private:
  static const int kSigma = 26;
  struct Node {
    vector<int> to;
    bool term;
    int len, link, compressedlink;
    vector<int> indexes;
    Node();
  };
  vector<Node> trie;
  void count();
};

Trie::Node::Node() : term(false), len(0), link(-1), compressedlink(-1) {
  to.resize(kSigma, -1);
}

Trie::Trie() {}

void Trie::add(const string& str, int index) {
  if (trie.empty()) {
    trie.push_back(Node());
  }
  int v = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    int index = str[i] - 'a';
    if (trie[v].to[index] == -1) {
      trie[v].to[index] = trie.size();
      trie.push_back(Node());
    }
    v = trie[v].to[index];
  }
  trie[v].term = true;
  trie[v].len = str.size();
  trie[v].indexes.push_back(index);
}

void Trie::count() {
  trie[0].link = 0;
  trie[0].compressedlink = 0;
  for (int c = 0; c < kSigma; ++c) {
    if (trie[0].to[c] == -1) {
      trie[0].to[c] = 0;
    }
  }
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int c = 0; c < kSigma; ++c) {
      int u = trie[v].to[c];
      if (trie[u].link != -1) {
        continue;
      }
      trie[u].link = (v == 0 ? 0 : trie[trie[v].link].to[c]);
      trie[u].compressedlink =
        (trie[trie[u].link].term ? trie[u].link
                                 : trie[trie[u].link].compressedlink);
      for (int d = 0; d < kSigma; ++d) {
        if (trie[u].to[d] == -1) {
          trie[u].to[d] = trie[trie[u].link].to[d];
        }
      }
      q.push(u);
    }
  }
}

vector<vector<int>> Trie::solve(const string& text, int n) {
  count();
  vector<vector<int>> result(n, vector<int>(1));
  int v = 0;
  for (size_t i = 0; i < text.size(); ++i) {
    v = trie[v].to[text[i] - 'a'];
    int current = (trie[v].term ? v : trie[v].compressedlink);
    while (current != 0) {
      for (auto index : trie[current].indexes) {
        ++result[index][0];
        result[index].push_back(i - trie[current].len + 2);
      }
      current = trie[current].compressedlink;
    }
  }
  return result;
}

int main() {
  string text;
  int n;
  std::cin >> text >> n;
  Trie trie;
  string read;
  for (int i = 0; i < n; ++i) {
    std::cin >> read;
    trie.add(read, i);
  }
  for (auto array : trie.solve(text, n)) {
    std::sort(array.begin() + 1, array.end());
    for (auto element : array) {
      std::cout << element << ' ';
    }
    std::cout << '\n';
  }
}

