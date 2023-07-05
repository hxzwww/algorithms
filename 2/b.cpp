#include <iostream>

void qsort(int *mas, int size) {
    int i = 0;
    int j = size - 1;
    int mid = mas[size / 2];
    do {
        while(mas[i] < mid) {
            i++;
        }
        while(mas[j] > mid) {
            j--;
        }
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0) {
        qsort(mas, j + 1);
    }
    if (i < size) {
        qsort(&mas[i], size - i);
    }
}

int main() {
    int n;
    std::cin >> n;
    int* l = new int[n + 1];
    int* r = new int[n];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &l[i], &r[i]);
    }
    qsort(l, n);
    qsort(r, n);
    l[n] = r[n - 1] + 1;
    int ans = 0, layerNum = 0, iL = 0, iR = 0;
    while (iL <= n && iR < n) {

        if (l[iL] < r[iR]) {
            layerNum++;
            if (layerNum == 1) {
                ans += std::min(((iL + 1 < n) ? l[iL + 1] : r[iR]), r[iR]) - l[iL];
            }
            iL++;
        }

        if (l[iL] > r[iR]) {
            layerNum--;
            if (layerNum == 1) {
                ans += std::min(r[iR + 1], l[iL]) - r[iR];
            }
            iR++;
        }

        if (l[iL] == r[iR]) {

            iR++;
            layerNum--;
        }

    }
    std::cout << ans << "\n";
}
