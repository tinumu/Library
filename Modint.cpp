#include <bits/stdc++.h>
using namespace std;

template < unsigned mod >
class Modint
{
public:
	using uint = unsigned;
	using u64 = uint64_t;
	using i64 = int64_t;

	Modint (const i64 dat = 0) : dat(dat >= 0 ? dat % mod : (mod - (-dat) % mod) % mod) {}

	constexpr Modint operator + (const Modint &v) const { return ( Modint(dat + v.dat) ); }
	constexpr Modint operator - () const { return ( Modint(-((i64)dat)) ); }
	constexpr Modint operator - (const Modint &v) const { return ( (*this) + -v ); }
	constexpr Modint operator * (const Modint &v) const { return ( Modint((u64)dat * v.dat) ); }
	
	constexpr Modint operator ~ () const
	{
		i64 a = dat, b = mod, x1 = 1, x2 = 0, t;
		
		while ( b > 0 ) {
			t = a / b;
			swap(a -= t * b, b);
			swap(x1 -= t * x2, x2);
		}
		
		return ( Modint(x1) );
	}
	
	constexpr Modint operator / (const Modint &v) const { return ( (*this) * ~v ); }

	Modint &operator = (const i64 &v) { return ( (*this) = Modint < mod > (v) ); }
	Modint &operator += (const Modint &v) { return ( (*this) = (*this) + v ); }
	Modint &operator -= (const Modint &v) { return ( (*this) = (*this) - v ); }
	Modint &operator *= (const Modint &v) { return ( (*this) = (*this) * v ); }
	Modint &operator /= (const Modint &v) { return ( (*this) = (*this) / v ); }

	constexpr Modint operator ^ (u64 n) const
	{
		Modint < mod > ret(1), mul(dat);
		while ( n > 0 ) {
			if ( n & 1 ) ret *= mul;
			mul *= mul;
			n >>= 1;
		}
		return ( ret );
	}
	
	bool operator == (const Modint &v) { return ( dat == v.dat ); }
	bool operator != (const Modint &v) { return ( dat != v.dat ); }

	friend ostream& operator << (ostream &os, const Modint &p )
	{
		return ( os << p.dat );
	}
	
	friend istream& operator >> (istream &is, Modint &p )
	{
		i64 data;
		is >> data;
		p = Modint < mod >(data);
		return ( is );
	}

private:
	uint dat;
};

int main()
{
	Modint < 5 > a, b, c;
	
	cin >> a >> b >> c;

	cout << a + b + c << endl;
	cout << a * b * c << endl;
	
	cout << ~a << endl;
	
	return ( 0 );
}