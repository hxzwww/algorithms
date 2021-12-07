#include <iostream>
#include <cstdio>

class Strange {

private:

    struct node {
        long long sum = 0;
        int tl = 0, tr = 0;
        node* left = nullptr;
        node* right = nullptr;
    };

    int size;
    node* first; 

public:

    Strange() {
        first = new node;
        first->sum = 0;
        first->tl = 0;
        first->tr = 1e9 - 1;
        first->left = nullptr;
        first->right = nullptr;
    }

    ~Strange() {
        delete_tree(first);
    }

    void delete_tree(node* current) {
        if (current->left) {
            delete_tree(current->left);
        }
        if (current->right) {
            delete_tree(current->right);
        }
        delete current;
    }

    void update(node* current, int val) {
        if (current->tl == val && current->tr == val) {
            return;
        }
        int tm = (current->tl + current->tr) >> 1;
        if (val <= tm) {
            if (current->left == nullptr) {
                node* left = new node;
                left->sum = val;
                left->tl = current->tl;
                left->tr = tm;
                current->left = left;
            }
            else {
                current->left->sum += val;
            }
            update(current->left, val);
        }
        if (val >= tm + 1) {
            if (current->right == nullptr) {
                node* right = new node;
                right->sum = val;
                right->tl = tm + 1;
                right->tr = current->tr;
                current->right = right;
            }
            else {
                current->right->sum += val;
            }
            update(current->right, val);
        }
    }

    void add(int val) {
        first->sum += val;
        update(first, val);
    }

    long long get_sum(int val) {
        return sum(first, val);
    }

    long long sum(node* current, int val) {
        if (current->tr <= val) {
            return current->sum;
        }
        long long ans = 0;
        int tm = (current->tl + current->tr) >> 1;
        if (val >= tm) {
            if (current->left) {
                ans += current->left->sum;
            }
            if (val >= tm+1 && current->right) {
                ans += sum(current->right, val);
            }
        }
        else {
            if (current->left) {
                ans += sum(current->left, val);
            }
        }
        return ans;
    }
};

int main() {
    int n;
    scanf("%d", &n);
    Strange strange;
    for (int i = 0; i < n; ++i) {
        char cmd;
        int num;
        std::cin >> cmd >> num;
        if (cmd == '+') {
            strange.add(num);
        }
        if (cmd == '?') {
            printf("%lld\n", strange.get_sum(num));
        }
    }
}
