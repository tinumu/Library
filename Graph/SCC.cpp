#include <bits/stdc++.h>
using namespace std;

//StronglyConnectedComponent(強連結成分分解)
//エッジを入れてビルドすると、閉路を１ノードにまとめたDAGを形成する

struct SCC {
	vector<vector<int>> G;
	vector<vector<int>> rG;
	vector<vector<int>> indexes;
	vector<int> group;
	vector<vector<int>> newG;
	int newsize;
	int size;
	
	SCC(int n) : size(n) {
		G = decltype(G)(n);
		rG = decltype(rG)(n);
		group = decltype(group)(n);
	}

	void add_edge(int u, int v) {
		G[u].push_back(v);
		rG[v].push_back(u);
	}
	
	void build() {	

		vector<int> number;
		vector<bool> flag(size, false);

		function<void(int)> numbering = [&](int u) {
			if (flag[u]) return;
			flag[u] = true;
			for (auto &v : G[u]) {
				numbering(v);
			}
			number.push_back(u);
		};

		function<void(int, int)> nodeBuild = [&](int u, int nu) {
			if (flag[u]) return;
			flag[u] = true;
			group[u] = nu;
			indexes[nu].push_back(u);
			for (auto &v : rG[u]) {
				nodeBuild(v, nu);
			}
		};

		for (int u = 0; u < size; u++) {
			numbering(u);
		}
		reverse(begin(number), end(number));

		flag.assign(size, false);
		int cnt = 0; 
		for (auto &u : number) {
			if (!flag[u]) {
				indexes.push_back(vector<int>());
				nodeBuild(u, cnt);
				cnt++;
			}
		}
	
		newsize = cnt;
		vector<int> nflag(cnt, -1);
		newG = decltype(newG)(cnt);

		// edge build
		for (int nu = 0; nu < cnt; nu++) {
			for (auto &u : indexes[nu]) {
				for (auto &v : G[u]) {
					int nv = group[v];
					if (nu == nv) continue;
					if (nflag[nv] != nu) {
						nflag[nv] = nu;
						newG[nu].push_back(nv);
					}
				}
			}
		}
	}
};

//verified https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_C
//辺がちゃんと張られているかは https://atcoder.jp/contests/abc245/tasks/abc245_f 辺りで試しはした。
//間接的な試しではあるのでちゃんとverifyはされてない

int main() {
	int V, E; cin >> V >> E;
	SCC scc(V);
	for (int i = 0; i < E; i++) {
		int s, t; cin >> s >> t;
		scc.add_edge(s, t);
	}
	scc.build();
	int Q; cin >> Q;
	for (int i = 0; i < Q; i++) {
		int u, v; cin >> u >> v;
		if (scc.group[u] == scc.group[v]) {
			cout << 1 << '\n';
		} else {
			cout << 0 << '\n';
		}
	}
	return (0);
}
