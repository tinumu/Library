#include <bits/stdc++.h>
using namespace std;

template<typename T> 
struct BIT {
	vector<T> dat;
	T all;
	int midsize; //lower_boundの時の最初のアクセスポイント

	BIT (int n) : all(0) { 
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

int main() {
	BIT<int> bit(127);
	for (int i = 0; i < 127; i++) bit.add(i, i);
	
	int val; cin >> val;
	cout << bit.query(126) << endl;
	cout << bit.lower_bound(val) << endl;

	return (0);
}
