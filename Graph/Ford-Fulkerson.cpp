#include <bits/stdc++.h>
using namespace std;

//Please copy under code!

template<typename T>
struct FordFulkerson {
    struct Edge {
        int to, rev;
        T cap;
        Edge () {}
        Edge (int to, int rev, T cap) : to(to), rev(rev), cap(cap) {}
    };

    vector<vector<Edge>> G;
    vector<int> used;
    const T INF;
    int timestamp;

    FordFulkerson(int size) : INF(numeric_limits<T>::max()), timestamp(0) {
        G.resize(size);
        used.assign(size, -1);
    }

    void add_edge(int from, int to, T cap) {
        G[from].emplace_back(to, (int)G[to].size(), cap);
        G[to].emplace_back(from, (int)G[from].size() - 1, 0);
    }
    
    T dfs(int v, int t, T flow) {
        if (v == t) return (flow);
        used[v] = timestamp;
        for (auto &e : G[v]) {
            if (used[e.to] < timestamp && e.cap > 0) {
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
        T flow = 0;
        for (T f; (f = dfs(s, t, INF)) > 0; timestamp++) {
            flow += f;  
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
    FordFulkerson< int > g(V);
    for(int i = 0; i < E; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        g.add_edge(a, b, c);
    }
    printf("%d\n", g.max_flow(0, V - 1));
}
