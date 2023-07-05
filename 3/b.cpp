#include <iostream>
#include <cstdio>
 
class SegmentTree {
 
    private:
 
        struct Tree {
            int tl = 0;
            int tr = 0;
            int sum = 0;
        };
 
        Tree* tree;
        int size = 0;
        int* pointer;
 
    public:
 
        SegmentTree(int k, int* mas) {
            size = k;
            tree = new Tree [tree_size()];
            pointer = new int [size + 2];
            fill_tree(1, 1, size, mas);
            fill_nums();
        }
 
        ~SegmentTree() {
            delete [] tree;
            delete [] pointer;
        }
 
        int tree_size() {
            int i = 0;
            while (1<<i < size) {
                ++i;
            }
            return 1<<(i+1);
        }
 
        void fill_tree(int i, int left, int right, int* mas) {
            tree[i].tl = left;
            tree[i].tr = right;
            if (left != right) {
                tree[i].sum = 0;
                int mid = (left + right) >> 1;
                fill_tree(i*2, left, mid, mas);
                fill_tree(i*2+1, mid+1, right, mas);
            }
            else {
                pointer[tree[i].tl] = i;
                tree[i].sum = ((tree[i].tl % 2 == 1) ? mas[tree[i].tl-1] : -mas[tree[i].tl-1]);
            }
        }
 
        void fill_nums() {
            for (int i = tree_size()-1; i >= 3; i-=2) {
                tree[i/2].sum += (tree[i-1].sum + tree[i].sum);
            }
        }
 
        void update(int i) {
            tree[i/2].sum = tree[i].sum;
            if (i%2 == 0) {
                tree[i/2].sum = tree[i].sum + tree[i+1].sum;
            }
            else {
                tree[i/2].sum = tree[i].sum + tree[i-1].sum;
            }
            if (i/2 == 1) {
                return;
            }
            else {
                update(i/2);
            }
        }
 
        int get_sum(int i, int tl, int tr, int l, int r) {
            if (tl == l && tr == r) {
                return tree[i].sum;
            }
            int tm = (tl + tr) >> 1;
            int sum = 0;
            if (l <= tm) {
                sum += get_sum(i*2, tl, tm, l, std::min(r, tm));
            }
            if (r >= tm + 1) {
                sum += get_sum(i*2+1, tm+1, tr, std::max(tm+1, l), r);
            }
            return sum;
        }
 
        void give_val(int i, int j) {
            tree[pointer[i]].sum = ((tree[pointer[i]].tl % 2 == 1) ? j : -j);
            update(pointer[i]);
        }
};
 
int main() {
    int k;
    scanf("%d", &k);
    int* mas = new int [k];
    for (int i = 0; i < k; ++i) {
        scanf("%d", &mas[i]);
    }
    int m;
    scanf("%d", &m);
    SegmentTree tree(k, mas);
    delete [] mas;
    for (int i = 0; i < m; ++i) {
        int n, x, y;
        scanf("%d%d%d", &n, &x, &y);
        if (n) {
            printf("%d\n", tree.get_sum(1, 1, k, x, y) * ((x % 2 == 1) ? 1 : -1));
        }
        else {
            tree.give_val(x, y);
        }
    }
}
