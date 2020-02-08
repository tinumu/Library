#include <bits/stdc++.h>
using namespace std;

//Please copy under code!

template<typename T>
struct Dinic {
	struct Edge {
		int to, rev;
		T cap;
		Edge () {}
		Edge (int to, int rev, T cap) : to(to), rev(rev), cap(cap) {}
	};

	vector<vector<Edge>> G;
	vector<int> level, itr;
	const T INF;
	int V;

	Dinic(int size) : V(size), INF(numeric_limits<T>::max()), timestamp(0) {
		G.resize(size);
	}

	void add_edge(int from, int to, T cap) {
		G[from].emplace_back(to, (int)G[to].size(), cap);
		G[to].emplace_back(from, (int)G[from].size() - 1, 0);
	}

	void bfs(int s) {
		level.assign(V, -1);
		queue<int> que;

		level[s] = 0; que.push(s);
		while (!que.empty()) {
			int v = que.front(); que.pop();
			for (auto &e : G[v]) {
				if (e.cap > 0 && level[e.to] == -1) {
					level[e.to] = level[v] + 1;
					que.push(e.to);
				}
			}
		}
	}

	T dfs(int v, int t, T flow) {
		if (v == t) return (flow);
		for (int& i = itr[v]; i < (int)G[v].size(); i++) {
			Edge &e = G[v][i];
			if (e.cap > 0 && level[e.to] > level[v]) {
				T d = dfs(e.to, t, min(flow, e.cap));
				if (d > 0) {
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return (d);
				}
			}
		}
		return (0);
	}

	T max_flow(int s, int t) {
		T flow = 0, f;
		while (bfs(s), level[t] >= 0) {
			itr.assign(V, 0);
			while ((f = dfs(s, t, INF)) > 0) flow += f;
		}
		return (flow);
	}
};

//Please copy above code!

//verify用のソースコードはei1333さんのものを借りました
//verified with http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
int main() {
	int V, E;
	scanf("%d %d", &V, &E);
	Dinic< int > g(V);
	for(int i = 0; i < E; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		g.add_edge(a, b, c);
	}
	printf("%d\n", g.max_flow(0, V - 1));
}
