#include <bits/stdc++.h>
using namespace std;

const int INF = numeric_limits<int>::max();

template<typename T>
struct SegmentTree {
	
	T id;
	function <T(T, T)> op;
	vector<T> dat;
	int size;

	SegmentTree(int n, T id, function <T(T, T)> op) : id(id), op(op) {
		size = 1;
		while (size < n) size <<= 1;
		dat.assign(size * 2 + 10, id);
	}

	void update(int k, T x) {
		k += size, dat[k] = x;
		while (k > 1) k >>= 1, dat[k] = op(dat[k << 1], dat[(k << 1) | 1]);
	}

	void merge(int k, T x) { update(k, op(x, dat[k + size])); }
	//[a, b)
	T query(int a, int b) {
		T tl = id, tr = id;
		for (int l = a + size, r = b + size; l < r; l >>= 1, r >>= 1) {
			if (l & 1) tl = op(tl, dat[l++]);
			if (r & 1) tr = op(tr, dat[--r]);
		}
		return (op(tl, tr));
	}
};

int main()
{
	int N, Q;
	cin >> N >> Q;
	//RMQ
	SegmentTree<int> seg(N, INF, [](int a, int b) { return (min(a, b)); } );

	while (Q--) {
		int com, a, b;
		cin >> com >> a >> b;
		if (com == 0) seg.update(a, b);
		else cout << seg.query(a, b + 1) << endl;
	}
		
	return (0);
}
