#include <iostream>
#include <vector>
#include <queue>
using std::vector;

int64_t h;
int64_t a, b, c;
int64_t ans = 0;

void deikstr() {
    std::priority_queue<int64_t, vector<int64_t>, std::greater<int64_t>> q;
    vector<int64_t> dist(a, h + 1);
    q.push(1);
    while (!q.empty()) {
        int64_t v = q.top();
        q.pop();
        if (v > h) {
            continue;
        }
        if (dist[v % a] == h + 1) {
            dist[v % a] = v;
            ans += (h - v) / a + 1;
        } else {
            continue;
        }
        if (a != b) q.push(v + b);
        if (a != c && b != c) q.push(v + c);
    }
}

int main() {
    std::cin >> h >> a >> b >> c;
    if (a > b) {
        std::swap(a, b);
    }
    if (a > c) {
        std::swap(a, c);
    }
    deikstr();
    std::cout << ans;
}

