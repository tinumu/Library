#include <bits/stdc++.h>
using namespace std;

struct RootedTree {
	int size, bsize;
	vector<vector<int>> G;	
	vector<vector<int>> parent;
	vector<int> depth;

	RootedTree(int N) : size(N) {
		G = decltype(G)(N);
		depth = vector<int>(N);
		bsize = 0;
		while ((1<<bsize) < N) bsize++;
		parent = decltype(parent)(N, vector<int>(bsize));
	}
	
	void add_edge(int from, int to) {
		G[from].push_back(to);
		G[to].push_back(from);
	}
	
	void makeDepthAndParent(int u, int p, int d) {
		depth[u] = d;
		parent[u][0] = p;
		for (auto &v : G[u]) {
			if (v == p) continue;
			makeDepthAndParent(v, u, d+1);
		}
	}

	void doubling() {
		for (int b = 1; b < bsize; b++) {
			for (int i = 0; i < size; i++) {
				if (parent[i][b-1] == -1) {
					parent[i][b] = -1;
				} else {
					parent[i][b] = parent[parent[i][b-1]][b-1];
				}
			}
		}
	}

	void build(int root) {
		makeDepthAndParent(root, -1, 0);
		doubling();
	}

	int lca(int su, int sv) {
		if (depth[su] > depth[sv]) swap(su, sv);
		int sa = depth[sv] - depth[su];

		int u = su, v = sv;
		for (int b = 0; b < bsize; b++) {
			if ((sa>>b)&1) v = parent[v][b];
		}
		if (u == v) return (u);
	
		for (int b = bsize-1; b >= 0; b--) {
			if (parent[u][b] != parent[v][b]) {
				u = parent[u][b];
				v = parent[v][b];
			}
		}

		return (parent[u][0]);
	}

};

//verified https://judge.yosupo.jp/problem/lca (結構遅そうだけど)
//Euler Tour の実装のほうが早そう？

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	int N, Q; cin >> N >> Q;

	RootedTree rtree(N);
	for (int i = 1; i < N; i++) {
		int p; cin >> p;
		rtree.add_edge(p, i);
	}

	rtree.build(0);
	for (int i = 0; i < Q; i++) {
		int u, v; cin >> u >> v;
		cout << rtree.lca(u, v) << '\n';
	}
	return (0);
}
