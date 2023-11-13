#include <bits/stdc++.h>
using namespace std;

//Please copy under code.

template<typename T>
struct WeightedUnionfind {
	vector<int> data;
	vector<T> weight;
	
	WeightedUnionfind() {}
	WeightedUnionfind(int n, T id = 0) {
		data.assign(n, -1);
		weight.assign(n, id);
	}

	int root(int n) {
		if (data[n] < 0) return (n);
		int r = root(data[n]);
		weight[n] += weight[data[n]];
		return (data[n] = r);
	}

	int size(int n) { return (-data[root(n)]); };
	bool same(int x, int y) { return (root(x) == root(y)); }
	T getWeight(int x) { root(x); return (weight[x]); }

	//同じ連結成分に含まれているときに使う
	//x -> y の差分を取る w_y-w_x
	T diff(int x, int y) { return (getWeight(y) - getWeight(x)); }
	
	//x -> y に w を追加
	void unite(int x, int y, T w) {
		int rx = root(x), ry = root(y);
		if (rx == ry) return;

		if (data[rx] > data[ry]) {
			swap(rx, ry);
			swap(x, y);
			w = -w;
		}
		weight[ry] = w - (weight[y] - weight[x]);
		data[rx] += data[ry];
		data[ry] = rx;
	}
};

//verified https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_B
int main() {
	using ll = long long;
	int N, Q; cin >> N >> Q;
	WeightedUnionfind<ll> tree(N);
	while (Q--) {
		int t; cin >> t;
		if (t == 0) {
			int x, y;
			ll z; cin >> x >> y >> z;
			tree.unite(x, y, z);
		} else {
			int x, y; cin >> x >> y;
			if (!tree.same(x, y)) {
				cout << "?" << '\n';
			} else {
				cout << tree.diff(x, y) << '\n';
			}
		}
	}
	return (0);
}
