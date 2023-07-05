#include <iostream>
#include <vector>
#include <set>
#include <map>

int main() {
    long long N;
    int M, K;
    std::cin >> N;
    std::cin >> M >> K;
    std::map <long long, std::set<long long>> map;
    std::vector<std::set<long long>> vec(M + 1);
    std::string cmd;
    long long num, index;
    for (int r = 0; r < K; ++r) {
        std::cin >> cmd;
        if (cmd == "ADD") {
            std::cin >> num >> index;
            vec[index].insert(num);
            map[num].insert(index);
        }
        if (cmd == "DELETE") {
            std::cin >> num >> index;
            vec[index].erase(num);
            map[num].erase(index);
        }
        if (cmd == "CLEAR") {
            std::cin >> index;
            for (auto j : vec[index]) map[j].erase(index);
            vec[index].clear();
        }
        if (cmd == "LISTSET") {
            std::cin >> index;
            if (vec[index].empty()) std::cout << -1;
            else for (auto j : vec[index]) std::cout << j << " ";
            std::cout << '\n';
        }
        if (cmd == "LISTSETSOF") {
            std::cin >> num;
            if (map[num].empty()) std::cout << -1;
            else for (auto j : map[num]) std::cout << j << " ";
            std::cout << '\n';
        }
    }
}

