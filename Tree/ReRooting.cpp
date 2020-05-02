#include <bits/stdc++.h>
using namespace std;

template<typename Node_t, typename Edge_t>
struct ReRooting {
	struct Edge {
		int to;
		Edge_t cost;
		Node_t ndp, dp;
	};

	using F1 = function<Node_t(Node_t, Node_t)>;
	using F2 = function<Node_t(Node_t, Edge_t)>;
	using Graph = vector<vector<Edge>>;

	Graph G;
	F1 f1; F2 f2;
	Node_t id;	
	vector<Node_t> sdp, dp;

	ReRooting(int N, F1 f1, F2 f2, Node_t id) : f1(f1), f2(f2), id(id), G(Graph(N)), 
		sdp(vector<Node_t>(N, id)), dp(vector<Node_t>(N, id)) {}
	
	void add_edge(int from, int to, const Edge_t &cost) {
		G[from].push_back({to, cost, id, id});
		G[to].push_back({from, cost, id, id});
	}
	
	void dfs1(int u, int p) {
		for (auto &e : G[u]) {
			if (e.to != p) {
				dfs1(e.to, u);
				sdp[u] = f1(sdp[u], f2(sdp[e.to], e.cost));
			}
		}
	}
	
	void dfs2(int u, Node_t d_par, int p) {
		Node_t cur{id};
		for (int i = 0; i < (int)G[u].size(); i++) {
			auto &e = G[u][i];
			e.ndp = cur;
			e.dp = f2(e.to == p ? d_par : sdp[e.to], e.cost);
			cur = f1(cur, e.dp);
		}
		dp[u] = cur;
		cur = id;	
		for (int i = (int)G[u].size()-1; i >= 0; i--) {
			auto &e = G[u][i];
			if (e.to != p) dfs2(e.to, f1(cur, e.ndp), u);
			e.ndp = f1(cur, e.ndp);
			cur = f1(cur, e.dp);
		}
	}

	vector<Node_t> build() {
		dfs1(0, -1);
		dfs2(0, id, -1);
		return (dp);
	}
};

