#include <string>
#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <queue>
using std::vector;

struct Condition {
    int weight;
    uint64_t current; 
    std::string res; 
    Condition() = default;
    Condition(const Condition& other) :
        weight(other.weight), 
        current(other.current), 
        res(other.res) {}
    Condition(uint64_t current, std::string res, int weight) :
        weight(weight), current(current), res(res) {}
    void operator=(const Condition& other) {
        weight = other.weight;
        current = other.current;
        res = other.res;
    }
    ~Condition() {}
};

using QUEUE = std::priority_queue<
Condition, vector<Condition>, std::greater<Condition>>;

static const uint64_t finish_condition = 1147797409030816545;

bool operator>(const Condition& a, const Condition& b) {
    if (a.weight != b.weight) return a.weight > b.weight;
    return a.res.size() < b.res.size();
}

uint64_t tolong(vector<int>& vec) {                                         
    uint64_t res = 0;                                                           
    for (int i = 15; i >= 0; --i) {                                             
        res <<= 4;                                                              
        res += vec[i];                                                            
    }                                                                           
    return res;                                                                 
}

int num(uint64_t mask, int i) {                                                 
    return (mask >> (4 * i)) & 15;                                          
}

uint64_t swap(uint64_t mask, uint64_t a, uint64_t b) {
    a = a << 2;
    b = b << 2;
    uint64_t x = (mask >> a) & 15;
    uint64_t y = (mask >> b) & 15;
    mask = mask ^ (x << a);
    mask = mask ^ (y << b);
    mask |= (y << a);
    mask |= (x << b);
    return mask;
}

void process(Condition& new_cond, Condition& cond, char sym, int shift, 
        int zero_num, QUEUE& queue) {
    new_cond.res = cond.res + sym;
    new_cond.weight = cond.weight -
        (num(new_cond.current, zero_num) == zero_num + 1) +
        (num(cond.current, zero_num + shift) == zero_num + shift + 1);
    queue.push(new_cond);
}

void next_conds(Condition& cond, QUEUE& queue, std::unordered_set<uint64_t>& used) {
    used.insert(cond.current);
    uint8_t zero_num;
    for (int i = 0; i < 16; ++i) {
        if (num(cond.current, i) == 0) {
            zero_num = i;
            break;
        }
    }
    Condition new_cond;
    if (zero_num >= 4 && cond.res.back() != 'U') {
        new_cond.current = swap(cond.current, zero_num, zero_num - 4);
        if (used.find(new_cond.current) == used.end())         
            process(new_cond, cond, 'D', -4, zero_num, queue);
    }
    if (zero_num % 4 != 0 && cond.res.back() != 'L') {
        new_cond.current = swap(cond.current, zero_num, zero_num - 1);
        if (used.find(new_cond.current) == used.end()) 
            process(new_cond, cond, 'R', -1, zero_num, queue);
    }
    if (zero_num % 4 != 3 && cond.res.back() != 'R') {
        new_cond.current = swap(cond.current, zero_num, zero_num + 1);
        if (used.find(new_cond.current) == used.end()) 
            process(new_cond, cond, 'L', 1, zero_num, queue); 
    }
    if (zero_num < 12 && cond.res.back() != 'D') {
        new_cond.current = swap(cond.current, zero_num, zero_num + 4);
        if (used.find(new_cond.current) == used.end()) 
            process(new_cond, cond, 'U', 4, zero_num, queue);
    }
}

int conflict_counter(vector<int>& cur) {
    int count = 0;
    for (int i = 0; i < 16; ++i) {
        if (!cur[i]) continue;
        count += (cur[i] != i + 1);
    }
    return count;
}

std::string solve(vector<int>& start) {
            
    Condition first;
    first.current = tolong(start);
    int weight = conflict_counter(start);
    first.res = "";
        
    QUEUE queue;
    queue.push(first);

    std::unordered_set<uint64_t> used;

    while (true) {
        Condition v = queue.top();
        queue.pop();
        if (used.find(v.current) != used.end()) {
            continue;
        }
        if (v.current == finish_condition) {
            return std::to_string(v.res.size()) + '\n' + v.res;
        }
        next_conds(v, queue, used);
    }
    return "";
}

bool solvable(vector<int>& start, int zero_num) {
    int inv = 0;
    for (int i = 0; i < 16; ++i) {
        if (start[i]) {
            for (int j = 0; j < i; ++j) {
                if (start[j] > start[i]) {
                    ++inv;
                }
            }
        }
    }
    inv += zero_num / 4;
    return inv & 1;
}

int main() {
    int zero_num;
    vector<int> start(16);
    for (int i = 0; i < 16; ++i) {
        std::cin >> start[i];
        if (start[i] == 0) zero_num = i;
    }
    
    if (!solvable(start, zero_num)) {
        std::cout << -1;
    } else {
        std::cout << solve(start);
    } 
}


