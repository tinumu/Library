#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct BIT {
	vector<T> dat;
	int midsize; //lower_boundの時の最初のアクセスポイント

	BIT (int n) {
		dat.assign(n+1, 0);
		midsize = 1;
		while (midsize <= n) midsize <<= 1;
		midsize >>= 1;
	}

	void add(int k, T x) {
		for (++k; k < dat.size(); k += k & -k) dat[k] += x;
		all += x;
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

	// O(log N) に修正, 実装汚いけど
	int lower_bound(T x) {
		T sum = 0;
		int sz = midsize;
		int pos = 0;
		T all = query((int)dat.size() - 1);
		while (sz && pos+1 < dat.size()) {
			T val;
			int next;
			if ((pos|sz) >= dat.size()) val = all, next = (int)dat.size()-1;
			else val = sum + dat[pos|sz], next = pos|sz;

			if (val < x) {
				sum = val;
				pos = next;
			}
			sz >>= 1;
		}
		return (pos);
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
	vector<int> data = {3, 2, 1, 0};
	cout << invNum(data) << endl;
}
