#include <bits/stdc++.h>
using namespace std;

template<typename SemiGroup>
struct SparseTable {
	using T = typename SemiGroup::valueType;
	T** table;
	int* logtable;
	int bsize;
	SparseTable(const vector<T> &dat) {
		bsize = 0;
		int n = dat.size();
		while ((1<<bsize) <= n) bsize++;
		table = new T*[bsize];
		logtable = new int[n+1];
		
		table[0] = new T[n];
		for (int i = 0; i < n; i++) {
			table[0][i] = dat[i];
		}
		for (int b = 1; b < bsize; b++) {
			int t = (1<<(b-1));
			table[b] = new T[n];
			for (int i = 0; i < n - t; i++) {
				table[b][i] = SemiGroup::op(table[b-1][i], table[b-1][i+t]);
			}
		}
		for (int i = 2; i <= n; i++) {
			logtable[i] = logtable[i>>1] + 1;
		}
	}

	~SparseTable() {
		for (int i = 0; i < bsize; i++) {
			delete [] table[i];
		}
		delete[] table;
		delete[] logtable;
	}
	
	//[l, r)
	T query(int l, int r) {
		int length = r - l;
		return (SemiGroup::op(table[logtable[length]][l], table[logtable[length]][r-(1<<logtable[length])]));
	}
};

template<typename T>
struct RmQ {
	using valueType = T;
	static T op(T a, T b) { return (min(a, b)); }
};

//verified https://judge.yosupo.jp/problem/staticrmq
int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int N, Q; cin >> N >> Q;
	vector<int> A(N);
	for (auto &a : A) cin >> a;

	SparseTable<RmQ<int>> rmq(A);
	
	while (Q--) {
		int l, r; cin >> l >> r;
		cout << rmq.query(l, r) << '\n';
	}
	return (0);
}
