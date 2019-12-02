#include <bits/stdc++.h>
using namespace std;

const int INF = (1 << 30) - 1;

template < typename T >
struct Monoid {
	T id;
	function < T(T, T) > op;
	Monoid ( T id, function < T(T, T) > op) : id(id), op(op) {}
};

template < typename T >
struct SegmentTree {
	const Monoid < T > monoid;
	vector < T > dat;
	int size;

	SegmentTree(int n, Monoid < T > monoid) : monoid(monoid) {
		size = 1;
		while ( size < n ) size *= 2;
		dat.assign(size * 2 + 10, monoid.id);
	}

	void update(int k, T x) {
		k += size - 1;
		dat[k] = x;
		while ( k > 0 ) {
			k = (k - 1) / 2;
			dat[k] = monoid.op(dat[k * 2 + 1], dat[k * 2 + 2]);
		}
	}
	
	void add(int k, T x) { update(k, monoid.op(x, dat[k + size - 1])); }
	T query(int a, int b) { return (query(a, b, 0, 0, size - 1)); }

	T query(int a, int b, int k, int l, int r) {
		T vl, vr;
		if ( r < a || b < l ) return ( monoid.id );
		if ( a <= l && r <= b ) return ( dat[k] );
		vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
		vr = query(a, b, k * 2 + 2, (l + r) / 2 + 1, r);
		return ( monoid.op(vl, vr) );
	}
};

int main()
{
	int N;
	string S;

	cin >> N;

	//RMQ
	SegmentTree < int > seg(N, Monoid < int > (INF, [](int a, int b) { return (min(a, b)); } ));
	
	for ( int i = 0; i < N; i++ ) {
		int val;
		cin >> val;
		seg.update(i, val);
	}
	
	while ( cin >> S, S != "exit" ) {
		switch ( S[0] ) {
		case 'm' : //min
			int a, b;
			cin >> a >> b;
			cout << seg.query(a, b) << endl;
			break;
		case 'u' : //update
			int k, x;
			cin >> k >> x;
			seg.update(k, x);
			break;
		}
	}
	
	return ( 0 );
}
