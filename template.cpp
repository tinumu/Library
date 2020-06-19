#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Pi = pair<int, int>;
using Pl = pair<ll, ll>;
using vint = vector<int>;
using vvint = vector<vint>;
using vvvint = vector<vvint>;
using vdouble = vector<double>;
using vvdouble = vector<vdouble>;
using vvvdouble = vector<vvdouble>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vvvll = vector<vvll>;
using uint = unsigned int;
using ull = unsigned long long;

template<typename T> using uset = unordered_set<T>;
template<typename T1, typename T2> using umap = unordered_map<T1, T2>;

constexpr int INF = (1 << 30) - 1;
constexpr ll LLINF = 1LL << 60;
constexpr int dy[] = {1, 0, -1, 0, 1, -1, -1, 1};
constexpr int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
constexpr char el = '\n';
constexpr int mod = 1000000007;
constexpr int mod2 = 998244353;
template<typename T> T gcd(T a, T b) { return (b ? gcd(b, a % b) : a); }
template<typename T> T lcm(T a, T b) { return (a / gcd(a, b) * b); }
template<typename T1, typename T2>
inline bool chmin(T1 &a, T2 b) { return (a > b && (a = b, true)); }
template<typename T1, typename T2>
inline bool chmax(T1 &a, T2 b) { return (a < b && (a = b, true)); }

template<typename T = ll>
vector<T> makeVector(size_t a, T b) { return (vector<T>(a, b)); }
template<typename... Ts>
auto makeVector(size_t a, Ts... ts) { 
	return (vector<decltype(makeVector(ts...))>(a, makeVector(ts...)));
}

template<typename T>
bool isin(T y, T x, T h, T w) { return (0 <= y && 0 <= x && y < h && x < w); }
template<typename T>
bool isin1(T y, T x, T h, T w) { return (0 < y && 0 < x && y <= h && x <= w); }

template<typename T>
ostream& operator <<(ostream &os, vector<T> &v) {
	os << v[0];
	for (int i = 1; i < v.size(); i++) os << " " << v[i];
	return (os);
}

template<typename T>
istream& operator >>(istream &is, vector<T> &v) {
	for (auto &u : v) is >> u;
	return (is);
}

template<typename T1, typename T2>
istream& operator >>(istream &is, pair<T1, T2> &p) {
	return (is >> p.first >> p.second);
}


void Main() {

}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	cout << fixed << setprecision(20);
	Main();
	return (0);
}
