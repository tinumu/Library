#include <bits/stdc++.h>
using namespace std;

constexpr int INF = (1 << 30) - 1;

template<typename M>
struct LazySegmentTree {
	using T = typename M::valueTypeT;
	using E = typename M::valueTypeE;

	vector < T > dat;
	vector < E > laz;

	int size, height;

	LazySegmentTree(int n) {
		size = 1, height = 0;
		while (size < n) size <<= 1, height++;
		dat.assign((size << 1) + 10, M::ti);
		laz.assign((size << 1) + 10, M::ei);
	}

	void build(const vector < T > &vec) {
		for (int i = 0; i < vec.size(); i++) dat[i + size] = vec[i];
		for (int i = size - 1; i > 0; i--) dat[i] = M::f(dat[i << 1], dat[(i << 1) | 1]);
	}

	inline T reflect(int k) {
		return (laz[k] == M::ei ? dat[k] : M::g(dat[k], laz[k]));
	}

	inline void propagate(int k) {
		if (laz[k] == M::ei) return;
		laz[k << 1] = M::h(laz[k << 1], laz[k]);
		laz[(k << 1) | 1] = M::h(laz[(k << 1) | 1], laz[k]);
		dat[k] = reflect(k);
		laz[k] = M::ei;
	}

	inline void thrust(int k) {
		for (int i = height; i > 0; i--) propagate(k >> i);
	}

	inline void recalc(int k) {
		while (k >>= 1) dat[k] = M::f(reflect(k << 1), reflect((k << 1) | 1));
	}

	void update(int a, int b, E x) {
		int l = a + size, r = b + size;
		thrust(l); thrust(r - 1);
		while (l < r) {
			if (l & 1) laz[l] = M::h(laz[l], x), ++l;
			if (r & 1) --r, laz[r] = M::h(laz[r], x);
			l >>= 1, r >>= 1;
		}
		recalc(a + size); recalc(b + size - 1);
	}

	void setval(int k, T x) {
		thrust(k += size);
		dat[k] = x, laz[k] = M::ei;
		recalc(k);
	}
//[a, b)
	T query(int a, int b) {
		int l = a + size, r = b + size;
		T tl = M::ti, tr = M::ti;
		thrust(l); thrust(r - 1);
		while (l < r) {
			if (l & 1) tl = M::f(tl, reflect(l++));
			if (r & 1) tr = M::f(reflect(--r), tr);
			l >>= 1, r >>= 1;
		}
		return (M::f(tl, tr));
	}
};

//区間の長さは取らないといけないかな？
template<typename T>
struct RangeAffineRangeSum {
	using TT = pair<T, int>;
	using E = pair<T, T>;
	using valueTypeE = E;
	using valueTypeT = TT;

	static inline TT ti = TT(0, 0);
	static inline E ei = E(1, 0);
	static TT f(TT a, TT b) { return (TT(a.first+b.first, a.second+b.second)); }
	static TT g(TT a, E b) { return (TT(a.first*b.first + b.second*a.second, a.second)); };
	static E h(E a, E b) { return (E(b.first*a.first, b.first*a.second + b.second)); };
};


template<typename T>
struct RangeAddRangeMin {
	using E = T;
	using valueTypeE = E;
	using valueTypeT = T;

	static inline T ti = numeric_limits<T>::max();
	static inline E ei = 0;
	static T f(T a, T b) { return (min(a, b)); }
	static T g(T a, E b) { return (a+b); }
	static E h(E a, E b) { return (a+b); }
};

//verified https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_H
//verified https://judge.yosupo.jp/problem/range_affine_range_sum

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	int N, Q;
	
	cin >> N >> Q;
	LazySegmentTree<RangeAddRangeMin<int>> seg(N);
	seg.build(vector<int>(N, 0));

	while (Q--) {
		int Q, A, B, C;
		cin >> Q >> A >> B;
		if (Q == 0) {
			cin >> C;
			seg.update(A, B + 1, C);
		} else {	
			cout << seg.query(A, B + 1) << '\n';
		}
	}
	return (0);
}
