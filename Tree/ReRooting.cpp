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
	vector<Node_t> node_data; //必要なときがあるかはわからないが入れておく。

	ReRooting(int N) : G(Graph(N)),
		sdp(vector<Node_t>(N, M::id)), dp(vector<Node_t>(N, M::id)),
		node_data(vector<Node_t>(N, M::id)) {}

	ReRooting(int N, const vector<Node_t> &dat) : G(Graph(N)),
		sdp(dat), dp(vector<Node_t>(N, M::id)),
		node_data(dat) {}

	//辺の向きごとにコストを変更できるが正しい dp になる？
	void add_edge(int from, int to, const Edge_t &cost) {
		G[from].push_back({to, cost, M::id, M::id});
	}
	void add_edge_both(int a, int b, const Edge_t &cost) {
		add_edge(a, b, cost);
		add_edge(b, a, cost);
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
		Node_t cur = node_data[u];
		for (int i = 0; i < (int)G[u].size(); i++) {
			auto &e = G[u][i];
			e.ndp = cur;
			e.dp = M::g(e.to == p ? d_par : sdp[e.to], e.cost);
			cur = M::f(cur, e.dp);
		}
		dp[u] = cur;
		cur = node_data[u];
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


