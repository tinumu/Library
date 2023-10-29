#include <bits/stdc++.h>
using namespace std;

struct LowLink {
	using Graph = vector<vector<int>>;
	Graph G;
	vector<int> ord;
	vector<int> low;
	vector<int> used;
	
	vector<pair<int, int>> bridges;
	vector<int> aps;

	LowLink(const Graph &G) : G(G) {
		ord.resize(G.size());
		low.resize(G.size());
		used.assign(G.size(), 0);
		int k = 0;
		for (int i = 0; i < G.size(); i++) {
			if (!used[i]) k = dfs(i, k, -1);
		}
		sort(begin(aps), end(aps));
		sort(begin(bridges), end(bridges));
	}
	
	int dfs(int u, int k, int p) {
		used[u] = true;
		ord[u] = k++;
		low[u] = ord[u];
		bool is_aps = false;
		int cnt = 0;
		int pnum = 0;
		for (auto &v : G[u]) {
			if (!used[v]) {
				cnt++;
				k = dfs(v, k, u);
				low[u] = min(low[u], low[v]);
				if (ord[u] < low[v]) bridges.emplace_back(min(u, v), max(u, v));
				if (p != -1 && ord[u] <= low[v]) is_aps = true;
			} else if (v != p || pnum >= 1) {
				low[u] = min(low[u], low[v]);
			} else {
				pnum++;
			}
		}
		if (p == -1 && cnt >= 2) is_aps = true;
		if (is_aps) aps.push_back(u);
		return (k);
	}
};

//verified with https://judge.yosupo.jp/problem/two_edge_connected_components

int main() {
	int N, M; cin >> N >> M;
	vector<vector<int>> G(N);
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	LowLink llink(G);
	
	auto &bridges = llink.bridges;

	vector<int> flag(N, 0);
	vector<int> ans;
	vector<vector<int>> anses;
	function<void(int)> dfs = [&](int u) {
		flag[u] = true;
		ans.push_back(u);
		for (auto &v : G[u]) {
			if (flag[v]) continue;
			if (binary_search(begin(bridges), end(bridges), pair<int, int>(min(u, v), max(u, v)))) {
				continue;
			}
			dfs(v);
		}
	};
	for (int i = 0; i < N; i++) {
		if (!flag[i]) {
			ans.resize(0);
			dfs(i);
			anses.push_back(ans);
		}
	}
	cout << anses.size() << '\n';
	for (auto &d : anses) {
		cout << d.size();
		for (int i = 0; i < d.size(); i++) {
			cout << " " << d[i];
		}
		cout << '\n';
	}
}
