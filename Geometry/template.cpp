#include <bits/stdc++.h>
using namespace std;

constexpr double EPS = 1e-10;
bool equals(double a, double b) { return (fabs(a - b) < EPS); }

struct Point {
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
	
	Point operator + (Point p) { return (Point(x + p.x, y + p.y)); }
	Point operator - (Point p) { return (Point(x - p.x, y - p.y)); }
	Point operator * (double r) { return (Point(x * r, y * r)); }
	Point operator / (double r) { return (Point(x / r, y / r)); }
	
	double abs() { return (sqrt(norm())); }
	double norm() { return (x*x + y*y); }
	
	bool operator < (const Point &p) const { 
		return (x != p.x ? x < p.x : y < p.y); 
	}
	bool operator == (const Point &p) const {
		return (equals(x, p.x) && equals(y, p.y));
	}
};

using Vector = Point;
using Polygon = vector<Point>;
struct Segment {
	Point p1, p2;
	Segment() {}
	Segment(Point p1, Point p2) : p1(p1), p2(p2) {}
};
using Line = Segment;
struct Circle {
	Point c;
	double r;
	Circle() {}
	Circle(Point c, double r) : c(c), r(r) {}
};


