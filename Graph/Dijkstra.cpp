#include <bits/stdc++.h>
using namespace std;

using Pi = pair<int, int>;

template < typename T >
struct Edge {
    int from, to;
    T cost;
    Edge () {}
    Edge (int from, int to, T cost) : from(from), to(to), cost(cost) {}
    Edge (int to, T cost) : from(-1), to(to), cost(cost) {}
};

template < typename T >
vector<T> Dijkstra(int V, const vector<vector<Edge<T>>> &G, int s) {
    using Node = pair<T, int>;
    constexpr T INF = numeric_limits<T>::max();
    vector<T> d(V, INF);
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    d[s] = 0;
    pq.emplace(0, s);
    while (!pq.empty()) {
        Node node = pq.top(); pq.pop();
        if (d[node.second] < node.first) continue;
        for (auto &e : G[node.second]) {
            T cost = e.cost + node.first;
            if (cost < d[e.to]) {
                d[e.to] = cost;
                pq.emplace(cost, e.to);
            }
        }
    }

    return (d);
}

//verified https://atcoder.jp/contests/arc061/tasks/arc061_c
int main() {
    int N, M;
    map<Pi, int> ha;
    int cnt = 0;
    vector<vector<Edge<int>>> G(500005);
    vector<vector<int>> stp(100005);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int p, q, c;
        int u, v;
        cin >> p >> q >> c; --p, --q;
        if (ha.find(Pi(p, c)) == ha.end()) ha[Pi(p, c)] = cnt++;
        if (ha.find(Pi(q, c)) == ha.end()) ha[Pi(q, c)] = cnt++;
        u = ha[Pi(p, c)], v = ha[Pi(q, c)]; 
        G[u].emplace_back(v, 0);
        G[v].emplace_back(u, 0);
        stp[p].push_back(c);
        stp[q].push_back(c);
    }

    for (int i = 0; i < N; i++) {
        ha[Pi(i, -1)] = cnt++;
        int home = cnt - 1;
        for (auto &c : stp[i]) {
            int u = ha[Pi(i, c)];
            G[u].emplace_back(home, 0);
            G[home].emplace_back(u, 1);
        }
    }

    vector<int> ans = Dijkstra<int>(cnt, G, ha[Pi(0, -1)]);
    int ansv = ans[ha[Pi(N - 1, -1)]];
    if (ansv == numeric_limits<int>::max()) {
        cout << -1 << endl;
    } else {
        cout << ansv << endl;
    }
    return (0);
}
