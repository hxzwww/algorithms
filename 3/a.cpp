#include <iostream>
#include <cstdio>

class SegmentTree {

    private:
        
        struct Tree {
            int tl = 0;
            int tr = 0;
            int min = 0;
            int max = 0;
        };

        Tree* tree;
        int* pointer;

    public:

        SegmentTree() {
            tree = new Tree [262143];
            pointer = new int [100001];
            fill_tree(1, 1, 100000);
        }

        ~SegmentTree() {
            delete [] tree;
            delete [] pointer;
        }

        void fill_tree(int i, int left, int right) {
            tree[i].tl = left;
            tree[i].tr = right;
            tree[i].min = 0;
            tree[i].max = 0;
            if (left != right) {
                int mid = (left + right) >> 1;
                fill_tree(i*2, left, mid);
                fill_tree(i*2+1, mid+1, right);
            }
            else {
                tree[i].min = function(tree[i].tl);
                tree[i].max = function(tree[i].tl);
                pointer[tree[i].tl] = i;
                update(i);
            }
        }

        void update(int i) {
            if (tree[i/2].max == 0 && tree[i/2].min == 0) {
                tree[i/2].max = tree[i].max;
                tree[i/2].min = tree[i].min;
            }
            else {
                if (i % 2 == 0) {
                    tree[i/2].max = std::max(tree[i].max, tree[i+1].max);
                    tree[i/2].min = std::min(tree[i].min, tree[i+1].min);
                    }
                else {
                    tree[i/2].max = std::max(tree[i].max, tree[i-1].max);
                    tree[i/2].min = std::min(tree[i].min, tree[i-1].min);
                }
            }
            if (i/2 == 1) {
                return;
            }
            else {
                update(i/2);
            }
        }

        int function(int num) {
            long long n = long(num);
            return int((n*n % 12345) + (n*n*n % 23456));
        }

        int get_min(int i, int tl, int tr, int l, int r) {
            if (tl == l && tr == r) {
                return tree[i].min; 
            }
            int tm = (tl + tr) >> 1;
            int min = 1e9;
            if (l <= tm) {
                min = get_min(i*2, tl, tm, l, std::min(r, tm));
            }
            if (r >= tm + 1) {
                min = std::min(min, get_min(i*2+1, tm+1, tr, std::max(tm+1, l), r));
            }
            return min;
        }

        int get_max(int i, int tl, int tr, int l, int r) {
            if (tl == l && tr == r) {
                return tree[i].max;
            }
            int tm = (tl + tr) >> 1;
            int max = -1e9;
            if (l <= tm) {
                max = get_max(i*2, tl, tm, l, std::min(r, tm));
            }
            if (r >= tm + 1) {
                max = std::max(max, get_max(i*2+1, tm+1, tr, std::max(tm+1, l), r));
            }
            return max;
        }

        int get_diff(int x, int y) {
            return get_max(1, 1, 100000, x, y) - get_min(1, 1, 100000, x, y);
        }

        void give_val(int x, int y) {
            tree[pointer[x]].min = y;
            tree[pointer[x]].max = y;
            update(pointer[x]);
        }
};

int main() {
    int k;
    scanf("%d", &k);
    SegmentTree tree;
    for (int i = 0; i < k; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x > 0) {
            printf("%d\n", tree.get_diff(x, y));
        }
        else {
            tree.give_val(-x, y);
        }
    }
}

