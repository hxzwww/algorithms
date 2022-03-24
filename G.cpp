#include <iostream>
#include <vector>

using vec_char = std::vector<char>;

static const int module = 1e9 + 7;

bool check(int mask, int n, vec_char& pattern) {
    for (int i = 0; i < n; ++i) {
        if ((pattern[i] == '+') && !(mask & 1)) {
            return false;
        }
        if ((pattern[i] == '-') && (mask & 1)) {
            return false;
        }
        mask >>= 1;
    }
    return true;
}

bool is_two_in_row(int mask, int n) {
    for (int i = 0; i < n - 1; ++i) {
        if ((mask & 1) == ((mask >> 1) & 1)) {
            return true;
        }
        mask >>= 1;
    }
    return false;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<vec_char> pattern(m, vec_char(n));
    std::string read;
    for (int i = 0; i < n; ++i) {
        std::cin >> read;
        for (int j = 0; j < m; ++j) {
            pattern[j][i] = read[j];
        }
    }
    int T = (1 << n);
    int current_mask;
    int64_t result = 0, current_res, count;
    for (int mask = 0; mask < T; ++mask) {
        if (!check(mask, n, pattern[0])) {
            continue;
        }
        current_res = 1;
        current_mask = (T - 1) ^ mask;
        if (is_two_in_row(mask, n)) {
            for (int i = 1; i < m; ++i) {
                current_res = check(current_mask, n, pattern[i]);
                current_mask = (T - 1) ^ current_mask;
                if (!current_res) {
                    break;
                }
            }
        } else {
            for (int i = 1; i < m; ++i) {
                count = 0;
                if (check(current_mask, n, pattern[i])) {
                    ++count;
                }
                if (check((T - 1) ^ current_mask, n, pattern[i])) {
                    ++count;
                }
                current_res *= count;
                if (!current_res) {
                    break;
                }
            }
        }
        result += current_res;
        result %= module;
    }
    std::cout << result;
}
