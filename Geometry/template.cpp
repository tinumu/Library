#include <bits/stdc++.h>
using namespace std;

constexpr double EPS = 1e-10;
bool equals(double a, double b) { return (abs(a - b) < EPS); }

struct V2 {
	double x, y;
	V2(double x = 0, double y = 0) : x(x), y(y) {}
	
	V2 operator + (V2 p) const { return (V2(x + p.x, y + p.y)); }
	V2 operator - (V2 p) const { return (V2(x - p.x, y - p.y)); }
	V2 operator * (double r) const { return (V2(x * r, y * r)); }
	V2 operator / (double r) const { return (V2(x / r, y / r)); }
	
	double norm() const { return (sqrt(sqrNorm())); }
	double sqrNorm() const { return (x*x + y*y); }
	
	bool operator < (const V2 &p) const { 
		return (x != p.x ? x < p.x : y < p.y); 
	}
	bool operator == (const V2 &p) const {
		return (equals(x, p.x) && equals(y, p.y));
	}

	V2 rotate90() const { return (V2(y, -x)); }
	double dot(const V2 &p) const { return (x*p.x + y*p.y); }
	double cross(const V2 &p) const { return (x*p.y - y*p.x); }
};

using Polygon = vector<V2>;
struct Segment {
	V2 p1, p2;
	Segment() {}
	Segment(V2 p1, V2 p2) : p1(p1), p2(p2) {}
};

using Line = Segment;
struct Circle {
	V2 c;
	double r;
	Circle() {}
	Circle(V2 c, double r) : c(c), r(r) {}
};


