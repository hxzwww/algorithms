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

struct line {
	double a;
	double b;
	double c;
};

bool have_intersection(line l1, line l2) {
	return (l1.a * l2.b - l2.a * l1.b) != 0;
}

point intersection_point(line l1, line l2) {
	double delta = l1.a * l2.b - l2.a * l1.b;
	double delta1 = l1.b * l2.c - l2.b * l1.c;
	double delta2 = l2.a * l1.c - l1.a * l2.c;
	return {delta1 / delta, delta2 / delta};
}

double distance(line l1, line l2) {
	line normal_line{-l1.b, l1.a, 0};
	point inter1 = intersection_point(l1, normal_line);
	point inter2 = intersection_point(l2, normal_line);
	return sqrt((inter1.x - inter2.x) * (inter1.x  - inter2.x) + (inter1.y - inter2.y) * (inter1.y - inter2.y));
}


int main() {
	double a, b, c;
	std::cin >> a >> b >> c;
	line l1{a, b, c};
	std::cin >> a >> b >> c;
	line l2{a, b, c};
	std::cout << std::fixed << std::setprecision(6);
	std::cout << -l1.b << ' ' << l1.a << '\n';
	std::cout << -l2.b << ' ' << l2.a << '\n';
	if (have_intersection(l1, l2)) {
		point inter = intersection_point(l1, l2);
		std::cout << inter.x << ' ' << inter.y;
	} else {
		std::cout << distance(l1, l2);
	}
}

