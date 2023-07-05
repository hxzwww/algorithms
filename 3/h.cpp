#include <iostream>
#include <cstdio>

class SparseTable {

private:

    struct Table {
        int val = 0;
        int ind = 0;
    };

    Table** sparse;
    int size;
    int* arr;
    int log_size;

public:
    
    SparseTable(int n, int* mas) {
        size = n;
        log_size = log(n);
        sparse = new Table* [log_size+1];
        arr = mas;
        fill_sparse();
    }

    ~SparseTable() {
        delete [] arr;
        for (int i = 1; i <= log_size; ++i) {
            delete [] sparse[i];
        }
        delete [] sparse;
    }

    int log(int num){
        int i = 0;
        while (num) {
            ++i;
            num /= 2;
        }
        return i;
    }

    Table min(Table a, Table b) {
        if (a.val < b.val) {
            return a;
        }
        return b;
    }

    void fill_sparse() {
        sparse[0] = new Table [size];
        for (int i = 0; i < size; ++i) {
            sparse[0][i].val = arr[i];
            sparse[0][i].ind = i;
        }
        for (int k = 1; k <= log_size; ++k) {
            sparse[k] = new Table [size];
            for (int i = 0; i < size; ++i) {
                int ind = std::min(i + (1<<(k-1)), size - 1);
                sparse[k][i] = min(sparse[k-1][i], sparse[k-1][ind]);
            }
        }
    }

    int get_second(int left, int right) {
        Table min = get_min(left, right);
        if (min.ind == left) {
            return get_min(left+1, right).val;
        }
        if (min.ind == right) {
            return get_min(left, right-1).val;
        }
        return std::min(get_min(left, min.ind-1).val, get_min(min.ind+1, right).val);
    }

    Table get_min(int left, int right) {
        int degree = log(right - left + 1) - 1;
        return min(sparse[degree][left], sparse[degree][right - (1 << degree) + 1]);

    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int* arr = new int [n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    SparseTable sparse(n, arr);
    for (int i = 0; i < m; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", sparse.get_second(l-1, r-1));
    }
}

