#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

static const int64_t mod = 1000000007;

struct point {
    int64_t x;
    int64_t y;

    int64_t operator*(point other) {
        return x * other.y - y * other.x;
    }

    point operator-(point other) {
        return {x - other.x, y - other.y};
    }
};

vector<point> polygon;
vector<vector<bool>> visited;
vector<vector<int64_t>> dp;

int64_t get_area() {
    int64_t area = 0;
	size_t size = polygon.size();

    for (int i = 0; i < size; ++i) {
        area += polygon[i] * polygon[(i + 1) % size];
    }

    return area;
}

int64_t count_triangulations(int from, int to) {
    if (visited[from][to]) {
        return dp[from][to];
    }

    if (from + 1 == to) {
    	dp[from][to] = 1;
        return dp[from][to];
    }

    visited[from][to] = true;

    for (int i = from + 1; i < to; ++i) {
        if ((polygon[to] - polygon[from]) * (polygon[to] - polygon[i]) > 0) {
            dp[from][to] += count_triangulations(from, i) * count_triangulations(i, to);
            dp[from][to] %= mod;
        }
    }

    return dp[from][to];
}

int main() {
    int n;
    std::cin >> n;
	polygon.resize(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> polygon[i].x >> polygon[i].y;
    }

    size_t size = polygon.size();

    visited.assign(size, vector<bool>(size));
    dp.assign(size, vector<int64_t>(size));

    if (get_area() < 0) {
        std::reverse(polygon.begin() + 1, polygon.end());
    }

    std::cout << count_triangulations(0, size - 1);
}

