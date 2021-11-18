#include <iostream>

void sort_bubble(int* mas, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (mas[j] > mas[j + 1]) {
                std::swap(mas[j], mas[j + 1]);
            }   
        }   
    }
}

int median(int* mas, int size) {

    if (size < 10) {
        sort_bubble(mas, size);
        return mas[size/2];
    }

    int* medians = new int [size / 5 + 4];
    int size_medians = 0;

    for (int i = 0; i < size - 4; i += 5) {
        sort_bubble(&mas[i], 5);
        medians[size_medians] = mas[i + 3];
        ++size_medians;
    }

    int result = median(medians, size_medians);
    delete [] medians;
    return result;
}

void qsort(int* mas, int size) {
    int i = 0;
    int j = size - 1;

    int pivot = median(mas, size);

    do {
        while(mas[i] < pivot) {
            i++;
        }
        while(mas[j] > pivot) {
            j--;
        }

        if (i <= j) {
            std::swap(mas[i], mas[j]);

            i++;
            j--;
        }
    } while (i <= j);

    if(j > 0) {
        qsort(mas, j + 1);
    }
    if (i < size) {
        qsort(&mas[i], size - i);
    }
}

int main() {
    std::ios_base::sync_with_stdio (false);

    int n;
    std::cin >> n;
    int* mas = new int [n];
    for (int i = 0; i < n; i++) {
        std::cin >> mas[i];
    }
    qsort(mas, n);
    for (int i = 0; i < n; i++) 
        std::cout << mas[i] << " ";
}
