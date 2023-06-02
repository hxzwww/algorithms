#include <iostream>
#include <vector>
 
using std::vector;
 
int main() {
    int n;
    std::cin >> n;
    std::string s;
    int N = n - n / 2;
    int M = n/2; 
    vector<long long> neN(N);
    vector<long long> neM(M);
    vector<long long> neNM(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> s;
        for (int j = 0; j < N; ++j) {
            if (s[j] == '1') {
                neN[i] = (neN[i] | (1 << j));
            }
        }
        for (int j = N; j < n; ++j) {
            if (s[j] == '1') {
                neNM[i] = (neNM[i] | (1 << (j - N)));
            }
        }
    }
    for (int i = N; i < n; ++i) {
          std::cin >> s;
          for (int j = N; j < n; ++j) {
              if (s[j] == '1') {
                  neM[i - N] = (neM[i - N] | (1 << (j - N)));
              }
          }
      }
    if (n == 1) {
        std::cout << 2;
        return 0;
    }
    //std::cout << neNM[0] << ' ' << neNM[2] << '\n';
    //////////////////////////////////
    vector<bool> dpN(1 << N, 0);
    for (int i = 0; i < N; ++i) {
        dpN[1 << i] = 1;
    }
    int v = -1, t;
    for (uint64_t mask = 1; mask < (1 << N); ++mask) {
        if (!(mask & (mask - 1))) {
            ++v;
        }
        t = mask ^ (1 << v);
        if (!((t | neN[v]) ^ neN[v])) {
            dpN[mask] = std::max(dpN[t], dpN[mask]);
        }
    }
    uint64_t co = 0;
    for (uint64_t i = 1; i < (1 << N); ++i) {
        co += dpN[i];
    }
    //std::cout << co << '\n';
    //////////////////////////////////
    vector<int> dpM(1 << M, 0);
    for (int i = 0; i < M; ++i) {
        dpM[1 << i] = 1;
    }
    v = -1;
    for (uint64_t mask = 1; mask < (1 << M); ++mask) {
        if (!(mask & (mask - 1))) {
            ++v;
        }
        t = mask ^ (1 << v);
        if (!((t | neM[v]) ^ neM[v])) {
            dpM[mask] = std::max(dpM[t], dpM[mask]);
        }
    }
 
    uint64_t count = 0;
    for (uint64_t i = 1; i < (1 << M); ++i) {
        count += dpM[i];
    }
    //std::cout << count << '\n';
    //////////////////////////////////
    vector<uint64_t> dp_(1 << N);
    dp_[0] = (1 << M) - 1;
    int oldest = -1;
    for (uint64_t i = 1; i < (1 << N); ++i) {
        if (!(i & (i - 1))) {
            ++oldest;
        }
        dp_[i] = (dp_[i ^ (1 << oldest)] & neNM[oldest]);
    }
    //////////////////////////////////
    for (int i = 0; i < M; ++i){
        for (uint64_t mask = 0; mask < (1 << M); ++mask) {
            if (!((mask >> i) & 1)) {
                dpM[mask | (1 << i)] += dpM[mask];
            }
        }
    }
    //////////////////////////////////
    for (uint64_t i = 1; i < (1 << N); ++i) {
        count += dpN[i] * (1 + dpM[dp_[i]]);
    }
    std::cout << count + 1 << '\n';
}
