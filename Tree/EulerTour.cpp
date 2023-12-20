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

//verify しよう
