#include <iostream>
#include <cstdio>

class MergeSortTree {

    private:
    
        struct Tree {
            int tl = 0;
            int tr = 0;
            int max = 0;
        };

        Tree* tree;
        int size = 0;
        int* array;
        int* pointer;

    public:

        MergeSortTree(int k, int* mas) {
            size = k;
            tree = new Tree [tree_size()];
            array = mas;
            pointer = new int [size + 1];
            fill_tree(1, 1, size);
        }

        ~MergeSortTree() {
            delete [] tree;
            delete [] array;
            delete [] pointer;
        }

        int tree_size() {
            int i = 0;
            while (1<<i < size) {
                ++i;
            }
            return 1<<(i+1);
        }

        void fill_tree(int i, int left, int right) {
            tree[i].tl = left;
            tree[i].tr = right;
            tree[i].max = 0;
            if (left != right) {
                int mid = (left + right) >> 1;
                fill_tree(i*2, left, mid);
                fill_tree(i*2+1, mid+1, right);
            }
            else {
                pointer[tree[i].tl] = i;
                tree[i].max = array[tree[i].tl];
                update(i);
            }
        }

        void update(int i) {
            tree[i/2].max = std::max(tree[i/2*2].max, tree[i/2*2+1].max);
            if (i/2 == 1) {
                return;
            }
            else {
                update(i/2);
            }
        }

        void set(int i, int x) {
            tree[pointer[i]].max = x;
            update(pointer[i]);
        }

        int get_sec_max(int i, int x) {
            return go_up(pointer[i], x);
        }

        int go_up(int i, int val) {

            if (i == 1) {
                return -1;
            }

            if (tree[i].tl == tree[i].tr && tree[i].max >= val) {
                return tree[i].tl;
            }

            if (i/2*2+1 == i) {
                return go_up(i/2, val);
            }

            if (tree[i/2*2+1].max >= val) {
                return go_down(i/2*2+1, val);
            }

            return go_up(i/2, val);
        }

        int go_down(int i, int val) {

            if (tree[i].max < val) {
                return -1;
            }

            if (tree[i].tl == tree[i].tr && tree[i].max >= val) {
                return tree[i].tl;
            }

            if (tree[i*2].max >= val) {
                return go_down(i*2, val);
            }
            else {
                return go_down(i*2+1, val);
            }
        }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int* mas = new int [n+1];
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &mas[i]);
    }
    MergeSortTree tree(n, mas);
    for (int j = 0; j < m; ++j) {
        int cmd, i, x;
        scanf("%d%d%d", &cmd, &i, &x);
        if (!cmd) {
            tree.set(i, x);
        }
        else {
            printf("%d\n", tree.get_sec_max(i, x));
        }
    }
}

