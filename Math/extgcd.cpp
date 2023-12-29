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

//ansx は動くことは確かめられた
//x が非負整数で一番小さい値になるように調整してある
template<typename T>
tuple<T, T, bool> extgcd(T a, T b, T c) {
	T x, y;
	T g = gcd(a, b);
	if ((g + c%g)%g != 0) return (tuple<T, T, bool>(0, 0, false));
	extgcd(a, b, x, y);
	T ansx = x*c/g, ansy = y*c/g;
	auto bdiv = [](T v, T m) { return (v < 0 ? (v-m+1)/m : v/m); };
	T t = bdiv(ansx, b/g);
	ansx -= t*(b/g);
	ansy -= t*(a/g);
	return (tuple<T, T, bool>(ansx, ansy, true));
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
