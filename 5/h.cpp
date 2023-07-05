#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

void count(std::string& seq1, std::string& seq2) {
    int n = seq1.size();
    int m = seq2.size();
    seq1 = "z" + seq1;
    seq2 = "x" + seq2;
    vector<int> dp1(m + 1, 0);
    vector<int> dp2(m + 1, 0);
    vector<vector<bool>> r(n + 1, vector<bool>(m + 1, 0));
    vector<vector<bool>> p(n + 1, vector<bool>(m + 1, 0));
    vector<vector<bool>> rp(n + 1, vector<bool>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (seq1[i] == seq2[j]) {
                dp2[j] = dp1[j - 1] + 1;
                rp[i][j] = 1;
            } else {
                dp2[j] = std::max(dp2[j - 1], dp1[j]);
                if (dp2[j - 1] > dp1[j]) {
                    r[i][j] = 1;
                }
                else {
                    p[i][j] = 1;
                }
            }
        }
        dp1 = dp2;
    }
    int i = n, j = m;
    std::string ans;
    while (i > 0 && j > 0) {
        if (r[i][j]) {
            --j;
        }
        if (p[i][j]) {
            --i;
        }
        if (rp[i][j]) {
            ans += seq1[i];
            --i;
            --j;
        }
    }
    for (int i = 0; i < dp1[m]; ++i) {
        std::cout << ans[dp1[m] - 1 - i];
    }
}

int main() {
    std::string s1, s2;
    std::cin >> s1 >> s2;
    count(s1, s2);
}

