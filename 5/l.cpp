#include <iostream>
#include <vector>

bool bit(int mask, int pos) {
    return (mask >> pos) & 1;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<long long> nums1(n / 2);
    std::vector<long long> nums2(n - n / 2);
    for (long long i = 0; i < n / 2; ++i) {
        std::cin >> nums1[i];
    }
    for (long long i = 0; i < n - n / 2; ++i) {
        std::cin >> nums2[i];
    }
    long long C;
    std::cin >> C;
    long long s = 1 << (n / 2), ss = 1 << (n - n / 2);
    std::vector<long long> dp1(s, 0);
    std::vector<long long> dp2(ss, 0);
    long long ans = 0;
    for (long long mask = 1; mask < s; ++mask) {
        for (long long i = 0; i < n / 2; ++i) {
            if (bit(mask, i)) {
                dp1[mask] += nums1[i];
            }
        }
    }
    for (long long mask = 1; mask < ss; ++mask) {
        for (long long i = 0; i < n - n / 2; ++i) {
            if (bit(mask, i)) {
                dp2[mask] += nums2[i];
            }
        }
    }
    for (long long i = 0; i < s; ++i) {
        for (long long j = 0; j < ss; ++j) {
            if (dp1[i] + dp2[j] <= C) {
                ++ans;
            }
        }
    }
    std::cout << ans;
}

