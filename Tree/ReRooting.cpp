#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9+7;
template<unsigned MOD>
class Modint {
	public:
		using uint = unsigned;
		using u64 = uint64_t;
		using i64 = int64_t;

		Modint (const i64 dat = 0) : dat(dat >= 0 ? dat % MOD : (MOD - (-dat) % MOD) % MOD) {}

		constexpr Modint operator + (const Modint &v) const { return (Modint(*this) += v); }
		constexpr Modint operator - () const { return (Modint(-((i64)dat))); }
		constexpr Modint operator - (const Modint &v) const { return (Modint(*this) -= v); }
		constexpr Modint operator * (const Modint &v) const { return (Modint(*this) *= v); }

		constexpr Modint &operator = (const i64 &v) { return ((*this) = Modint<MOD>(v)); }
		constexpr Modint &operator += (const Modint &v) {
			dat += v.dat;
			if (dat >= MOD) dat -= MOD;
			return (*this);
		}
		constexpr Modint &operator -= (const Modint &v) {
			if (dat < v.dat) dat += MOD;
			dat -= v.dat;
			return (*this);
		}
		constexpr Modint &operator *= (const Modint &v) {
			dat = dat * v.dat % MOD;
			return (*this);
		}

		constexpr Modint operator ~ () const {
			i64 a = dat, b = MOD, x1 = 1, x2 = 0, t;

			while (b > 0) {
				t = a / b;
				swap(a -= t * b, b);
				swap(x1 -= t * x2, x2);
			}

			return (Modint(x1));
		}

		constexpr Modint operator / (const Modint &v) const { return ((*this) * ~v); }
		constexpr Modint &operator /= (const Modint &v) { return ((*this) = (*this) / v); }

		constexpr Modint operator ^ (u64 n) const {
			Modint<MOD> ret(1), mul(dat);
			while (n > 0) {
				if (n & 1) ret *= mul;
				mul *= mul;
				n >>= 1;
			}
			return (ret);
		}

		bool operator == (const Modint &v) { return (dat == v.dat); }
		bool operator != (const Modint &v) { return (dat != v.dat); }

		friend ostream& operator << (ostream &os, const Modint &p) {
			return (os << p.dat);
		}

		friend istream& operator >> (istream &is, Modint &p) {
			i64 data;
			is >> data;
			p = Modint<MOD>(data);
			return (is);
		}

	private:
		u64 dat;
};

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


int main() {
	struct Node_t {
		Modint<mod> pat;
		int size;
		Node_t () {}
		Node_t (Modint<mod> pat, int size) : pat(pat), size(size) {}
	};
	int N; cin >> N;
	
	vector<Modint<mod>> fact(N+1, 1);
	for (int i = 2; i <= N; i++) fact[i] *= fact[i-1] * i;

	auto f1 = [&](Node_t a, Node_t b) {
		a.pat /= fact[a.size] * fact[b.size];
		a.size += b.size;
		a.pat *= fact[a.size] * b.pat;
		return (a);
	};
	auto f2 = [&](Node_t a, int d) {
		return (Node_t(a.pat, a.size+d));
	};

	ReRooting<Node_t, int> re(N, f1, f2, Node_t(1, 0));
	for (int i = 0; i < N-1; i++) {
		int a, b;
		cin >> a >> b; --a, --b;
		re.add_edge(a, b, 1);
	}
	vector<Node_t> d = re.build();	

	for (auto &v : d) cout << v.pat << '\n';
	return (0);
}
