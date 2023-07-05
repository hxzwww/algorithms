#include <iostream>
#include <cstdio>
long long a[200000];

int main() {
    long long n, p, q;
    scanf("%lld%lld%lld", &n, &p, &q);
    long long left = 0, right = 0;
    for (long long i = 0; i < n; i++)
    {
        scanf("%lld", &a[i]);
        right = std::max(a[i], right);
    }
    if (p != q) {
        long long m, c;
        while (right > left + 1) {
            m = (right + left) / 2 ;
            c = 0;
            for (long long i = 0; i < n; i++) {
                    if (a[i] > q*m) c += (a[i]-q*m) / (p-q) + (((a[i]-q*m) % (p-q) == 0)?0:1);
            }
            if (c <= m) {
                right = m;
            }
            else {
                left = m;
            }
        }
    }
    else{
        right = 0;
        for (long long i = 0; i < n; i++)
            right = std::max(right, a[i]/p + ((a[i]%p==0)?0:1));
    }
    std::cout << right << "\n";
}
