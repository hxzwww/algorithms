#include <iostream>
#include <vector>
using std::string;
using std::vector;

class SuffArraySolver {
public:
  SuffArraySolver() = delete;
  explicit SuffArraySolver(const string& /*input_str*/);
  vector<int> suffarray();

private:
  static const int kSigma = 27;
  size_t n;
  string str = string();
  vector<int> p_vector;
  vector<int> c_vector;
  vector<int> counter;
  int index(size_t /*ind*/);
  void preCount();
  void reCount(vector<int> /*p_new*/, int /*exp2k*/);
};

SuffArraySolver::SuffArraySolver(const string& input_str)
    : n(input_str.size() + 1),
      str(input_str + '#'),
      p_vector(n),
      c_vector(n),
      counter(kSigma) {}

int SuffArraySolver::index(size_t ind) {
  return (str[ind] == '#' ? 0 : str[ind] - 'a' + 1);
}

void SuffArraySolver::preCount() {
  c_vector[p_vector[0]] = 0;
  for (size_t i = 0; i < n; ++i) {
    ++counter[index(i)];
  }
  for (size_t i = 1; i < kSigma; ++i) {
    counter[i] += counter[i - 1];
  }
  for (size_t i = n; i > 0; --i) {
    p_vector[--counter[index(i - 1)]] = i - 1;
  }
  for (size_t i = 1; i < n; ++i) {
    c_vector[p_vector[i]] = c_vector[p_vector[i - 1]];
    if (str[p_vector[i]] != str[p_vector[i - 1]]) {
      ++c_vector[p_vector[i]];
    }
  }
}

void SuffArraySolver::reCount(vector<int> p_new, int exp2k) {
  for (size_t i = 0; i < n; ++i) {
    p_new[i] = (p_vector[i] - exp2k);
    if (p_new[i] < 0) {
      p_new[i] += n;
    }
  }
  counter.assign(n, 0);
  for (size_t i = 0; i < n; ++i) {
    ++counter[c_vector[i]];
  }
  for (size_t i = 1; i < n; ++i) {
    counter[i] += counter[i - 1];
  }
  for (size_t i = n; i > 0; --i) {
    p_vector[--counter[c_vector[p_new[i - 1]]]] = p_new[i - 1];
  }
}

vector<int> SuffArraySolver::suffarray() {
  preCount();
  for (int k = 0; (1 << k) < n; ++k) {
    vector<int> p_new(n);
    int exp2k = (1 << k);
    reCount(p_new, exp2k);
    vector<int> c_new(n);
    c_new[p_vector[0]] = 0;
    for (size_t i = 1; i < n; ++i) {
      c_new[p_vector[i]] = c_new[p_vector[i - 1]];
      if (c_vector[p_vector[i]] != c_vector[p_vector[i - 1]]) {
        ++c_new[p_vector[i]];
      } else {
        size_t pi_exp = p_vector[i] + exp2k;
        size_t pi1_exp = p_vector[i - 1] + exp2k;
        if (c_vector[pi_exp >= n ? pi_exp - n : pi_exp] !=
            c_vector[pi1_exp >= n ? pi1_exp - n : pi1_exp]) {
          ++c_new[p_vector[i]];
        }
      }
    }
    c_vector = c_new;
  }
  return p_vector;
}

int main() {
  string str = string();
  std::cin >> str;
  SuffArraySolver solver(str);
  for (auto elem : solver.suffarray()) {
    if (elem != (int)str.size()) {
      std::cout << elem + 1 << ' ';
    }
  }
}

