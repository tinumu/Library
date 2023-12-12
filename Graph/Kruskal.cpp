#include <bits/stdc++.h>
using namespace std;

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

template<typename T>
T Kruskal(int V, vector<tuple<T, int, int>> edges) {
	sort(begin(edges), end(edges));
	Unionfind uf(V);

	T cost = 0;
	for (auto &[c, a, b] : edges) {
		if (!uf.same(a, b)) {
			uf.unite(a, b);
			cost += c;
		}
	}
	return (uf.size(0) == V ? cost : numeric_limits<T>::max());
}

//verified https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_12_A
int main() {
	int N; cin >> N;
	vector<tuple<int, int, int>> edges;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int cost; cin >> cost;
			if (i < j && cost != -1) edges.emplace_back(cost, i, j);
		}
	}
	cout << Kruskal(N, edges) << endl;
	return (0);
}
