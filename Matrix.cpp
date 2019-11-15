#include <bits/stdc++.h>
using namespace std;

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
	Matrix < int > a(3), b(3), ans(3);
	
	a.input();
	b.input();

	ans = a * b;

	ans.output();

	return ( 0 );
}
