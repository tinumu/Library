struct Unionfind
{
	vector < int > par;

	Unionfind(int n)
	{
		par = vector < int >(n);
		for ( int i = 0; i < n; i++ ) {
			par[i] = i;
		}
	}

	void unite(int x, int y)
	{
		x = root(x), y = root(y);
		if ( x == y ) return;
		par[x] = y;
	}

	bool same(int x, int y)
	{
		return ( root(x) == root(y) );
	}

	int root(int n)
	{
		return (par[n] = ( par[n] == n ? n : root(par[n]) ));
	}
};
