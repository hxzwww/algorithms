#include <iostream>
#include <string>

struct node {
    int val = 0;
    node* prev = nullptr;
};

class stack{
private:
    node* last;
    int size_;

    void delete_(node* cur) {
        if (cur->prev) delete_(cur->prev);
        delete cur;
    }

public:
    stack() : last(nullptr), size_(0) {}

    ~stack() {
        if (last) delete_(last);
    }

    void push(int x) {
        ++size_;
        node* new_ = new node;
        new_->val = x;
        new_->prev = last;
        last = new_;
    }

    std::string pop() {
        if (!size_) return "error";
        --size_;
        int ans = last->val;
        node* m = last->prev;
        delete last;
        last = m;
        return std::to_string(ans);
    }

    std::string back() {
        if (!size_) return "error";
        return std::to_string(last->val);
    }

    int size() {
        return size_;
    }

    void clear() {
        if (last) delete_(last);
        last = nullptr;
        size_ = 0;
    }
};

int main() {
    stack st;
    std::string cmd;
    int num;
	while (true){
	    std::cin >> cmd;
		if (cmd == "exit"){
			std::cout << "bye\n";
			break;
		}
		if (cmd == "push"){
			std::cin >> num;
			st.push(num);
            std::cout << "ok\n";
		}
		if (cmd == "pop"){
            std::cout << st.pop() << '\n';
		}
		if (cmd == "back"){
            std::cout << st.back() << '\n';
        }
		if (cmd == "size"){
			std::cout << st.size() << '\n';
        }
		if (cmd == "clear"){
            st.clear();
            std::cout << "ok\n";
        }
	}	
}
