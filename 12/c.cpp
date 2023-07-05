#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

static const double kEps = 1e-9;

struct Point {
  double x;
  double y;

  Point operator*(double coefficient) const {
    return {x * coefficient, y * coefficient};
  }

  Point operator-(Point other) const {
    return {x - other.x, y - other.y};
  }

  bool operator==(Point other) const {
    return (x == other.x) && (y == other.y);
  }

  bool belongsSegment(const Point& first, const Point& second) const {
    return std::fabs(sqrt((x - first.x) * (x - first.x) +
                          (y - first.y) * (y - first.y)) +
                     sqrt((x - second.x) * (x - second.x) +
                          (y - second.y) * (y - second.y)) -
                     sqrt((first.x - second.x) * (first.x - second.x) +
                          (first.y - second.y) * (first.y - second.y))) <= kEps;
  }
};

struct Line {
  double a;
  double b;
  double c;
  Point p;
  Point q;

  Line(double a_param, double b_param, double c_param)
      : a(a_param), b(b_param), c(c_param) {}

  Line(const Point& first, const Point& second)
      : a(first.y - second.y),
        b(second.x - first.x),
        c(first.x * second.y - first.y * second.x),
        p(first),
        q(second) {}

  bool operator==(const Line& other) const {
    return (a * other.b - b * other.a) == 0;
  }
};

bool haveIntersection(Line line_1, Line line_2) {
  return (line_1.a * line_2.b - line_2.a * line_1.b) != 0;
}

Point intersectionPoint(Line line_1, Line line_2) {
  double delta = line_1.a * line_2.b - line_2.a * line_1.b;
  double delta1 = line_1.b * line_2.c - line_2.b * line_1.c;
  double delta2 = line_2.a * line_1.c - line_1.a * line_2.c;
  return {delta1 / delta, delta2 / delta};
}

std::string solve(const Line& line_1, const Line& line_2) {
  if (line_1.p == line_1.q) {
    if (line_2.p == line_2.q) {
      return (line_1.p == line_2.p) ? "YES" : "NO";
    }
    return line_1.p.belongsSegment(line_2.p, line_2.q) ? "YES" : "NO";
  }
  if (line_2.p == line_2.q) {
    return line_2.p.belongsSegment(line_1.p, line_1.q) ? "YES" : "NO";
  }
  if (line_1 == line_2) {
    if (line_1.p.belongsSegment(line_2.p, line_2.q) ||
        line_1.p.belongsSegment(line_2.p, line_2.q) ||
        line_2.p.belongsSegment(line_1.p, line_1.q) ||
        line_2.q.belongsSegment(line_1.p, line_1.q)) {
      return "YES";
    }
    return "NO";
  }
  if (!haveIntersection(line_1, line_2)) {
    return "NO";
  }
  // std::cout << 123;
  Point inter_point = intersectionPoint(line_1, line_2);
  if (inter_point.belongsSegment(line_1.p, line_1.q) &&
      inter_point.belongsSegment(line_2.p, line_2.q)) {
    return "YES";
  }
  return "NO";
}

int main() {
  double p1x;
  double p1y;
  double q1x;
  double q1y;
  double p2x;
  double p2y;
  double q2x;
  double q2y;
  std::cin >> p1x >> p1y >> q1x >> q1y;
  std::cin >> p2x >> p2y >> q2x >> q2y;
  Line line_1({p1x, p1y}, {q1x, q1y});
  Line line_2({p2x, p2y}, {q2x, q2y});
  std::cout << solve(line_1, line_2);
}

