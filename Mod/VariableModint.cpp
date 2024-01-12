#include <bits/stdc++.h>
using namespace std;

//可変modだが、整数の代入が面倒
//うまいやり方を知らない
//うまくうごくのかもよくわからない
//constexpr ではなくしたらコンパイル通ったけど
struct Modint {
	using uint = unsigned;
	using u64 = uint64_t;
	using i64 = int64_t;

	Modint (const unsigned MOD, const i64 dat = 0) : MOD(MOD), dat(dat >= 0 ? dat % MOD : (MOD - (-dat) % MOD) % MOD) {}

	const Modint operator + (const Modint &v) const { return (Modint(*this) += v); }
	const Modint operator - () const { return (Modint(MOD, -((i64)dat))); }
	const Modint operator - (const Modint &v) const { return (Modint(*this) -= v); }
	const Modint operator * (const Modint &v) const { return (Modint(*this) *= v); }

	const Modint &operator += (const Modint &v) {
		dat += v.dat;
		if (dat >= MOD) dat -= MOD;
		return (*this);
	}
	const Modint &operator -= (const Modint &v) {
		if (dat < v.dat) dat += MOD;
		dat -= v.dat;
		return (*this);
	}
	const Modint &operator *= (const Modint &v) {
		dat = dat * v.dat % MOD;
		return (*this);
	}

	const Modint operator ~ () const {
		i64 a = dat, b = MOD, x1 = 1, x2 = 0, t;

		while (b > 0) {
			t = a / b;
			swap(a -= t * b, b);
			swap(x1 -= t * x2, x2);
		}

		return (Modint(MOD, x1));
	}

	const Modint operator / (const Modint &v) const { return ((*this) * ~v); }
	const Modint &operator /= (const Modint &v) { return ((*this) = (*this) / v); }

	const Modint operator ^ (i64 n) const {
		Modint ret(MOD, 1), mul(MOD, dat);
		u64 m = n < 0 ? -n : n;
		while (m > 0) {
			if (m & 1) ret *= mul;
			mul *= mul;
			m >>= 1;
		}
		return (n < 0 ? ~ret : ret);
	}

	bool operator == (const Modint &v) const { return (dat == v.dat); }
	bool operator != (const Modint &v) const { return (dat != v.dat); }

	friend ostream& operator << (ostream &os, const Modint &p) {
		return (os << p.dat);
	}

	friend istream& operator >> (istream &is, Modint &p) {
		i64 data;
		is >> data;
		p = Modint(p.MOD, data);
		return (is);
	}

	private:
	u64 dat;
	unsigned MOD;
};


