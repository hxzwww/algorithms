#include <iostream>
#include <vector>

using std::vector;
using vvll = vector<vector<long long>>;                                         
using vll = vector<long long>;        

const int module = 1e9 + 7;

vvll mul(vvll a, vvll b, int r) {                                                      
    vvll c(r, vector<long long>(r, 0));                                         
    for (int i = 0; i < r; ++i) {                                               
        for (int j = 0; j < r; ++j) {                                           
            for (int k = 0; k < r; ++k) {                                       
                c[i][j] += a[i][k] * b[k][j];                                   
                c[i][j] %= module;                                              
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

vvll binpow(vvll& a, long long n, int c) {                                              
    if (n == 0)                                                                 
        return one(c);                        
    if (n & 1)                                                                  
        return mul(binpow(a, n - 1, c), a, c);                                        
    else {                                                                      
        vvll t = binpow(a, n / 2, c);                                              
        return mul(t, t, c);                                                       
    }                                                                           
} 

int main() {
    int n;
    long long k;
    std::cin >> n >> k;
    
    vll tmp(18, 0);
    vll dp(18, 0);
    dp[1] = -1;
    tmp[0] = 1;
    
    long long a, b = 0, c;

    for (int i = 0; i < n; ++i) {       
/////////
        if (b == k) {
            std::cin >> a >> b >> c;
            b = k;
            continue;
        }
        
        std::cin >> a >> b >> c;
        b = std::min(b, k);
        ++c;
        
/////////
        dp = tmp;
        for (int i = c; i < 18; ++i) {
            dp[i] = 0;
        }
        vvll mat(c, vll(c));

        for (int i = 0; i < c; ++i) {
            mat[i][i] = 1;
            if (i) {
                mat[i - 1][i] = 1;
            }
            if (i < c - 1) {
                mat[i + 1][i] = 1;
            }
        }

        mat = binpow(mat, (b - a), c);
        
        for (int i = 0; i < 18; ++i) {
            tmp[i] = 0;
        }

        for (int i = 0; i < c; ++i) {
            for (int j = 0; j < c; ++j) {
                tmp[i] += mat[i][j] * dp[j];
                tmp[i] %= module; 
            }
        }
    }
    std::cout << tmp[0];
}


















