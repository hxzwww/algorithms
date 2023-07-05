#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>

static const double eps = 1e-9;

struct point {
	double x;
	double y;

	point operator*(double k) {
		return {x * k, y * k};
	}

	point operator-(point other) {
		return {x - other.x, y - other.y};
	}

	bool operator==(point other) const {
		return (x == other.x) && (y == other.y);
	}

	bool belongs_segment(const point& p, const point& q) const {
		return std::fabs(sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y)) +
			sqrt((x - q.x) * (x - q.x) + (y - q.y) * (y - q.y)) -
			sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y))) <= eps;
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
	point p;
	point q;

	line(double a, double b, double c) :
		a(a), b(b), c(c) {}

	line(const point& p, const point& q) :
		p(p), q(q),
		a(p.y - q.y), b(q.x - p.x),
		c(p.x * q.y - p.y * q.x) {}

	bool operator==(const line& other) const {
		return (a * other.b - b * other.a) == 0;
	}
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


int main() {
	int n;
	std::cin >> n;
	std::vector<point> p;
	for (int i = 0; i < n; ++i) {
		double x, y;
		std::cin >> x >> y;
		p.push_back({x, y});
	}

	std::vector<vec> v;

	for (int i = 0; i < n - 1; ++i) {
		v.push_back(vec(p[i], p[i + 1]));
	}
	v.push_back(vec(p[n - 1], p[0]));
	v.push_back(vec(p[0], p[1]));

	int sign = 0;

	for (int i = 0; i < v.size() - 1; ++i) {
		double aboba = vector_multiply(v[i], v[i + 1]);
		if (sign && aboba) {
			if (aboba * sign < 0) {
				std::cout << "NO";
				return 0;
			}
		}
		if (!sign && aboba) {
			sign = (aboba > 0) ? 1 : -1;
		}
	}
	std::cout << "YES";
}

