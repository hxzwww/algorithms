#include <iostream>
#include <string>

static const int module = 1e9 + 7;
static const int inverse_num_of_2 = 5e8 + 4;
static const int inverse_num_of_3 = 333333336;

int64_t binpow(int64_t num, int64_t degree) {                                    
    if (degree == 0)
        return 1;
    if (degree & 1) {
        return ((binpow(num, degree - 1) % module) * num) % module;
    }
    else {
        int64_t tmp = binpow(num, degree / 2) % module;
        return (tmp * tmp) % module;
    }
}

std::string answer(int64_t denominator, int is_even) {
    denominator = (denominator * inverse_num_of_2) % module;
    int64_t numerator =  ((denominator + is_even) * inverse_num_of_3) % module;
    return std::to_string(numerator) + "/" + std::to_string(denominator);
}

int main() {
    int k;
    int64_t num = 2;
    int is_even = -1;
    int64_t read;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        std::cin >> read;
        num = binpow(num, read);
        if (!(read & 1)) {
            is_even = 1;
        }
    }
    std::cout << answer(num, is_even);
}
