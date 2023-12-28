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
				low[u] = min(low[u], ord[v]);
			} else {
				pnum++;
			}
		}
		if (p == -1 && cnt >= 2) is_aps = true;
		if (is_aps) aps.push_back(u);
		return (k);
	}
};

struct BiconnectedComponents {
	using Graph = vector<vector<int>>;
	LowLink llink;
	vector<vector<int>> components;
	vector<vector<int>> groups;
	vector<int> used;
	vector<pair<int, int>> tmp;
	int groupsize;

	BiconnectedComponents(const Graph &G) : llink(G), groups(G.size()), used(G.size()) {
		groupsize = 0;
		for (int i = 0; i < G.size(); i++) {
			if (!used[i]) {
				if (G[i].size() == 0) {
					components.push_back({i});
					groups[i].push_back(groupsize);
					groupsize++;
					used[i] = true;
				} else {
					dfs(i, -1);
				}
			}
		}
		for (auto &component : components) {
			sort(begin(component), end(component));
			component.erase(unique(begin(component), end(component)), end(component));
		}
		for (auto &group : groups) {
			if (group.size() > 1) {
				sort(begin(group), end(group));
				group.erase(unique(begin(group), end(group)), end(group));
			}
		}
	}

	void dfs(int u, int p) {
		used[u] = true;
		for (auto &v : llink.G[u]) {
			if (v == p) continue;
			if (!used[v]) {
				tmp.emplace_back(min(u, v), max(u, v));
				dfs(v, u);
				if (llink.ord[u] > llink.low[v]) continue;
				components.push_back({});
				while (true) {
					auto &[a, b] = tmp.back();
					components.back().emplace_back(a);
					components.back().emplace_back(b);
					groups[a].push_back(groupsize);
					groups[b].push_back(groupsize);
					tmp.pop_back();
					if (min(u, v) == a && max(u, v) == b) break;
				}
				groupsize++;
			}
		}
	}
};

int main() {
	int N, M; cin >> N >> M;
	vector<vector<int>> G(N);
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	BiconnectedComponents bc(G);
	cout << bc.groupsize << '\n';
	for (int i = 0; i < bc.groupsize; i++) {
		cout << bc.components[i].size();
		for (auto &u : bc.components[i]) {
			cout << ' ' << u;
		}
		cout << '\n';
	}
}
