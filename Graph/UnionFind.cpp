#include <bits/stdc++.h>
using namespace std;

//Please copy under code!

struct Unionfind {
	vector<int> data;
	
	Unionfind() {}
	Unionfind(int n) { data.assign(n, -1); }

	int root(int n) {
		if (data[n] < 0) return (n);
		return (data[n] = root(data[n]));
	}

	int size(int n) { return (-data[root(n)]); };
	bool same(int x, int y) { return (root(x) == root(y)); }

	void unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) return;
		if (data[x] > data[y]) swap(x, y);
		data[x] += data[y];
		data[y] = x;
	}
};

//verified with https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_A
int main() {
	int n, q;
	cin >> n >> q;
	Unionfind tree(n);
	for (int i = 0; i < q; i++) {
		int c, x, y;
		cin >> c >> x >> y;
		if (c == 0) tree.unite(x, y);
		else cout << tree.same(x, y) << endl;
	}
	return (0);
}
