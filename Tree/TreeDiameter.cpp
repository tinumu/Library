#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Edge {
	int to;
	T cost;
	Edge () {}
	Edge (int to, T cost) : to(to), cost(cost) {}
};

template<typename T>
struct TreeDiameter {
	using Graph = vector<vector<Edge<T>>>;
	using Data = pair<T, int>;

	Graph G;
	T diameter;
	int enda, endb;
	vector<int> paths;	

	Data getHeight(int u, int p) {
		pair<T, int> h = make_pair((T)0, u);
		for (auto &[v, cost] : G[u]) {
			if (v == p) continue;
			auto ret = getHeight(v, u);
			ret.first += cost;
			h = max(h, ret);
		}
		return (h);
	}

	TreeDiameter(const Graph &G) : G(G) {
		Data a = getHeight(0, -1);
		Data b = getHeight(a.second, -1);
		diameter = b.first;
		enda = a.second, endb = b.second;
	}
	
	bool pathdfs(int u, int p) {
		if (u == endb) {
			paths.push_back(u);
			return (true);
		}
		for (auto &[v, c] : G[u]) {
			if (v == p) continue;
			if (pathdfs(v, u)) {
				paths.push_back(u);
				return (true);
			}
		}
		return (false);
	}
	vector<int> getPaths() {
		if (paths.size() > 0) return (paths);
		pathdfs(enda, -1);
		reverse(begin(paths), end(paths));
		return (paths);
	}
	T getDiameter() {
		return (diameter);
	}
};

//verified https://judge.yosupo.jp/problem/tree_diameter
int main() {
	using ll = long long;
	int N; cin >> N;
	vector<vector<Edge<ll>>> G(N);
	for (int i = 0; i < N-1; i++) {
		int a, b; ll c; cin >> a >> b >> c;
		G[a].emplace_back(b, c);
		G[b].emplace_back(a, c);
	}
	TreeDiameter<ll> td(G);
	auto paths = td.getPaths();
	
	cout << td.getDiameter() << " " << paths.size() << endl;
	cout << paths[0];
	for (int i = 1; i < paths.size(); i++) {
		cout << " " << paths[i];
	}
	cout << endl;
}
