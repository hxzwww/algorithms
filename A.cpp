#include <iostream>

struct node {
    node* left = nullptr;
    node* right = nullptr;
    int depth = 1;
    int val = 2e9;
};

class AVL {

private:

    node* root;

    void delete_tree(node* current) {
        if (current->left) {
            delete_tree(current->left);
        }
        if (current->right) {
            delete_tree(current->right);
        }
        delete current;
    }

    node* find(node* cur, int x) {
        if (cur->val == x) {
            return cur;
        }
        if (x < cur->val && cur->left) {
            return find(cur->left, x);
        }
        if (x > cur->val && cur->right) {
            return find(cur->right, x);
        }
        return nullptr;
    }

    node* find_parent(node* cur, int x) {
        if (cur->left && cur->left->val == x) {
            return cur;
        }
        if (cur->right && cur->right->val == x) {
            return cur;
        }
        if (x < cur->val && cur->left) {
            return find_parent(cur->left, x);
        }
        if (x > cur->val && cur->right) {
            return find_parent(cur->right, x);
        }
        return nullptr;
    }
    
    void exchange(node* cur, int x) {
        if (x == root->val && !root->left && !root->right) {
            root->val = 2e9;
            return;
        }
        if (!cur->left) {
            if (cur->right) {
                give(cur, cur->right);
            }
            else {
                node* par = find_parent(root, x);
                if (par->left && par->left->val == x) par->left = nullptr;
                else par->right = nullptr;
            }
        }
        else {
            if (cur->right) {
                if (!cur->right->left) {
                    cur->val = cur->right->val;
                    cur->right = cur->right->right;
                }
                else {
                    cur->val = right_min(cur->right);
                }
            }
            else {
                give(cur, cur->left);
            }
        }
    }

    int right_min(node* cur) {
        if (!cur->left) {
            int m = cur->val;
            exchange(cur, m);
            return m;
        }
        return right_min(cur->left);
    }

    int find_next(node* cur, int x) {
        int min = 2e9;
        if (cur->val <= x) {
            if (cur->right) {
                min = std::min(min, find_next(cur->right, x));
            }
            else return 2e9;
        }
        else {
            min = std::min(min, cur->val);
            if (cur->left) {
                min = std::min(min, find_next(cur->left, x));
            }
            else return min;
        }
        return min;
    }

    int find_prev(node* cur, int x) {
        int max = -2e9;
        if (cur->val >= x) {
            if (cur->left) {
                max = std::max(max, find_prev(cur->left, x));
            }
            else return -2e9;
        }
        else {
            max = std::max(max, cur->val);
            if (cur->right) {
                max = std::max(max, find_prev(cur->right, x));
            }
            else return max;
        }
        return max;
    }

    void give(node* to, node* from) {
        to->val = from->val;
        to->left = from->left;
        to->right = from->right;
        to->depth = from->depth;
    }

    int delta(node* cur) {
        int del = 0;
        if (cur->left) del += cur->left->depth;
        if (cur->right) del -= cur->right->depth;
        return del;
    }

    void right_rotation(node* cur) {
        node* m = new node;
        give(m, cur);
        m->right = cur->right->left;
        cur->right->left = m;
        give(cur, cur->right);
    }

    void left_rotation(node* cur) {
        node* m = new node;
        give(m, cur);
        m->left = cur->left->right;
        cur->left->right = m;
        give(cur, cur->left);
    }

    void update(node* cur, int x) {
        if (cur->val == x) {
            return;
        }
        if (x < cur->val) {
            if (cur->left) {
                update(cur->left, x);
            }
            else {
                cur->left = new node;
                cur->left->val = x;
            }
        }
        else { 
            if (cur->right) {
                update(cur->right, x);
            }
            else {
                cur->right = new node;
                cur->right->val = x;
            }
        }
        recalculate_depth(cur);
    }

    void check_depth(node* cur) {
        int del = delta(cur);
        if (del <= -2) {
            if (delta(cur->right) < 1) {
                right_rotation(cur);
            }
            else {
                left_rotation(cur->right);
                right_rotation(cur);
            }
        }
        if (del >= 2) {
            if (delta(cur->left) > -1) {
                left_rotation(cur);
            }
            else {
                right_rotation(cur->left);
                left_rotation(cur);
            }
        }
    }

    void recalculate_depth(node* cur) {
        int l_depth = 0, r_depth = 0;
        if (cur->left) {
            l_depth = cur->left->depth;
        }
        if (cur->right) {
            r_depth = cur->right->depth;
        }
        cur->depth = 1 + std::max(l_depth, r_depth);
        check_depth(cur);
    }

    void extraction(node* cur, int x) {
        if (cur->val == x) {
            exchange(cur, x);
        }
        if (!cur->left && !cur->right) {
            return;
        }
        else {
            if (cur->left && x < cur->val) {
                extraction(cur->left, x);
            }
            if (cur->right && x > cur->val) {
                extraction(cur->right, x);
            }
        }
        recalculate_depth(cur);
    }

public:

    AVL() : root(new node) {}

    ~AVL() {
        delete_tree(root);
    }

    void insert(int x) {
        if (root->val == 2e9) {
            root->val = x;
            return;
        }
        update(root, x);
    }

    void delete_(int x) {
        if (root->val == x) {
            exchange(root, x);
            return; 
        }
        extraction(root, x);
    }

    std::string next(int x) {
        int ans = find_next(root, x);
        return ((ans != 2e9) ? std::to_string(ans) : "none"); 
    }

    std::string prev(int x) {
        int ans = find_prev(root, x);
        return ((ans != -2e9) ? std::to_string(ans) : "none");
    }

    std::string exists(int x) {
        if (find(root, x) == nullptr) {
            return "false";
        }
        else return "true";
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::string cmd;
    int x;
    AVL avl_tree;
    while (std::cin >> cmd) {
        std::cin >> x;
        switch (cmd[0]) {

            case 'i': //insert
            avl_tree.insert(x);
            break;
            
            case 'd': //delete
            avl_tree.delete_(x);
            break;
            
            case 'e': //exists
            std::cout << avl_tree.exists(x) << '\n';
            break;

            case 'n': //next
            std::cout << avl_tree.next(x) << '\n';
            break;

            case 'p': //prev
            std::cout << avl_tree.prev(x) << '\n';
            break;
        }
    }
}
