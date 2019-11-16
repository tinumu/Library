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
			swap(x2 -= t * x1, x1);
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


template < typename T > 
struct Matrix
{
	using V = vector < T >;
	using VV = vector < V >;
	VV mat;

	Matrix ( int n )
	{
		mat.assign(n, V(n, 0));
	}
	
	void input()
	{
		int n = mat.size();
		for ( int i = 0; i < n; i++ ) {
			for ( int j = 0; j < n; j++ ) {
				cin >> mat[i][j];
			}
		}
	}

	void output()
	{
		int n = mat.size();
		for ( int i = 0; i < n; i++ ) {
			cout << mat[i][0];
			for ( int j = 1; j < n; j++ ) {
				cout << " " << mat[i][j];
			}
			cout << endl;
		}
	}

	Matrix operator + ( const Matrix &d ) const
	{
		int n = mat.size();
		Matrix ret(n);
		if ( n == d.mat.size() ) {
			for ( int i = 0; i < n; i++ ) {
				for ( int j = 0; j < n; j++ ) {
					ret.mat[i][j] = mat[i][j] + d.mat[i][j];
				}
			}
		}
		return ( ret );
	}

	Matrix operator - ( const Matrix &d ) const
	{
		int n = mat.size();
		Matrix ret(n);
		if ( n == d.mat.size() ) {
			for ( int i = 0; i < n; i++ ) {
				for ( int j = 0; j < n; j++ ) {
					ret.mat[i][j] = mat[i][j] - d.mat[i][j];
				}
			}
		}
		return ( ret );
	}
	
	Matrix operator * ( const Matrix &d ) const
	{
		int n = mat.size();
		Matrix ret(n);
		if ( n == d.mat.size() ) {
			for ( int i = 0; i < n; i++ ) {
				for ( int j = 0; j < n; j++ ) {
					for ( int k = 0; k < n; k++ ) {
						ret.mat[i][j] += mat[i][k] * d.mat[k][j];
					}
				}
			}
		}
		return ( ret );
	}
	
	V operator * ( const V &d ) const
	{
		int n = mat.size();
		V ret(n);
		if ( n == d.size() ) {
			for ( int i = 0; i < n; i++ ) {
				for ( int k = 0; k < n; k++ ) {
					ret[i] += mat[i][k] * d[k];
				}
			}
		}
		return ( ret );
	}

	Matrix operator ^ ( int w ) const
	{
		Matrix ret = I(), pad = *this;
		
		while ( w ) {
			if ( w & 1 ) ret = ret * pad;
			pad = pad * pad;
			w >>= 1;
		}

		return ( ret );
	}

	Matrix I() const
	{
		int n = mat.size();
		Matrix ret(n);
		for ( int i = 0; i < n; i++ ) {
			ret.mat[i][i] = 1;
		}
		return ( ret );
	}
};

int main()
{
	constexpr int mod = 1000000007;

	Matrix < Modint < 5 > > a(3), b(3), ans(3);
	
	a.input();
	b.input();

	ans = a * b;

	ans.output();

	return ( 0 );
}
