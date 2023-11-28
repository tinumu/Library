#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<unsigned MOD>
struct Modint {
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

	constexpr Modint operator ^ (i64 n) const {
		Modint<MOD> ret(1), mul(dat);
		u64 m = n < 0 ? -n : n;
		while (m > 0) {
			if (m & 1) ret *= mul;
			mul *= mul;
			m >>= 1;
		}
		return (n < 0 ? ~ret : ret);
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

int main() {
	using Mint = Modint<998244353>;
	Mint a = Mint(2)^(-10);

	Mint b = a * (Mint(2)^(10));

	cout << a << " " << b << endl;
}
