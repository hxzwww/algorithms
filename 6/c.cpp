#include <iostream>
#include <type_traits>
#include <vector>

using vvll = std::vector<std::vector<long long>>;
using vll = std::vector<long long>;

const int module = 1e9 + 7;

vvll mul(vvll& a, vvll& b, int r) {                                             
    vvll c(r, vll(r, 0));                                                       
    for (int i = 0; i < r; ++i) {                                               
        for (int j = 0; j < r; ++j) {                                           
            for (int k = 0; k < r; ++k) {                                       
                c[i][j] += a[i][k] * b[k][j];                                   
                c[i][j] %= module;                                                 
            }                                                                   
        }                                                                       
    }                                                                           
    return c;                                                                   
}                                                                               
                                                                                
vvll one(int c) {                                                               
    vvll a(c, vll(c));                                                          
    for (int i = 0; i < c; ++i) {                                               
        a[i][i] = 1;                                                            
    }                                                                           
    return a;                                                                   
}                                                                               
                                                                                
vvll binpow(vvll& a, long long n, int c) {                                      
    vvll t;                                                                     
    if (n == 0)                                                                 
        return one(c);                                                          
    if (n & 1) {                                                                
        t = binpow(a, n - 1, c);                                                
        return mul(t, a, c);                                                    
    }                                                                           
    else {                                                                      
        t = binpow(a, n / 2, c);                                                
        return mul(t, t, c);                                                    
    }                                                                           
}  

int main() {
    std::ios_base::sync_with_stdio(0);
    int64_t n, m, l;
    std::cin >> n >> l >> m;
    vll first(n);
    vll neigh(n);
    vll last(n);
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> first[i];
    }
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> neigh[i];
    }
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> last[i];
    }
    vll dp(m);
    for (int64_t i = 0; i < n; ++i) {
        ++dp[first[i] % m];
    }
    vvll mat(m, vll(m));
    for (int64_t i = 0; i < m; ++i) {
        for (int64_t j = 0; j < n; ++j) {
            ++mat[i][(m + i - neigh[j]) % m];
        }
    }
    mat = binpow(mat, l - 2, m);
    vll tmp(m);
    for (int64_t i = 0; i < m; ++i) {                                           
        for (int64_t j = 0; j < m; ++j) {                                       
            tmp[i] += mat[i][j] * dp[j];                                    
            tmp[i] %= module;                                               
        }                                                                   
    }
    int64_t answ = 0;
    for (int64_t j = 0; j < n; ++j) {
        answ += tmp[(3 * m - neigh[j] - last[j]) % m];
        answ %= module;
    }
    std::cout << answ;



}

