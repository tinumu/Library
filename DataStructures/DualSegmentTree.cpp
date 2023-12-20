#include <bits/stdc++.h>
using namespace std;


template <typename M>
struct DualSegmentTree {
	using E = typename M::valueTypeE;

	vector < E > laz;

	int size, height;
	DualSegmentTree(int n) {
		size = 1, height = 0;
		while (size < n) size <<= 1, height++;
		laz.assign((size << 1) + 10, M::ei);
	}

	inline void propagate(int k) {
		if (laz[k] == M::ei) return;
		laz[k << 1] = M::h(laz[k << 1], laz[k]);
		laz[(k << 1) | 1] = M::h(laz[(k << 1) | 1], laz[k]);
		laz[k] = M::ei;
	}

	inline void thrust(int k) {
		for (int i = height; i > 0; i--) propagate(k >> i);
	}

	//[a, b)
	void update(int a, int b, E x) {
		int l = a + size, r = b + size;
		thrust(l); thrust(r - 1);
		while (l < r) {
			if (l & 1) laz[l] = M::h(laz[l], x), ++l;
			if (r & 1) --r, laz[r] = M::h(laz[r], x);
			l >>= 1, r >>= 1;
		}
	}

	template<typename T>
	T get(int k, const T &dat, const function<T(T, E)> &g) {
		thrust(k + size);
		return (M::g(dat, laz[k+size]));
	}

	E get(int k) {
		thrust(k + size);
		return (laz[k+size]);
	}
};


template<typename T>
struct RangeAffinePointGet {
	using E = pair<T, T>;
	using valueTypeE = E;

	static inline E ei = E(1, 0);
	static E h(E a, E b) { return (E(b.first*a.first, b.first*a.second + b.second)); };
	static T g(T a, E b) { return (a*b.first + b.second); }; //双対セグ木では使わないが
};

//verified https://judge.yosupo.jp/problem/range_affine_point_get
//modint は省略する
int main() {
	using Mint = Modint<998244353>;
	using ll = long long;
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	int N, Q; cin >> N >> Q;
	vector<ll> A(N);
	for (auto &a : A) cin >> a;
	DualSegmentTree<RangeAffinePointGet<Mint>> seg(N);
	while (Q--) {
		int t; cin >> t;
		if (t == 0) {
			int l, r, b, c; cin >> l >> r >> b >> c;
			seg.update(l, r, make_pair(b, c));
		} else {
			int i; cin >> i;
			cout << RangeAffinePointGet<Mint>::g(A[i], seg.get(i)) << '\n';
		}
	}
}
