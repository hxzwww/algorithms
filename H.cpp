#include <iostream>
#include <cstdio>

const int len = 256;

unsigned long long bytePart(int part, unsigned long long num) {
    
    return (num >> (8 * (part - 1))) % len;
}
 
unsigned long long* lsdSort(unsigned long long* array, int size) {

    unsigned long long* answer = new unsigned long long [size + 1];

    for (int i = 1; i <= 8; i++) {
 
        int* cnt = new int [len];
 
        for (int k = 0; k < len; k++) {
            cnt[k] = 0;
        }
 
        for (int k = 0; k < size; k++) {
            cnt[bytePart(i, array[k])]++;
        }
        for (int k = 1; k < len; k++) {
            cnt[k] += cnt[k - 1];
        }
        for (int k = size - 1; k >= 0; k--) {
            answer[cnt[bytePart(i, array[k])]--] = array[k];
        }
 
        for (int k = 1; k <= size; k++) {
            array[k - 1] = answer[k];
        }
 
        delete [] cnt;
    }

    return answer;
}
 
 
int main() {
 
    int size = 0;
    std::cin >> size;
 
    unsigned long long* array = new unsigned long long [size];
 
    for (int i = 0; i < size; ++i) {
        scanf("%llu", &array[i]);
    }
 
    array = lsdSort(array, size);
 
    for (int i = 1; i <= size; i++) {
        printf("%llu ", array[i]);
    }
 
    delete [] array;
}
