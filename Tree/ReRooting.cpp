#include <bits/stdc++.h>
using namespace std;

template<typename M>
struct ReRooting {
	using Node_t = typename M::valueTypeNode;
	using Edge_t = typename M::valueTypeEdge;
	struct Edge {
		int to;
		Edge_t cost;
		Node_t ndp, dp;
	};

	using Graph = vector<vector<Edge>>;

	Graph G;
	vector<Node_t> sdp, dp;

	ReRooting(int N) : G(Graph(N)),
		sdp(vector<Node_t>(N, M::id)), dp(vector<Node_t>(N, M::id)) {}

	void add_edge(int from, int to, const Edge_t &cost) {
		G[from].push_back({to, cost, M::id, M::id});
		G[to].push_back({from, cost, M::id, M::id});
	}

	void dfs1(int u, int p) {
		for (auto &e : G[u]) {
			if (e.to != p) {
				dfs1(e.to, u);
				sdp[u] = M::f(sdp[u], M::g(sdp[e.to], e.cost));
			}
		}
	}

	void dfs2(int u, Node_t d_par, int p) {
		Node_t cur{M::id};
		for (int i = 0; i < (int)G[u].size(); i++) {
			auto &e = G[u][i];
			e.ndp = cur;
			e.dp = M::g(e.to == p ? d_par : sdp[e.to], e.cost);
			cur = M::f(cur, e.dp);
		}
		dp[u] = cur;
		cur = M::id;
		for (int i = (int)G[u].size()-1; i >= 0; i--) {
			auto &e = G[u][i];
			if (e.to != p) dfs2(e.to, M::f(cur, e.ndp), u);
			e.ndp = M::f(cur, e.ndp);
			cur = M::f(cur, e.dp);
		}
	}

	vector<Node_t> build() {
		dfs1(0, -1);
		dfs2(0, M::id, -1);
		return (dp);
	}
};

