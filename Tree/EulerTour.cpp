#include <bits/stdc++.h>
using namespace std;

struct EulerTour {
	int size;
	vector<vector<pair<int, int>>> G;
	vector<int> depth;
	vector<pair<int, int>> node_index;
	vector<pair<int, int>> edge_index;
	vector<tuple<int, int, int>> tour; //エンドポイント, エッジ, (進む : 1, 戻る : -1)

	EulerTour(int N) : size(N), G(N), depth(N), node_index(N), edge_index(N-1), tour(2*N-1) {}

	void add_edge(int u, int v, int j) {
		G[u].emplace_back(v, j);
		G[v].emplace_back(u, j);
	}
	
	void build(int u, int p, int d) {
		static int i = 1;
		depth[u] = d;
		for (auto &[v, j] : G[u]) {
			if (v == p) continue;
			node_index[v].first = i;
			edge_index[j].first = i;
			tour[i] = tuple<int, int, int>(v, j, 1);
			i++;

			build(v, u, d+1);

			node_index[v].second = i;
			edge_index[j].second = i;
			tour[i] = tuple<int, int, int>(u, j, -1);
			i++;
		}
	}

	void build() {
		node_index[0] = pair<int, int>(0, 2*size-1);
		tour[0] = tuple<int, int, int>(0, -1, 1);
		build(0, -1, 0);
	}
};

//verified https://judge.yosupo.jp/problem/lca
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
		for (int k = 0; k < val.size(); k++) {
			dat[k+size] = val[k];
		}
		calc_all();
	}

	void merge(int k, T x) { update(k, Monoid::op(x, dat[k + size])); }
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

struct RmQ {
	using valueType = pair<int, int>;
	static valueType op(valueType a, valueType b) { return (min(a, b)); }
	static inline valueType id = pair<int, int>(1<<30, 1<<30);
};

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	int N, Q; cin >> N >> Q;
	EulerTour euler(N);
	for (int i = 1; i < N; i++) {
		int p; cin >> p;
		euler.add_edge(i, p, i-1);
	}
	euler.build();
	SegmentTree<RmQ> seg(2*N-1);
	vector<pair<int, int>> dat(2*N-1);
	for (int i = 0; i < 2*N-1; i++) {
		dat[i] = pair<int, int>(euler.depth[get<0>(euler.tour[i])], i);
	}
	seg.updateall(dat);
	while (Q--) {
		int u, v; cin >> u >> v;
		int x = euler.node_index[u].first;
		int y = euler.node_index[v].first;
		int lca = seg.query(min(x, y), max(x, y)+1).second;
		cout << get<0>(euler.tour[lca]) << '\n';
	}

	return (0);
}
