#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from, to;
    long long cost;
    Edge () {}
    Edge (int from, int to, long long cost ) : from(from), to(to), cost(cost) {}
};

vector < long long > BellmanFord(int V, vector < Edge > &edges, int s)
{
    using ll = long long;
    constexpr ll INF = (1ll << 60) - 1;
    vector < ll > d(V, INF);
    d[s] = 0;
    for ( int i = 0; i < V; i++ ) {
        for ( auto &e : edges ) {
            if ( d[e.from] != INF && d[e.to] > d[e.from] + e.cost ) {
                d[e.to] = d[e.from] + e.cost;
                if ( i == V - 1 ) return ( vector < ll > () );
            }
        }
    }
    return ( d );
}

