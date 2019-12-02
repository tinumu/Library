#include <bits/stdc++.h>
using namespace std;

template < typename T > 
struct BIT {
	vector < T > dat;

	BIT (int n) { dat.assign(n + 1, 0); }
	
	void add(int k, T x) {
		k++;
		while ( k <= dat.size() ) dat[k] += x, k += k & -k;
	}

	T query(int k) {
		T sum = 0;
		k++;
		while ( k > 0 ) sum += dat[k], k -= k & -k;
		return ( sum );
	}

	int lower_bound(T x) {
		int l, r;
		l = -1, r = dat.size();
		while ( l + 1 < r ) {
			int m = (l + r) / 2;
			if ( query(m) >= x ) r = m;
			else l = m;
		}
		return ( r );
	}
};

int main()
{
	BIT < int > bit(100);

	return ( 0 );
}
