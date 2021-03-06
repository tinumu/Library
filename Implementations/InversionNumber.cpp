#include <bits/stdc++.h>
using namespace std;

template<typename T> 
struct BIT {
	vector<T> dat;

	BIT (int n) { dat.assign(n+1, 0); }

	void add(int k, T x) {
		for (++k; k < dat.size(); k += k & -k) dat[k] += x;
	}

	T query(int k) {
		T sum = 0;
		for (++k; k > 0; k -= k & -k) sum += dat[k];
		return (sum);
	}

	//[l, r]
	T fold(int l, int r) {
		return (query(r) - (l > 0 ? query(l-1) : 0));
	}

	int lower_bound(T x) {
		int l, r;
		l = -1, r = dat.size();
		while (l + 1 < r) {
			int m = (l + r) / 2;
			if (query(m) >= x) r = m;
			else l = m;
		}
		return (r);
	}
};

//0-indexed
long long invNum(vector<int> &perm) {
	long long ans = 0;
	int n = perm.size();
	BIT<int> tree(n);
	for (int j = 0; j < n; j++) {
		ans += j-tree.query(perm[j]);
		tree.add(perm[j], 1);
	}
	return (ans);
}







//たしかめ

int main() {
	vector<int> data = {2, 0, 1, 3};
	cout << invNum(data) << endl;
}
