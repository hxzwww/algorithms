#include <iostream>
#include <vector>

using std::vector;
using vvll = vector<vector<long long>>;
using vll = vector<long long>;

vvll mul(vvll a, vvll b, int r, int mod) {                                               
    vvll c(r, vector<long long>(r, 0));                                         
    for (int i = 0; i < r; ++i) {                                               
        for (int j = 0; j < r; ++j) {                                           
            for (int k = 0; k < r; ++k) {                                       
                c[i][j] += a[i][k] * b[k][j];                                   
                c[i][j] %= mod;                                              
            }                                                                   
        }                                                                       
    }                                                                           
    return  c;                                                                  
}                                                                               

vvll one(int c) {                                                               
    vvll a(c, vll(c));                                                          
    for (int i = 0; i < c; ++i) {                                               
        a[i][i] = 1;                                                            
    }                                                                           
    return a;                                                                   
}                                                                                   

vvll binpow(vvll& a, long long n, int c, int mod) {                                      
    if (n == 0)                                                                 
        return one(c);                                                          
    if (n & 1)                                                                  
        return mul(binpow(a, n - 1, c, mod), a, c, mod);                                  
    else {                                                                      
        vvll t = binpow(a, n / 2, c, mod);                                           
        return mul(t, t, c, mod);                                                    
    }                                                                           
}

bool check(int mask1, int mask2) {                                              
    int last = -1;                                                              
    while (mask1 && mask2) {                                                    
        if (mask1 == 1 && mask2 == 1) {                                         
            return true;                                                        
        }                                                                       
        if ((mask2 & 1) == last && (mask1 & 1) == last) {                       
            return false;                                                       
        }                                                                       
        if ((mask1 & 1) == (mask2 & 1)) {                                       
            last = mask1 & 1;                                                   
        } else {                                                                
            last = -1;                                                          
        }                                                                       
        mask1 >>= 1;                                                            
        mask2 >>= 1;                                                            
    }                                                                           
    return true;                                                                
} 

int main() {
    int64_t n;
    int m, t, mod;
    std::cin >> t;
    for (int q = 0; q < t; ++q) {
        std::cin >> n >> m >> mod;
        vvll mat(1 << m, vll(1 << m));
        for (int i = 0; i < (1 << m); ++i) {
            for (int j = 0; j < (1 << m); ++j) {
                mat[i][j] = check((1 << m) | i, (1 << m) | j);
            }
        }
        mat = binpow(mat, n - 1, (1 << m), mod);
        vll dp(1 << m, 1);
        int64_t answ = 0;
        for (int i = 0; i < (1 << m); ++i) {
            for (int j = 0; j < (1 << m); ++j) {
                answ += mat[i][j] * dp[j];
                answ %= mod;
            }
        }
        std::cout << answ << '\n'; 
    }
}

