#include <bits/stdc++.h>
using namespace std;

template < typename T >
struct Edge {
    int from, to;
    T cost;
    Edge () {}
    Edge (int from, int to, T cost) : from(from), to(to), cost(cost) {}
	Edge (int to, T cost) : from(-1), to(to), cost(cost) {}
};

template < typename T >
vector<T> Dijkstra(int V, vector<vector<Edge<T>>> &G, int s) {
	using Node = pair<T, int>;
    constexpr T INF = numeric_limits<T>::max();
    vector<T> d(V, INF);
	priority_queue<Node, vector<Node>, greater<Node>> pq;

    d[s] = 0;
	pq.emplace(0, s);
	while (!pq.empty()) {
		Node node = pq.top(); pq.pop();
		for (auto &e : G[node.second]) {
			int cost = e.cost + node.first;
			if (cost < d[e.to]) {
				d[e.to] = cost;
				pq.emplace(e.to, cost);
			}
		}
	}
		
    return (d);
}

