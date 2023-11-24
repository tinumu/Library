#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct PartialPersistentUnionfind {
	vector<int> data;
	vector<vector<pair<T, int>>> tsize;
	vector<T> update_time;

	PartialPersistentUnionfind() {}
	PartialPersistentUnionfind(int n) {
		data.assign(n, -1);
		tsize.resize(n);
		T infinity = numeric_limits<T>::max();
		for (int i = 0; i < n; i++) {
			tsize[i].emplace_back(-infinity, -1);
		}
		update_time.assign(n, infinity);
	}

	int root(int n, T t) {
		if (t < update_time[n]) return (n);
		return (root(data[n], t));
	}

	int size(int n, T t) {
		n = root(n, t);
		return (-prev(lower_bound(begin(tsize[n]), end(tsize[n]), pair<T, int>(t, 0)))->second);
	};

	bool same(int x, int y, T t) { return (root(x, t) == root(y, t)); }

	//unite するときは t を昇順に入れる
	void unite(int x, int y, T t) {
		x = root(x, t), y = root(y, t);
		if (x == y) return;
		if (data[x] > data[y]) swap(x, y);

		data[x] += data[y];
		data[y] = x;
		update_time[y] = t;
		tsize[x].emplace_back(t, data[x]);
	}
};

//verified? https://atcoder.jp/contests/agc002/tasks/agc002_d
int main() {
	int N, M; cin >> N >> M;

	PartialPersistentUnionfind<int> ppuf(N);
	for (int i = 0; i < M; i++) {
		int A, B; cin >> A >> B; --A, --B;
		ppuf.unite(A, B, i+1);
	}

	int Q; cin >> Q;
	while (Q--) {
		int x, y, z; cin >> x >> y >> z; --x, --y;
		int ok = M, ng = 0;
		while (abs(ok-ng) > 1) {
			int t = (ok+ng) / 2;
			int size = ppuf.size(x, t);

			if (!ppuf.same(x, y, t)) size += ppuf.size(y, t);
			if (size >= z) ok = t;
			else ng = t;
		}
		cout << ok << '\n';
	}
}
