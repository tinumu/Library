#include <bits/stdc++.h>
using namespace std;

//汎用性は今の所あんまないかも...
//木が辺のみの処理で、辺の構造が可換なモノイドのときはつかえる。
//更新クエリには対応していない

template<typename Edge_t>
struct RootedTree {
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
	function<Edge_t(Edge_t, Edge_t)> op;
	Edge_t id;

	RootedTree(int N, Edge_t id, function<Edge_t(Edge_t, Edge_t)> op) : size(N), op(op), id(id) {
		G = decltype(G)(N);
		depth = vector<int>(N);
		bsize = 0;
		while ((1<<bsize) < N) bsize++;
		parent = decltype(parent)(N, vector<Edge>(bsize));
	}
	
	void add_edge(int from, int to, Edge_t weight) {
		G[from].emplace_back(to, weight);
		G[to].emplace_back(from, weight);
	}
	
	void makeDepthAndParent(int u, int p, Edge_t weight, int d) {
		depth[u] = d;
		parent[u][0] = Edge(p, weight);
		for (auto &v : G[u]) {
			if (v.to == p) continue;
			makeDepthAndParent(v.to, u, v.weight, d+1);
		}
	}

	void doubling() {
		for (int b = 1; b < bsize; b++) {
			for (int i = 0; i < size; i++) {
				if (parent[i][b-1].to == -1) {
					parent[i][b].to = -1;
					parent[i][b].weight = id;
				} else {
					parent[i][b].to = parent[parent[i][b-1].to][b-1].to;
					parent[i][b].weight = op(parent[i][b-1].weight, parent[parent[i][b-1].to][b-1].weight);
				}
			}
		}
	}

	void build(int root) {
		makeDepthAndParent(root, -1, id, 0);
		doubling();
	}

	int lca(int su, int sv) {
		if (depth[su] > depth[sv]) swap(su, sv);
		int sa = depth[sv] - depth[su];

		int u = su, v = sv;
		for (int b = 0; b < bsize; b++) {
			if ((sa>>b)&1) v = parent[v][b].to;
		}
		if (u == v) return (u);
	
		for (int b = bsize-1; b >= 0; b--) {
			if (parent[u][b].to != parent[v][b].to) {
				u = parent[u][b].to;
				v = parent[v][b].to;
			}
		}

		return (parent[u][0].to);
	}

	Edge_t query(int u, int v) {
		Edge_t ret = id;
		int r = lca(u, v);
		int sau = depth[u] - depth[r];
		int sav = depth[v] - depth[r];

		for (int b = 0; b < bsize; b++) {
			if ((sau>>b)&1) {
				ret = op(ret, parent[u][b].weight);
				u = parent[u][b].to;
			}
			if ((sav>>b)&1) {
				ret = op(ret, parent[v][b].weight);
				v = parent[v][b].to;
			}
		}

		return (ret);
	}
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
	RootedTree<long long> rtree(N, (long long)(-2e18), [](long long a, long long b) { return (max(a, b)); });
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
