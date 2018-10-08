#include <bits/stdc++.h>
using namespace std;

struct MMatrix
{
	using V = vector < int >;
	using VV = vector < V >;
	VV mat;
	int mod;

	MMatrix ( int n, int mod ) : mod(mod)
	{
		mat.assign(n, V(n, 0));
	}

	MMatrix operator + ( const MMatrix &d ) const
	{
		int n = mat.size();
		MMatrix ret(n, mod);
		if ( n == d.mat.size() ) {
			for ( int i = 0; i < n; i++ ) {
				for ( int j = 0; j < n; j++ ) {
					ret.mat[i][j] = ((int64_t)mat[i][j] + d.mat[i][j]) % mod;
				}
			}
		}
		return ( ret );
	}

	MMatrix operator - ( const MMatrix &d ) const
	{
		int n = mat.size();
		MMatrix ret(n, mod);
		if ( n == d.mat.size() ) {
			for ( int i = 0; i < n; i++ ) {
				for ( int j = 0; j < n; j++ ) {
					ret.mat[i][j] = ((int64_t)mat[i][j] - d.mat[i][j] + mod) % mod;
				}
			}
		}
		return ( ret );
	}
	
	MMatrix operator * ( const MMatrix &d ) const
	{
		int n = mat.size();
		MMatrix ret(n, mod);
		if ( n == d.mat.size() ) {
			for ( int i = 0; i < n; i++ ) {
				for ( int j = 0; j < n; j++ ) {
					for ( int k = 0; k < n; k++ ) {
						ret.mat[i][j] = ((int64_t)ret.mat[i][j] + (int64_t)mat[i][k] * d.mat[k][j]) % mod;
					}
				}
			}
		}
		return ( ret );
	}

	MMatrix operator ^ ( int w ) const
	{
		MMatrix ret = I(), pad = *this;
		
		while ( w ) {
			if ( w & 1 ) ret = ret * pad;
			pad = pad * pad;
			w >>= 1;
		}

		return ( ret );
	}

	MMatrix I() const
	{
		int n = mat.size();
		MMatrix ret(n, mod);
		for ( int i = 0; i < n; i++ ) {
			ret.mat[i][i] = 1;
		}
		return ( ret );
	}
};


