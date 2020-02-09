#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int MAX = 3010000;
constexpr int MOD = 1000000007;

//Please set MAX and MOD!!========================================

ll fac[MAX], finv[MAX], inv[MAX];

void COMinit() {
	fac[0] = fac[1] = 1;
	finv[0] = finv[1] = 1;
	inv[1] = 1;
	for (int i = 2; i < MAX; i++) {
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
		finv[i] = finv[i - 1] * inv[i] % MOD;
	}
}

ll COM(int n, int k) {
	if (n < k || n < 0 || k < 0) return (0);
	return (fac[n] * (finv[k] * finv[n - k] % MOD) % MOD);
}
//end=============================================================
//verified https://atcoder.jp/contests/abc145/tasks/abc145_d

int main()
{
	COMinit(); 

	int X, Y;
 
	cin >> X >> Y;

	if ((X + Y) % 3 != 0 || (X + Y) / 3 > X || (X + Y) / 3 > Y) {
		cout << 0 << endl;
	} else {
		int n = (X + Y) / 3;
		int k = (X - n);
 
		cout << COM(n, k) << endl;
	}
 
	return (0);
}
