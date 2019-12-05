#include <bits/stdc++.h>
using namespace std;

constexpr int INF = (1 << 30) - 1;

template < typename T, typename E >
struct LazySegmentTree {

	using F = function < T(T, T) >;
	using G = function < T(T, E) >;
	using H = function < T(E, E) >;
	F f;
	G g;
	H h;
	T ti;
	E ei;
	vector < T > dat;
	vector < E > laz;

	int size, height;

	LazySegmentTree(int n, T ti, E ei, F f, G g, H h) : ti(ti), ei(ei), f(f), g(g), h(h) {
		size = 1, height = 0;
		while ( size < n ) size <<= 1, height++;
		dat.assign((size << 1) + 10, ti);
		laz.assign((size << 1) + 10, ei);
	}
	
	void build(const vector < T > vec) {
		for ( int i = 0; i < vec.size(); i++ ) dat[i + size] = vec[i];
		for ( int i = size - 1; i > 0; i-- ) dat[i] = f(dat[i << 1], dat[(i << 1) | 1]);
	}

	inline T reflect(int k) {
		return ( laz[k] == ei ? dat[k] : g(dat[k], laz[k]) );
	}

	inline void propagate(int k) {
		if ( laz[k] == ei ) return;
		laz[k << 1] = h(laz[k << 1], laz[k]);
		laz[(k << 1) | 1] = h(laz[(k << 1) | 1], laz[k]);
		dat[k] = reflect(k);
		laz[k] = ei;
	}

	inline void thrust(int k) {
		for ( int i = height; i > 0; i-- ) propagate(k >> i);
	}
	
	inline void recalc(int k) {
		while ( k >>= 1 ) dat[k] = f(reflect(k << 1), reflect((k << 1) | 1));
	}

	void update(int a, int b, E x) {
		int l = a + size, r = b + size;
		thrust(l); thrust(r - 1);
		while ( l < r ) {
			if ( l & 1 ) laz[l] = h(laz[l], x), ++l;
			if ( r & 1 ) --r, laz[r] = h(laz[r], x);
			l >>= 1, r >>= 1;
		}
		recalc(a + size); recalc(b + size - 1);
	}

	void setval(int k, T x) {
		thrust(k += size);
		dat[k] = x, laz[k] = ei;
		recalc(k);
	}
//[a, b) T query(int a, int b) {
		int l = a + size, r = b + size;
		T tl = ti, tr = ti;
		thrust(l); thrust(r - 1);
		while ( l < r ) {
			if ( l & 1 ) tl = f(tl, reflect(l++));
			if ( r & 1 ) tr = f(tr, reflect(--r));
			l >>= 1, r >>= 1;
		}
		return ( f(tl, tr) );
	}
};

int main() {
	int N, Q;
	
	auto t = [](int a, int b) { return ( min(a, b) ); };
	auto g = [](int a, int b) { return ( a + b ); };

	cin >> N >> Q;

	LazySegmentTree < int, int > seg(N, INF, 0, t, g, g);
	seg.build(vector < int >(N, 0));

	while ( Q-- ) {
		int Q, A, B, C;
		cin >> Q >> A >> B;
		if ( Q == 0 ) {
			cin >> C;
			seg.update(A, B + 1, C);
		} else {	
			cout << seg.query(A, B + 1) << '\n';
		}
	}
	return ( 0 );
}

//verified https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_H
