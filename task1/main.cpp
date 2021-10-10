#include <iostream>
#include "arithmetics.h"

void panic() {
    std::cout << "Unexpected result: " << result << "\n";
}

void printSuccess() {
    std::cout << "Ok!" << "/n";
}

int main() {
    int a, b;
    std::cin >> a >> b;

    if (sum(a, b) == a + b) {
        printSuccess();
    }
    else {
        panic(sum(a, b));
    }

    if (mul(a, b) == a * b) {
        printSuccess();
    }
    else {
        panic(mul(a, b));
    }
    
    return 0;
}
