#include <iostream>
#include <vector>

using vvll = std::vector<std::vector<long long>>;
using vll = std::vector<long long>;

const int mod = 1e9 + 7;

bool is_3k(int64_t x) {                                                           
    int c = 0;                                                                  
    while (x) {                                                              
        c += (x & 1);                                                        
        x >>= 1;                                                             
    }                                                                           
    return !(c % 3);                                                                   
}

vvll mul(vvll& a, vvll& b, int r) {                                      
    vvll c(r, vll(r, 0));                                         
    for (int i = 0; i < r; ++i) {                                               
        for (int j = 0; j < r; ++j) {                                           
            for (int k = 0; k < r; ++k) {                                       
                c[i][j] += a[i][k] * b[k][j];                                   
                c[i][j] %= mod;                                                 
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
    int n;
    long long k;
    std::cin >> n >> k;
    vll a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    vvll mat(n, vll(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat[i][j] = is_3k(a[i] ^ a[j]);
        }
    }
    mat = binpow(mat, k - 1, n);
    int64_t answ = 0; 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            answ += mat[i][j];
            answ %= mod;
        }
    }
    std::cout << answ;
}

