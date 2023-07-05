#include <iostream>
#include <cstdio>

class Canvas {

private:

    struct Tree {
        int tl = 0;
        int tr = 0;
        int min = 0;
        int prom = -1;
    };

    Tree* tree;
    int* pointer;
    int* arr;
    int size = 0;

public:

    Canvas(int k, int* mas) {
        size = k;
        tree = new Tree [tree_size()];
        pointer = new int [size + 2];
        arr = mas;
        fill_tree(1, 1, size);
        fill_nums();
    }

    int tree_size() {
        int i = 0;
        while (1<<i < size) {
            ++i;
        }
        return 1<<(i+1);
    }

    ~Canvas() {
        delete [] tree;
        delete [] pointer;
        delete [] arr;
    }

    void fill_tree(int i, int left, int right) {
        tree[i].tl = left;
        tree[i].tr = right;
        tree[i].min = 0;
        if (left != right) {
            int mid = (left + right) >> 1;
            fill_tree(i*2, left, mid);
            fill_tree(i*2+1, mid+1, right);
        }
        else {
            tree[i].min = arr[tree[i].tl];
            pointer[tree[i].tl] = i;
        }
    }

    void fill_nums() {
        for (int i = tree_size()-1; i >= 3; i-=2) {
            if (tree[i-1].tl == tree[i/2].tl && tree[i].tr == tree[i/2].tr)
                tree[i/2].min = std::min(tree[i-1].min, tree[i].min);
        }
    }

    void push(int i) {
        if (tree[i].prom == -1) {
            return;
        }
        tree[i*2].prom = tree[i].prom;
        tree[i*2+1].prom = tree[i].prom;
        tree[i*2].min = tree[i].prom;
        tree[i*2+1].min = tree[i].prom;
        tree[i].prom = -1;
    }

    void update(int i, int left, int right, int val) {
        if (tree[i].tl == left && tree[i].tr == right) {
            tree[i].prom = val;
            tree[i].min = val;
            return;
        }
        push(i);
        int tm = (tree[i].tl + tree[i].tr) >> 1;
        if (left <= tm) {
            update(i*2, left, std::min(right, tm), val);
        }
        if (right >= tm+1) {
            update(i*2+1, std::max(tm+1, left), right, val);
        }
        tree[i].min = std::min(tree[i*2].min, tree[i*2+1].min);
    }

    int paint(int c, int d, int rgb, int e, int f) {
        tree[pointer[c]].min = rgb;
        update(1, c, d, rgb);
        return get_min(1, e, f);
    }

    int get_min(int i, int left, int right) {
        if (tree[i].tl == left && tree[i].tr == right) {
            return tree[i].min;
        }
        int tm = (tree[i].tl + tree[i].tr) >> 1;
        int min = 1e9;
        push(i);
        if (left <= tm) {
            min = std::min(min, get_min(i*2, left, std::min(right, tm)));
        }
        if (right >= tm + 1) {
            min = std::min(min, get_min(i*2+1, std::max(tm+1, left), right));
        }
        return min;
    }
};

int main() {
    int N;
    scanf("%d", &N);
    int* mas = new int [N+1];
    for (int i = 1; i <= N; ++i) {
        int r, g, b;
        scanf("%d%d%d", &r, &g, &b);
        mas[i] = r+g+b;
    }
    Canvas tree(N, mas);
    int K;
    scanf("%d", &K);
    for (int i = 0; i < K; ++i) {
        int c, d, r, g, b, e, f;
        scanf("%d%d%d%d%d%d%d", &c, &d, &r, &g, &b, &e, &f);
        printf("%d ", tree.paint(c+1, d+1, r+g+b, e+1, f+1));
    }
}


