#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
using std::vector;
using std::queue;
using std::string;

const long long mod = 10000;

struct node {
    vector<long long> to;
    bool term = false;
    long long link = -1;
    node() {
    	to.assign(26, -1);
	}
};

long long n, t;
vector<node> trie;

void add(const string& str) {
	if (trie.empty()) {
		trie.push_back(node());
	}
	long long v = 0;
	for (long long i = 0; i < str.size(); ++i) {
		long long index = str[i] - 'a';
		if (trie[v].to[index] == -1) {
			trie[v].to[index] = trie.size();
			trie.push_back(node());
		}
		v = trie[v].to[index];
	}
	trie[v].term = true;
}

void count() {
	trie[0].link = 0;
	for (long long c = 0; c < 26; ++c) {
		if (trie[0].to[c] == -1) {
			trie[0].to[c] = 0;
		}
	}
	queue<long long> q;
	q.push(0);
	while (!q.empty()) {
		long long v = q.front();
		q.pop();
		for (long long c = 0; c < 26; ++c) {
			long long u = trie[v].to[c];
			if (trie[u].link != -1) continue;
			trie[u].link = (v == 0 ? 0 : trie[trie[v].link].to[c]);
			for (long long d = 0; d < 26; ++d) {
				if (trie[u].to[d] == -1) trie[u].to[d] = trie[trie[u].link].to[d];
			}
			q.push(u);
		}
	}
}

long long solve() {
    count();

	vector<vector<long long>> spam(n + 1, vector<long long>(trie.size(), 0));
    vector<vector<long long>> not_spam(n + 1, vector<long long>(trie.size(), 0));
    not_spam[0][0] = 1;

    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < trie.size(); ++j) {
            for (auto v: trie[j].to) {
                long long u = v;
                while (u && !trie[u].term) {
                    u = trie[u].link;
                }
                spam[i + 1][v] = (spam[i + 1][v] + spam[i][j]) % mod;
                if (u) {
                    spam[i + 1][v] = (spam[i + 1][v] + not_spam[i][j]) % mod;
                } else {
                    not_spam[i + 1][v] = (not_spam[i + 1][v] + not_spam[i][j]) % mod;
                }
            }
        }
    }

	return std::accumulate(spam[n].begin(), spam[n].end(), (long long)0) % mod;
}

int main() {
	std::cin >> n >> t;

    string read;
    for (long long i = 0; i < t; ++i) {
		std::cin >> read;
		add(read);
    }

	std::cout << solve();
}

