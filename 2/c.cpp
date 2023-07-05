#include <iostream>

int partition(int* arr, int left, int right, int pIndex) {
    int pivot = arr[pIndex];
    std::swap(arr[pIndex], arr[right]);
    pIndex = left;
    for (int i = left; i < right; i++) {
        if (arr[i] <= pivot) {
            std::swap(arr[i], arr[pIndex]);
            pIndex++;
        }
    }
    std::swap(arr[pIndex], arr[right]);
    return pIndex;
}

int quickSelect(int* arr, int left, int right, int k) {
    while (left != right) {

        int pIndex = left + rand() % (right - left + 1);
        pIndex = partition(arr, left, right, pIndex);
        if (k == pIndex) {
            return arr[k];
        }
        else if (k < pIndex) {
            right =  pIndex - 1;
        }
        else {
            left =  pIndex + 1;
        }
        if (left == right) {
            break;
        }
    }   
    return arr[left];
}

int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    int* mas = new int[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &mas[i]);
    }
    printf("%d\n", quickSelect(mas, 0, N - 1, K));
    delete [] mas;
}

