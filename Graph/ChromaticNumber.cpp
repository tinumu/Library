#include <bits/stdc++.h>
using namespace std;

struct ChromaticNumber {
	const int m = 998244353;
	using ll = long long;

	vector<ll> F, I;
	int size;
	int chromatic_number;
	vector<int> G;

	ChromaticNumber(vector<int> &G) : size(G.size()), G(G) {
		init();
		chromatic_number = calcChromaticNumber();
	};

	void init() {
		F.resize(1<<size);
		I.resize(1<<size);
		for (int S = 0; S < (1<<size); S++) {
			F[S] = (size - __builtin_popcount(S)) % 2 == 0 ? 1 : (m-1);
		}
	}

	int calcChromaticNumber() {
		I[0] = 1;
		for (int S = 1; S < (1<<size); S++) {
			int ctz = __builtin_ctz(S);
			I[S] = (I[S^(1<<ctz)] + I[(S^(1<<ctz))&(~G[ctz])]) % m;
		}

		for (int k = 1; k < size; k++) {
			ll G_k = 0;
			for (int S = 0; S < (1<<size); S++) {
				(F[S] *= I[S]) %= m;
				(G_k += F[S]) %= m;
			}
			if (G_k != 0) {
				return (k);
			}
		}
		return (size);
	}

	int get() {
		return (chromatic_number);
	}
};

//verified https://judge.yosupo.jp/problem/chromatic_number

int main() {
	int N, M; cin >> N >> M;
	vector<int> G(N);
	for (int i = 0; i < M; i++) {
		int u, v; cin >> u >> v;
		G[u] |= (1<<v);
		G[v] |= (1<<u);
	}
	ChromaticNumber cnumber(G);
	cout << cnumber.get() << endl;
	return (0);
}
