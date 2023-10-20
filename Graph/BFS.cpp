#include <bits/stdc++.h>
using namespace std;

using Pi = pair<int, int>;

template<typename T>
struct Edge {
	int from, to;
	T cost;
	Edge () {}
	Edge (int from, int to, T cost) : from(from), to(to), cost(cost) {}
	Edge (int to, T cost) : from(-1), to(to), cost(cost) {}
};

//オーバーフローに気をつける
template<typename T>
vector<T> BFS(int V, const vector<vector<Edge<T>>> &G, int s) {
	using Node = pair<T, int>;
	constexpr T INF = numeric_limits<T>::max();
	vector<T> d(V, INF);
	deque<Node> deq;

	d[s] = 0;
	deq.emplace_back(0, s);
	while (!deq.empty()) {
		Node node = deq.front(); deq.pop_front();
		if (d[node.second] < node.first) continue;
		for (auto &e : G[node.second]) {
			T cost = e.cost + node.first;
			if (cost < d[e.to]) {
				d[e.to] = cost;
				if (e.cost == 0) deq.emplace_front(cost, e.to);
				else deq.emplace_back(cost, e.to);
			}
		}
	}

	return (d);
}

//verified with https://atcoder.jp/contests/abc176/tasks/abc176_d

int main() {
	int H, W; cin >> H >> W;
	int ch, cw, dh, dw; cin >> ch >> cw >> dh >> dw; --ch, --cw, --dh, --dw;
	vector<string> S(H);
	for (int i = 0; i < H; i++) cin >> S[i];

	auto to_int = [&](int y, int x) { return (W*y+x); };

	vector<vector<Edge<int>>> G(H*W);
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			if (S[y][x] == '#') continue;
			for (int i = max(0, y-2); i <= min(y+2, H-1); i++) {
				for (int j = max(0, x-2); j <= min(x+2, W-1); j++) {
					if (i == y && j == x) continue;
					if (S[i][j] == '#') continue;
					if (abs(y-i) + abs(x-j) == 1) {
						G[to_int(y, x)].emplace_back(to_int(i, j), 0);
						G[to_int(i, j)].emplace_back(to_int(y, x), 0);
					} else {
						G[to_int(y, x)].emplace_back(to_int(i, j), 1);
						G[to_int(i, j)].emplace_back(to_int(y, x), 1);
					}
				}
			}
		}
	}	
	auto d = BFS(H*W, G, to_int(ch, cw));
	int v = to_int(dh, dw);
	if (d[v] == numeric_limits<int>::max()) {
		cout << -1 << endl;
	} else {
		cout << d[v] << endl;
	}

	return (0);
}
