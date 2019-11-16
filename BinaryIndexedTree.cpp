#include <bits/stdc++.h>
using namespace std;

template < typename T > 
struct BIT
{
	vector < T > dat;

	BIT (int n)
	{
		dat.assign(n + 1, 0);
	}
	
	void add(int k, T x)
	{
		k++;
		while ( k <= dat.size() ) {
			dat[k] += x;
			k += k & -k;
		}
	}

	T query(int k)
	{
		T sum = 0;
		k++;
		while ( k > 0 ) {
			sum += dat[k];
			k -= k & -k;
		}
		return ( sum );
	}
};

int main()
{
	BIT < int > bit(100);

	return ( 0 );
}
