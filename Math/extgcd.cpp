#include <bits/stdc++.h>
using namespace std;

//https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E
//この問題で確かめたが、|x| + |y| が最小値になっているかどうかはよくわからない
template<typename T>
T extgcd(T a, T b, T &x, T &y) {
	if (b == 0) {
		x = 1, y = 0;
		return (a);
	}
	T d = extgcd(b, a%b, y, x);
	y -= a/b * x;
	return (d);
}

//modInv はまだ確かめてない
template<typename T>
T modInv(T dat, T mod) {
	T x, y;
	extgcd(dat, mod, x, y);
	return (x);
}

using ll = long long;
int main() {
	ll a, b; cin >> a >> b;
	ll x, y;
	ll div = extgcd(a, b, x, y);
	a /= div, b /= div;
	cout << x << " " << y << endl;
	return (0);
}
