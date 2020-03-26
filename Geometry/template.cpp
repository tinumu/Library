#include <bits/stdc++.h>
using namespace std;

constexpr double EPS = 1e-10;
constexpr int COUNTER_CLOCKWISE = 1;
constexpr int CLOCKWISE = -1;
constexpr int ONLINE_BACK = 2;
constexpr int ONLINE_FRONT = -2;
constexpr int ON_SEGMENT = 0;

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
	V2 normalized() const { return (*this / norm()); }

	double dot(const V2 &p) const { return (x*p.x + y*p.y); }
	double cross(const V2 &p) const { return (x*p.y - y*p.x); }
	double arg() const { return (atan2(y, x)); }
};
V2 polar(double r, double a) { return (V2(cos(a) * r, sin(a) * r)); }
int ccw(V2 p0, V2 p1, V2 p2) {
	V2 a = p1-p0, b = p2-p0;
	if (a.cross(b) > EPS) return (COUNTER_CLOCKWISE);
	if (a.cross(b) < -EPS) return (CLOCKWISE);
	if (a.dot(b) < -EPS) return (ONLINE_BACK);
	if (a.sqrNorm() < b.sqrNorm()) return (ONLINE_FRONT);
	return (ON_SEGMENT);
}
using Polygon = vector<V2>;
struct Segment {
	V2 p1, p2;
	Segment() {}
	Segment(V2 p1, V2 p2) : p1(p1), p2(p2) {}
};

using Line = Segment;

struct Circle {
	V2 o;
	double r;
	Circle() {}
	Circle(V2 o, double r) : o(o), r(r) {}

	int intersects(const Circle &c) {
		double d = (o-c.o).norm();
		if (d + c.r < r) return (3); //contain on A
		if (d + r < c.r) return (-3); //contain on B
		if (equals(d + c.r, r)) return (1);  //inscribed on A
		if (equals(d + r, c.r)) return (-1); //inscribed on B
		if (r + c.r < d) return (0); //circumscribed
		if (equals(r + c.r, d)) return (4); //far 
		return (2); //intersected
	}

	vector<V2> crossPoints(const Circle &c) {
		int inter = intersects(c);
		if (abs(inter) == 3 || inter == 0) return (vector<V2>());
		double d = (c.o-o).norm();
		double t = (c.o-o).arg();
		if (abs(inter) == 1 || inter == 4) return ((vector<V2>){o + (c.o-o).normalized() * r});
		double a = acos((r*r + d*d - c.r*c.r) / (2*r*d));
		return ((vector<V2>){o + polar(r, t+a), o + polar(r, t-a)});
	}
};

Polygon ConvexHull(Polygon data) {
	int size = data.size();
	Polygon u, l;
	sort(begin(data), end(data));
	if (size < 3) return (data);
	u.push_back(data[0]); u.push_back(data[1]);
	l.push_back(data[size-1]); l.push_back(data[size-2]);
	for (int i = 2; i < size; i++) {
		for (int sz = u.size(); sz > 1 && ccw(u[sz-2], u[sz-1], data[i]) != CLOCKWISE; sz--) {
			u.pop_back();
		}
		u.push_back(data[i]);
	}
	for (int i = size-3; i >= 0; i--) {
		for (int sz = l.size(); sz > 1 && ccw(l[sz-2], l[sz-1], data[i]) != CLOCKWISE; sz--) {
			l.pop_back();
		}
		l.push_back(data[i]);
	}
	reverse(begin(l), end(l));
	for (int i = u.size()-2; i >= 1; i--) {
		l.push_back(u[i]);
	}
	return (l);
}
