#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

struct point {
	double x;
	double y;

	point operator*(double k) {
		return {x * k, y * k};
	}

	point operator-(point other) {
		return {x - other.x, y - other.y};
	}
};

struct vec {
	double x;
	double y;

	vec(point p, point q) {
		x = q.x - p.x;
		y = q.y - p.y;
	}

	double len() {
		return sqrt(x * x + y * y);
	}

	void normalize() {
		auto len_ = len();
		x /= len_;
		y /= len_;
	}


};
double scalar_multiply(vec lhs, vec rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

double vector_multiply(vec lhs, vec rhs) {
	return lhs.x * rhs.y - rhs.x * lhs.y;
}

int main() {
	double px, py, qx, qy;
	std::cin >> px >> py >> qx >> qy;
	vec vec1({px, py}, {qx, qy});
	std::cin >> px >> py >> qx >> qy;
	vec vec2({px, py}, {qx, qy});
	std::cout << std::fixed << std::setprecision(6) << vec1.len() << ' ' << vec2.len() << '\n';
	std::cout << std::fixed << std::setprecision(6) << vec1.x + vec2.x << ' ' << vec1.y + vec2.y << '\n';
	std::cout << std::fixed << std::setprecision(6) << scalar_multiply(vec1, vec2) << ' ' << vector_multiply(vec1, vec2) << '\n';
	std::cout << std::fixed << std::setprecision(6) << std::fabs(vector_multiply(vec1, vec2)) / 2;
}

