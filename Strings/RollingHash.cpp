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

