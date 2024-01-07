#include <bits/stdc++.h>
using namespace std;


template<typename Monoid>
struct SegmentTree {
	using T = typename Monoid::valueType;
	vector<T> dat;
	int size;

	SegmentTree(int n) {
		size = 1;
		while (size < n) size <<= 1;
		dat.assign(size * 2, Monoid::id);
	}

	void update(int k, T x) {
		k += size, dat[k] = x;
		while (k > 1) k >>= 1, dat[k] = Monoid::op(dat[k<<1], dat[(k<<1) | 1]);
	}
	
	void calc_all() {
		for (int k = size-1; k > 0; k--) {
			dat[k] = Monoid::op(dat[k<<1], dat[(k<<1) | 1]);
		}
	}

	void updateall(T x) {
		for (int k = size; k < (size<<1); k++) {
			dat[k] = x;
		}
		calc_all();
	}

	void updateall(const vector<T> &val) {
		for (int k = 0; k < (int)val.size(); k++) {
			dat[k+size] = val[k];
		}
		calc_all();
	}

	void merge(int k, T x) { update(k, Monoid::op(x, dat[k + size])); }

	T get(int k) { return (dat[k+size]); }
	//[a, b)
	T query(int a, int b) {
		T tl = Monoid::id, tr = Monoid::id;
		for (int l = a + size, r = b + size; l < r; l >>= 1, r >>= 1) {
			if (l & 1) tl = Monoid::op(tl, dat[l++]);
			if (r & 1) tr = Monoid::op(dat[--r], tr);
		}
		return (Monoid::op(tl, tr));
	}
};

//クエリリスト

template<typename T>
struct RmQ {
	using valueType = T;
	static T op(T a, T b) { return (min(a, b)); }
	static inline T id = numeric_limits<T>::max();
};

template<typename T>
struct RMQ {
	using valueType = T;
	static T op(T a, T b) { return (max(a, b)); }
	static inline T id = numeric_limits<T>::lowest();
};

template<typename T>
struct RSQ {
	using valueType = T;
	static T op(T a, T b) { return (a+b); }
	static inline T id = 0;
};	

template<typename Data_t>
struct SumMaxQuery {
	using valueType = pair<Data_t, Data_t>;
	static valueType op(valueType a, valueType b) {
		if (a == id) return (b);
		if (b == id) return (a);
		return (valueType(max(a.first, b.first+a.second), a.second + b.second));
	}
	static inline valueType id = valueType(numeric_limits<Data_t>::lowest(), 0);
};

template<typename Data_t>
struct SumMinQuery {
	using valueType = pair<Data_t, Data_t>;
	static valueType op(valueType a, valueType b) {
		if (a == id) return (b);
		if (b == id) return (a);
		return (valueType(min(a.first, b.first+a.second), a.second + b.second));
	}
	static inline valueType id = valueType(numeric_limits<Data_t>::max(), 0);
};

template<unsigned int MOD>
struct RollingHashQuery {
	using Mint = Modint<MOD>;
	using T = pair<Mint, Mint>;
	using valueType = T;

	static inline T id = T(0, 1);
	static T op(T a, T b) {
		return (T(a.first*b.second + b.first, a.second * b.second));
	}
};


int main()
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	int N, Q;
	cin >> N >> Q;
	//RmQ
	SegmentTree<RmQ<int>> seg(N);

	while (Q--) {
		int com, a, b;
		cin >> com >> a >> b;
		if (com == 0) seg.update(a, b);
		else cout << seg.query(a, b + 1) << '\n';
	}
		
	return (0);
}
