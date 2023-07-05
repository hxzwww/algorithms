#include <iostream>
#include <cstdio>
#include <vector>

class Stars {

private:

    std::vector<std::vector<std::vector<long long>>> space;
    std::vector<std::vector<std::vector<int>>> stars;
    int size;

public:
    
    Stars(int n) {
        for (int i = 0; i < n; ++i) {
            std::vector<std::vector<int>> a;
            std::vector<std::vector<long long>> b;
            for (int j = 0; j < n; ++j) {
                std::vector<int> c;
                std::vector<long long> d;
                c.resize(n, 0);
                d.resize(n, 0);
                a.push_back(c);
                b.push_back(d);
            }
            stars.push_back(a);
            space.push_back(b);
        }
        size = n;
    }
    
    ~Stars() {
        space.clear();
        stars.clear();
    }

    int f(int i) {
        return i & (i+1);
    }

    int g(int i) {
        return i | (i+1);
    }
    
    void append(int x, int y, int z, int val) {
        stars[x][y][z] += val;
        update(x, y, z, val);
    }

    void update(int x, int y, int z, int val) {
        for (int i = x; i < size; i = g(i)) {
            for (int j = y; j < size; j = g(j)) {
                for (int k = z; k < size; k = g(k)) {
                    space[i][j][k] += val;
                }
            }
        }
    }

    long long count(int x1, int y1, int z1, int x2, int y2, int z2) {
        long long ans = 0;
        ans += pref_sum(x2, y2, z2);
        ans -= pref_sum(x1-1, y2, z2);
        ans -= pref_sum(x2, y1-1, z2);
        ans -= pref_sum(x2, y2, z1-1);
        ans += pref_sum(x1-1, y1-1, z2);
        ans += pref_sum(x1-1, y2, z1-1);
        ans += pref_sum(x2, y1-1, z1-1);
        ans -= pref_sum(x1-1, y1-1, z1-1);
        return ans;
    }

    long long pref_sum(int x, int y, int z) {
        long long ans = 0;
        for (int i = x; i >= 0; i = f(i)-1) {
            for (int j = y; j >= 0; j = f(j)-1) {
                for (int k = z; k >= 0; k = f(k)-1) {
                    ans += space[i][j][k];
                }
            }
        }
        return ans;
    }
};

int main() {
    int n;
    scanf("%d", &n);
    Stars stars(n);
    while (true) {
        int m;
        scanf("%d", &m);
        if (m == 1) {
            int x, y, z, k;
            scanf("%d%d%d%d", &x, &y, &z, &k);
            stars.append(x, y, z, k);
        }
        if (m == 2) {
            int x1, y1, z1, x2, y2, z2;
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            printf("%lld\n", stars.count(x1, y1, z1, x2, y2, z2));
        }
        if (m == 3) {
            break;
        }
    }
}

