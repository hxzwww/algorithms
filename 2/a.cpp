#include <iostream>
#include <string>
#include <fstream>
         
bool operator >(std::string& a, std::string& b) {
    return b + a < a + b;
}

void bubbleSort(std::string* number, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (number[j] > number[j + 1]) {
                std::swap(number[j], number[j + 1]);
            }   
        }   
    }
}
     
int main() {
     
    std::string* number = new std::string [1000];
    std::ifstream numberIn("number.in", std::ios::in);
    int size = 0;
 
    while (!numberIn.eof()) {
        std::string str;
        std::getline(numberIn, str);
        number[size] = std::string(str);
        size++;
    }   

    bubbleSort(number, size);
         
    freopen("number.out", "w", stdout);
    for (int i = size - 1; i >= 0; i--) std::cout << number[i];
}

