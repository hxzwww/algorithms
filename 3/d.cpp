#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using v_pii = std::vector<std::pair<long long, long long>>;
using pii = std::pair<long long, long long>;

class Tree {
 
private:
 
    struct node {
        unsigned long long sum = 0;
        long long tl = 0, tr = 0;
        node* left = nullptr;
        node* right = nullptr;
    };
    node* first;
 
public:
 
    Tree() {
        first = new node;
        first->sum = 0;
        first->tl = 0;
        first->tr = 1e9;
        first->left = nullptr;
        first->right = nullptr;
    }
 
    ~Tree() {
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
 
    void update(node* current, long long val) {
        if (current->tl == val && current->tr == val) {
            return;
        }
        long long tm = (current->tl + current->tr) >> 1;
        if (val <= tm) {
            if (current->left == nullptr) {
                node* left = new node;
                left->sum = 1;
                left->tl = current->tl;
                left->tr = tm;
                current->left = left;
            }
            else {
                current->left->sum += 1;
            }
            update(current->left, val);
        }
        if (val >= tm + 1) {
            if (current->right == nullptr) {
                node* right = new node;
                right->sum = 1;
                right->tl = tm + 1;
                right->tr = current->tr;
                current->right = right;
            }
            else {
                current->right->sum += 1;
            }
            update(current->right, val);
        }
    }
 
    void add(long long val) {
        first->sum += 1;
        update(first, val);
    }
 
    void delete_val(node* current, long long val) {
        --current->sum;
        if (current->tl == val && current->tr == val) {
            return;
        }
        long long tm = (current->tl + current->tr) >> 1;
        if (val <= tm) {
            if (current->left) {
                delete_val(current->left, val);
            }
        }
        if (val >= tm + 1) {
            if (current->right) {
                delete_val(current->right, val);
            }
        }
    }
 
    unsigned long long get_sum(long long val) {
        unsigned long long answer = sum(first, val);
        delete_val(first, val);
        return answer;
    }
 
    unsigned long long sum(node* current, long long val) {
        if (current->tr <= val) {
            return current->sum;
        }
        unsigned long long ans = 0;
        long long tm = (current->tl + current->tr) >> 1;
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
    friend unsigned long long solve(std::vector<std::pair<long long, long long>>& arr, Tree& tree);
};

bool comp(pii a, pii b){
    if (a.first == b.first) {
        return (a.second > b.second);
    }
    return (a.first < b.first);
}
 
unsigned long long solve(std::vector<std::pair<long long, long long>>& arr, Tree& tree) {
    for (size_t i = 0; i < arr.size(); ++i) {
        tree.add(arr[i].second);
    }
    long long replays_cnt = 1;
    unsigned long long ans = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        ans += (tree.get_sum(arr[i].second) - 1);
        if (i) {
            if (arr[i] == arr[i-1]) {
                ++replays_cnt;
            }
            else {
                ans -= ((replays_cnt - 1) * replays_cnt / 2);
                replays_cnt = 1;
            }
        }

    }
    ans -= ((replays_cnt - 1) * replays_cnt / 2);
    return ans;
}

int main() {
    long long n;
    scanf("%lld", &n);
    v_pii arr;
    for (long long i = 0; i < n; ++i) {
        pii arr_i;
        scanf("%lld%lld", &arr_i.first, &arr_i.second);
        arr.push_back(arr_i);
    }
    sort(arr.begin(), arr.end(), comp);
    Tree tree;
    printf("%lld", solve(arr, tree));
}

