#include <bits/stdc++.h>
using namespace std;

template <typename E>
struct DualSegmentTree {

	using H = function < E(E, E) >;
	H h;
	E ei;
	vector < E > laz;

	int size, height;
	DualSegmentTree(int n, E ei, H h) : ei(ei), h(h) {
		size = 1, height = 0;
		while (size < n) size <<= 1, height++;
		laz.assign((size << 1) + 10, ei);
	}
	
	inline void propagate(int k) {
		if (laz[k] == ei) return;
		laz[k << 1] = h(laz[k << 1], laz[k]);
		laz[(k << 1) | 1] = h(laz[(k << 1) | 1], laz[k]);
		laz[k] = ei;
	}

	inline void thrust(int k) {
		for (int i = height; i > 0; i--) propagate(k >> i);
	}
	
	//[a, b)
	void update(int a, int b, E x) {
		int l = a + size, r = b + size;
		thrust(l); thrust(r - 1);
		while (l < r) {
			if (l & 1) laz[l] = h(laz[l], x), ++l;
			if (r & 1) --r, laz[r] = h(laz[r], x);
			l >>= 1, r >>= 1;
		}
	}

	template<typename T>
	T get(int k, const T &dat, const function<T(T, E)> &g) {
		thrust(k + size);
		return (g(dat, laz[k+size]));
	}

	E get(int k) {
		thrust(k + size);
		return (laz[k+size]);
	}
};

//verified https://judge.yosupo.jp/problem/range_affine_point_get

using ll = long long;
using Query = pair<ll, ll>;
constexpr ll mod = 998244353;

ll G(ll a, Query b) {
	const auto &[A, B] = b;
	return ((A*a + B) % mod);
}

Query H(Query a, Query b) {
	const auto &[A1, B1] = a;
	const auto &[A2, B2] = b;
	return (Query(A2*A1 % mod, (A2*B1 + B2) % mod));
}

Query EI = Query(1, 0);

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	int N, Q; cin >> N >> Q;
	vector<ll> A(N);
	for (auto &a : A) cin >> a;
	DualSegmentTree<Query> seg(N, EI, H);
	while (Q--) {
		int t; cin >> t;
		if (t == 0) {
			int l, r, b, c; cin >> l >> r >> b >> c;
			seg.update(l, r, Query(b, c));
		} else {
			int i; cin >> i;
			cout << G(A[i], seg.get(i)) << '\n';
		}
	}
}
