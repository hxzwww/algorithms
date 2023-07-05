#include <iostream>
#include <vector>

using std::vector;

bool not_2x2_square(int mask1, int mask2) {
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

long long solve(int n, int m) {
    long long answer = 0;
    vector<vector<long long>> dp(n, vector<long long>(1 << m));                 
    for (int i = 0; i < (1 << m); ++i) {                                        
        dp[0][i] = 1;                                                           
    }                                                                           
    for (int i = 1; i < n; ++i) {                                               
        for (int mask1 = 0; mask1 < (1 << m); ++mask1) {                        
            for (int mask2 = 0; mask2 < (1 << m); ++mask2) {                    
                if (not_2x2_square(mask1 | (1 << m), mask2 | (1 << m))) {                
                    dp[i][mask2] += dp[i - 1][mask1];                           
                }                                                               
            }                                                                   
        }                                                                       
    }                                                                           
    for (int i = 0; i < (1 << m); ++i) {                                        
        answer += dp[n - 1][i];                                                   
    }
    return answer;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    if (m > n) {
        std::swap(m, n);
    }
    std::cout << solve(n, m);
}

