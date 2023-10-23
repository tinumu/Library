#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Edge {
	int from, to;
	T cost;
	Edge () {}
	Edge (int from, int to, T cost ) : from(from), to(to), cost(cost) {}
	Edge (int to, T cost) : from(-1), to(to), cost(cost) {}
};

	template<typename T>
vector<T> BellmanFord(int V, vector<Edge<T>> &edges, int s)
{
	constexpr T INF = numeric_limits<T>::max();
	vector<T> d(V, INF);
	d[s] = 0;
	for (int i = 0; i < V; i++) {
		for (auto &e : edges) {
			if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
				d[e.to] = d[e.from] + e.cost;
				if (i == V - 1) return (vector<T>());
			}
		}
	}
	return (d);
}

