// fast fourier transform algo

#include <cmath>
#include <complex>
#include <iostream>
#include <numbers>
#include <vector>

using std::vector;

class FFT {
public:
  FFT(vector<int>& a_polynomial, vector<int>& b_polynomial);
  void findPolynomialsProduct();
  vector<int> getResultPolynomial() const;

private:
  using complex = std::complex<double>;
  constexpr static const double kPi = std::numbers::pi;
  vector<int> a_polynomial;
  vector<int> b_polynomial;
  vector<int> c_polynomial;

  void fft(vector<complex>& polynomial, int degree, complex omega);
};

FFT::FFT(vector<int>& a_polynomial, vector<int>& b_polynomial)
    : a_polynomial(a_polynomial), b_polynomial(b_polynomial) {}

void FFT::findPolynomialsProduct() {
  vector<complex> fourier_a(a_polynomial.begin(), a_polynomial.end());
  vector<complex> fourier_b(b_polynomial.begin(), b_polynomial.end());
  size_t size = 1;
  while (size <= fourier_a.size() + fourier_b.size() - 2) {
    size <<= 1;
  }
  complex omega(cos(2 * kPi / size), sin(2 * kPi / size));
  fft(fourier_a, size, omega);
  fft(fourier_b, size, omega);
  for (size_t i = 0; i < size; ++i) {
    fourier_a[i] *= fourier_b[i];
  }
  fft(fourier_a, size, complex(1) / omega);
  c_polynomial.resize(size);
  for (size_t i = 0; i < size; ++i) {
    c_polynomial[i] = lround(fourier_a[i].real() / size);
  }
  while (!c_polynomial.empty() && c_polynomial.back() == 0) {
		c_polynomial.pop_back();
  }
}

vector<int> FFT::getResultPolynomial() const {
  return c_polynomial;
}

void FFT::fft(vector<complex>& polynomial, int degree, complex omega) {
  if (degree == 1) {
    return;
  }
  polynomial.resize(degree);
  vector<complex> polynomial_0(degree / 2);
  vector<complex> polynomial_1(degree / 2);
  for (int i = 0, j = 0; i < degree; i += 2, ++j) {
    polynomial_0[j] = polynomial[i];
    polynomial_1[j] = polynomial[i + 1];
  }
  fft(polynomial_0, degree / 2, omega * omega);
  fft(polynomial_1, degree / 2, omega * omega);
  complex complex_one(1);
  for (int i = 0; i < degree / 2; ++i) {
    polynomial[i] = polynomial_0[i] + complex_one * polynomial_1[i];
    polynomial[i + degree / 2] =
      polynomial_0[i] - complex_one * polynomial_1[i];
    complex_one *= omega;
  }
}

int main() {
  int a_degree;
  int b_degree;
  std::cin >> a_degree;
  vector<int> a_polynomial(a_degree + 1);
  for (auto& read : a_polynomial) {
    std::cin >> read;
  }
  std::cin >> b_degree;
  vector<int> b_polynomial(b_degree + 1);
  for (auto& read : b_polynomial) {
    std::cin >> read;
  }
  a_polynomial = vector<int>(a_polynomial.rbegin(), a_polynomial.rend());
  b_polynomial = vector<int>(b_polynomial.rbegin(), b_polynomial.rend());
  FFT fft_solver(a_polynomial, b_polynomial);
  fft_solver.findPolynomialsProduct();
  auto result = fft_solver.getResultPolynomial();
  std::cout << result.size() - 1 << ' ';
  for (int i = result.size() - 1; i >= 0; --i) {
    std::cout << result[i] << ' ';
  }
}
