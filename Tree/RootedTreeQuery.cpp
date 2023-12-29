#include <bits/stdc++.h>
using namespace std;

//汎用性は今の所あんまないかも...
//木が辺のみの処理で、辺の構造が可換なモノイドのときはつかえる。
//更新クエリには対応していない

template<typename M>
struct RootedTree {
	using Edge_t = typename M::valueType;
	struct Edge {
		int to;
		Edge_t weight;
		Edge () {}
		Edge (int to, Edge_t weight) : to(to), weight(weight) {}
	};

	int size, bsize;
	vector<vector<Edge>> G;
	vector<vector<Edge>> parent;
	vector<int> depth;

	RootedTree(int N) : size(N) {
		G = decltype(G)(N);
		depth = vector<int>(N);
		bsize = 0;
		while ((1<<bsize) < N) bsize++;
		parent = decltype(parent)(bsize, vector<Edge>(N));
	}

	void add_edge(int from, int to, Edge_t weight) {
		G[from].emplace_back(to, weight);
		G[to].emplace_back(from, weight);
	}

	void makeDepthAndParent(int u, int p, Edge_t weight, int d) {
		depth[u] = d;
		parent[0][u] = Edge(p, weight);
		for (auto &v : G[u]) {
			if (v.to == p) continue;
			makeDepthAndParent(v.to, u, v.weight, d+1);
		}
	}

	void doubling() {
		for (int b = 1; b < bsize; b++) {
			for (int i = 0; i < size; i++) {
				if (parent[b-1][i].to == -1) {
					parent[b][i].to = -1;
					parent[b][i].weight = M::id;
				} else {
					parent[b][i].to = parent[b-1][parent[b-1][i].to].to;
					parent[b][i].weight = M::op(parent[b-1][i].weight, parent[b-1][parent[b-1][i].to].weight);
				}
			}
		}
	}

	void build(int root) {
		makeDepthAndParent(root, -1, M::id, 0);
		doubling();
	}

	int lca(int su, int sv) {
		if (depth[su] > depth[sv]) swap(su, sv);
		int sa = depth[sv] - depth[su];

		int u = su, v = sv;
		for (int b = 0; b < bsize; b++) {
			if ((sa>>b)&1) v = parent[b][v].to;
		}
		if (u == v) return (u);

		for (int b = bsize-1; b >= 0; b--) {
			if (parent[b][u].to != parent[b][v].to) {
				u = parent[b][u].to;
				v = parent[b][v].to;
			}
		}

		return (parent[0][u].to);
	}
	
	pair<int, Edge_t> getParent(int u) {
		return (pair<int, Edge_t>(parent[0][u].to, parent[0][u].weight));
	}

	//k 個前の祖先のクエリ
	pair<int, Edge_t> getAncestor(int u, int k) {
		Edge_t ret = M::id;
		k = min(k, depth[u]);
		for (int b = 0; b < bsize; b++) {
			if ((k>>b)&1) {
				ret = M::op(ret, parent[b][u].weight);
				u = parent[b][u].to;
			}
		}
		return (pair<int, Edge_t>(u, ret));
	}
	
	//数字が大きくなる系は使える (max, 正の重みの和)
	pair<int, Edge_t> getAncestorDist(int u, Edge_t dist) {
		int ku = u;
		Edge_t uw = M::id;
		for (int b = bsize-1; b >= 0; b--) {
			if (parent[b][ku].to == -1) continue;
			if (M::op(parent[b][ku].weight, uw) <= dist) {
				uw = M::op(uw, parent[b][ku].weight);
				ku = parent[b][ku].to;
			}
		}
		return (make_pair(ku, uw));
	}

	Edge_t query(int u, int v) {
		Edge_t ret = M::id;
		int r = lca(u, v);
		int sau = depth[u] - depth[r];
		int sav = depth[v] - depth[r];

		for (int b = 0; b < bsize; b++) {
			if ((sau>>b)&1) {
				ret = M::op(ret, parent[b][u].weight);
				u = parent[b][u].to;
			}
			if ((sav>>b)&1) {
				ret = M::op(ret, parent[b][v].weight);
				v = parent[b][v].to;
			}
		}

		return (ret);
	}
};

template<typename T>
struct RMQ {
	using valueType = T;
	static inline T id = -numeric_limits<T>::max();
	static T op(T a, T b) { return (max(a, b)); }
};

template<typename T>
struct RSQ {
	using valueType = T;
	static inline T id = 0;
	static T op(T a, T b) { return (a+b); }
};


//ここまで======================================================================

//veryfied with https://atcoder.jp/contests/abc235/tasks/abc235_e (MST+1)
//ここからverify用のコード======================================================
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


int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	int N, M, Q; cin >> N >> M >> Q;
	Unionfind tree(N);
	vector<tuple<int, int, int>> edges;
	for (int i = 0; i < M; i++) {
		int a, b, c; cin >> a >> b >> c; --a, --b;
		edges.emplace_back(c, a, b);
	}
	sort(begin(edges), end(edges));
	RootedTree<RMQ<long long>> rtree(N);
	for (int i = 0; i < M; i++) {
		auto [c, a, b] = edges[i];
		if (!tree.same(a, b)) {
			tree.unite(a, b);
			rtree.add_edge(a, b, c);
		}
	}

	rtree.build(0);
	while (Q--) {
		int u, v;
		long long w; cin >> u >> v >> w; --u, --v;
		if (u != v && w < rtree.query(u, v)) {
			cout << "Yes" << '\n';
		} else {
			cout << "No" << '\n';
		}
	}
	return (0);
}
