#include <bits/stdc++.h>
using namespace std;

template < uint_fast64_t MOD = 1000000007, uint_fast64_t base = 9973 >
class RollingHash {
public:
	using u64 = uint_fast64_t;
	using i32 = int_fast32_t;
	RollingHash() {}

	RollingHash(const string &s) {
		i32 n = s.size();
		hash.assign(n + 1, 0);
		power.assign(n + 1, 1);
		for ( i32 i = 0; i < n; i++ ) {
			hash[i + 1] = (hash[i] * base + s[i]) % MOD;
			power[i + 1] = power[i] * base % MOD;
		}
	}

	u64 get(i32 l, i32 n) {
		u64 value = hash[l + n] + MOD - hash[l] * power[n] % MOD;
		return ( value - (value >= MOD ? MOD : 0) );
	}

private:
	vector < u64 > hash, power;
};

template < uint_fast64_t MOD = 1000000007, uint_fast64_t base1 = 2009, uint_fast64_t base2 = 9973 >
class RollingHash2D {
public:
	using u64 = uint_fast64_t;
	using i32 = int_fast32_t;

	RollingHash2D () {}
	
	RollingHash2D(const vector < string > &D, i32 R, i32 C) : row(R), col(C) {
		i32 H = D.size(), W = D[0].size();
		vector < RollingHash < MOD, base2 > > data;

		hash.assign(H - R + 1, vector < u64 >(W - C + 1, 0));
		for ( const string &s : D ) data.emplace_back(s);

		for ( i32 j = 0; j < W - C + 1; j++ ) {
			vector < u64 > hh(H + 1, 0);
			vector < u64 > power(H + 1, 1);
			for ( i32 i = 0; i < H; i++ ) {
				hh[i + 1] = (hh[i] * base1 + data[i].get(j, C)) % MOD;
				power[i + 1] = power[i] * base1 % MOD;
			}
			for ( i32 i = 0; i < H - R + 1; i++ ) {
				hash[i][j] = hh[i + R] + MOD - hh[i] * power[R] % MOD;
				if ( hash[i][j] >= MOD ) hash[i][j] -= MOD;
			}
		}
	}
	u64 get(i32 y, i32 x) { return ( hash[y][x] ); }
	
private:
	vector < vector < u64 > > hash;
	i32 row, col;
};


int main()
{
	constexpr int mod = 1000000007, base1 = 2009, base2 = 9973;
	int H, W, R, C;
			
	cin >> H >> W;
	vector < string > S(H);
	for ( string &s : S ) cin >> s;
	cin >> R >> C;
	vector < string > T(R);
	for ( string &t : T ) cin >> t;
	
	RollingHash2D < mod, base1, base2 > r1(S, R, C);
	RollingHash2D < mod, base1, base2 > r2(T, R, C);
	
	uint_fast64_t b = r2.get(0, 0);
	for ( int i = 0; i < H - R + 1; i++ ) {
		for ( int j = 0; j < W - C + 1; j++ ) {
			if ( r1.get(i, j) == b ) cout << i << " " << j << endl;
		}
	}
	return ( 0 );
}
