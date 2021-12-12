#include <iostream>

struct node {
    int val = 0;
    node* ptr = nullptr;
};

class GoblinsQueue {
private:
    node* last;
    node* mid;
    node* first;
    int queue_size;

public:
    
    GoblinsQueue() : last(nullptr), mid(nullptr), first(nullptr), queue_size(0) {}
    
    void push(int v) {
        queue_size++;
        node* m = new node;
        m -> val = v;
        if (queue_size == 1) {
            last = m;
            first = m;
            mid = m;
        }
        else {
            last -> ptr = m;
            last = m;
            if (queue_size % 2) mid = mid -> ptr;
        }
    }

    int pop() {
        int ans = first -> val;
        queue_size--;
        if (queue_size % 2)
            mid = mid -> ptr;
        node* m = new node;
        m = first -> ptr;
        delete first;
        first = m;
        return ans;
    }

    void pushMid(int v) {
        queue_size++;
        node* m = new node;
        m -> val = v;
        if (queue_size == 1) {
            first = m;
            mid = m;
            last = m;
         }
         else {
            if (queue_size == 2) last = m;
            m -> ptr = mid -> ptr;
            mid -> ptr = m;
            if (queue_size % 2)
                mid = m;
        }
    }

    ~GoblinsQueue() {
        delete_(first);
    }

    void delete_(node* cur) {
        if (cur) {
            delete_(cur->ptr);
            delete cur;
        }
    }
};

int main () {
    GoblinsQueue queue;
    int n;
    std::cin >> n;
    int v;
    char cmd;
    for (int i = 0; i < n; i++) {
        std::cin >> cmd;
        switch (cmd) {
            case '+' :
            std::cin >> v;
            queue.push(v);
            break;

            case '-' :
            std::cout << queue.pop()  << '\n';
            break;

            case '*' :
            std::cin >> v;
            queue.pushMid(v);
            break;
        }
    }
}
