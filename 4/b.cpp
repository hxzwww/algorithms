#include <iostream>

struct node {
    node* left = nullptr;
    node* right = nullptr;
    unsigned long long sum = 0;
    int val = 2e9;
};

struct split_tree {
    node* left = nullptr;
    node* right = nullptr;
};

class Splay {

private:

    node* root;
    unsigned long long last_sum;

    void delete_tree(node* current) {
        if (current->left) {
            delete_tree(current->left);
        }
        if (current->right) {
            delete_tree(current->right);
        }
        delete current;
    }

    void update(node* cur, int x) {
        if (cur->val == x) {
            return;
        }
        if (x < cur->val) {
            cur->sum += x;
            if (cur->left) {
                update(cur->left, x);
            }
            else {
                cur->left = new node;
                cur->left->val = x;
                cur->left->sum = x;
            }
        }
        else {
            cur->sum += x;
            if (cur->right) {
                update(cur->right, x);
            }
            else {
                cur->right = new node;
                cur->right->val = x;
                cur->right->sum = x;
            }
        }
        choose_zig(cur, x);
    }

    void resum(node* cur) {
        cur->sum = cur->val;
        if (cur->left) cur->sum += cur->left->sum;
        if (cur->right) cur->sum += cur->right->sum;
    }
    
    void left_zig(node* cur) {
        std::swap(cur->val, cur->left->val);
        std::swap(cur->left, cur->right);
        std::swap(cur->right->left, cur->right->right);
        std::swap(cur->left, cur->right->right);
        resum(cur->right);
        resum(cur);
    }

    void right_zig(node* cur) {
        std::swap(cur->val, cur->right->val);
        std::swap(cur->left, cur->right);
        std::swap(cur->left->left, cur->left->right);
        std::swap(cur->right, cur->left->left);
        resum(cur->left);
        resum(cur);
    }

    void left_zig_zig(node* cur) {
        left_zig(cur);
        left_zig(cur);
    }

    void right_zig_zig(node* cur) {
        right_zig(cur);
        right_zig(cur);
    }

    void left_zig_zag(node* cur) {
        right_zig(cur->left);
        left_zig(cur);
    }

    void right_zig_zag(node* cur) {
        left_zig(cur->right);
        right_zig(cur);
    }

    void choose_zig(node* cur, int x) {
        if (cur == root) {
            if (cur->left && cur->left->val == x) {
                left_zig(cur);
                return;
            }
            if (cur->right && cur->right->val == x) {
                right_zig(cur);
                return;
            }
        }
        if (cur->left && cur->val > x) {
            if (cur->left->val == x) {
                return;
            }
            if (cur->left->left && cur->left->val > x) {
                left_zig_zig(cur);
                return;
            }
            if (cur->left->right && cur->left->val < x) {
                left_zig_zag(cur);
                return;
            }
        }
        if (cur->right && cur->val < x) {
            if (cur->right->val == x) {
                return;
            }
            if (cur->right->left && cur->right->val > x) {
                right_zig_zag(cur);
                return;
            }
            if (cur->right->right && cur->right->val < x) {
                right_zig_zig(cur);
                return;
            }
        }
    }

    void splay(node* cur, int x) {
        if (x < cur->val && cur->left) {
            splay(cur->left, x);
        }
        if (x > cur->val && cur->right) {
            splay(cur->right, x);
        }
        choose_zig(cur, x);
    }

    int find_bigger(node* cur, int x) {
        int min = 2e9;
        if (cur->val == x) return x;
        if (cur->val < x) {
            if (cur->right) {
                min = std::min(min, find_bigger(cur->right, x));
            }
            else return 2e9;
        }
        else {
            min = std::min(min, cur->val);
            if (cur->left) {
                min = std::min(min, find_bigger(cur->left, x));
            }
            else return min;
        }
        return min;
    }

    int find_smaller(node* cur, int x) {
        int max = -2e9;
        if (cur->val == x) return x;
        if (cur->val > x) {
            if (cur->left) {
                max = std::max(max, find_smaller(cur->left, x));
            }
            else return -2e9;
        }
        else {
            max = std::max(max, cur->val);
            if (cur->right) {
                max = std::max(max, find_smaller(cur->right, x));
            }
            else return max;
        }
        return max;
    }

    split_tree split(int x) {
        splay(root, x);
        split_tree sptr;
        
        sptr.left = new node;
        give(sptr.left, root);
        sptr.left->right = nullptr;
        resum(sptr.left);
        
        sptr.right = new node;
        give(sptr.right, root);
        sptr.right->left = nullptr;
        resum(sptr.right);
        
        return sptr;
    }

    void merge(split_tree sptr) {
        root->left = sptr.left->left;
        delete sptr.left;
        resum(root);
    }

    void give(node* a, node* b) {
        a->left = b->left;
        a->right = b->right;
        a->val = b->val;
        resum(a);
    }
        
public:

    Splay() : root(new node), last_sum(0) {}

    ~Splay() {
        delete_tree(root);
    }

    void add(int x) {
        if (root->val == 2e9) {
            root->val = x;
            root->sum = x;
            return;
        }
        if (last_sum) {
            x = (x + last_sum) % 1000000000;
            last_sum = 0;
        }
        update(root, x);
    }

    unsigned long long sum(int l, int r) {
        int s_l = find_bigger(root, l);
        int s_r = find_smaller(root, r);
        if (s_l > s_r) {
            last_sum = 0;
            return last_sum;
        }
        split_tree sptr = split(s_l);
        delete root;
        root = sptr.right;
        splay(root, s_r);
        last_sum = root->val + (root->left ? root->left->sum : 0);
        splay(root, s_l);
        merge(sptr);
        return last_sum;
    }
};

int main() {
    int n;
    std::cin >> n;
    char cmd;
    Splay tree;
    int x, l, r;
    for (int i = 0; i < n; ++i) {
        std::cin >> cmd;
        switch (cmd) {

            case '+':
            std::cin >> x;
            tree.add(x);
            break;

            case '?':
            std::cin >> l >> r;
            std::cout << tree.sum(l, r) << '\n';
            break;
        }
    }
}

