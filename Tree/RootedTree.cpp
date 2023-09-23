#include <bits/stdc++.h>
using namespace std;

//veryfied with https://atcoder.jp/contests/abc235/tasks/abc235_e (MST+1)
//汎用性は今の所あんまないかも...
//木が辺のみの処理で、辺の構造が可換なモノイドのときはつかえる。
//非可換なときはまだ試してない。一応計算できるようには書いているとは思うけど
//更新クエリには対応していない

template<typename Edge_t>
struct RootedTree {
	struct Edge {
		int to;
		Edge_t cost;
		Edge () {}
		Edge (int to, Edge_t cost) : to(to), cost(cost) {}
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
	
	void add_edge(int from, int to, Edge_t cost) {
		G[from].emplace_back(to, cost);
		G[to].emplace_back(from, cost);
	}
	
	void makeDepthAndParent(int u, int p, Edge_t cost, int d) {
		depth[u] = d;
		parent[u][0] = Edge(p, cost);
		for (auto &v : G[u]) {
			if (v.to == p) continue;
			makeDepthAndParent(v.to, u, v.cost, d+1);
		}
	}

	void doubling() {
		for (int b = 1; b < bsize; b++) {
			for (int i = 0; i < size; i++) {
				parent[i][b].to = parent[max(0, parent[i][b-1].to)][b-1].to;
				parent[i][b].cost = op(parent[i][b-1].cost, parent[max(0, parent[i][b-1].to)][b-1].cost);
			}
		}
	}

	void build() {
		makeDepthAndParent(0, -1, id, 0);
		doubling();
	}

	int lca(int su, int sv) {
		if (depth[su] > depth[sv]) swap(su, sv);
		int sa = depth[sv] - depth[su];

		int u = su, v = sv;
		for (int b = 0; b < bsize; b++) {
			if ((sa>>b)&1) v = parent[v][b].to;
		}

		int ng = -1, ok = depth[u];
		while (abs(ng-ok) > 1) {
			int back = (ng+ok)/2;
			int nu = u, nv = v;
			for (int b = 0; b < bsize; b++) {
				if ((back>>b)&1) {
					nu = parent[nu][b].to;
					nv = parent[nv][b].to;
				}
			}
			if (nu == nv) ok = back;
			else ng = back;
		}
		for (int b = 0; b < bsize; b++) {
			if ((ok>>b)&1) u = parent[u][b].to;
		}
		return (u);
	}

	Edge_t query(int u, int v) {
		Edge_t retu = id, retv = id;
		int r = lca(u, v);
		int sau = depth[u] - depth[r];
		int sav = depth[v] - depth[r];

		for (int b = 0; b < bsize; b++) {
			if ((sau>>b)&1) {
				retu = op(retu, parent[u][b].cost);
				u = parent[u][b].to;
			}
			if ((sav>>b)&1) {
				retv = op(parent[v][b].cost, retv);
				v = parent[v][b].to;
			}
		}

		return (op(retu, retv));
	}
};

//ここまで======================================================================

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

	rtree.build();
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
