#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct BIT {
	vector<T> dat;
	int size; //2べきのサイズ

	BIT (int n) {
		dat.assign(n+1, 0);
		size = 1;
		while (size <= n) size <<= 1;
	}

	void add(int k, T x) {
		for (++k; k < dat.size(); k += k & -k) dat[k] += x;
	}
	void update(int k, T x) { add(k, x - fold(k, k)); }
	void updateall(T x) {
		for (int k = 1; k < (int)dat.size(); k++) {
			dat[k] += x;
			int l = k+(k&-k);
			if (l < dat.size()) dat[l] += dat[k];
		}
	}
	void updateall(const vector<T> &val) {
		for (int k = 1; k < (int)dat.size(); k++) {
			dat[k] += val[k-1];
			int l = k+(k&-k);
			if (l < dat.size()) dat[l] += dat[k];
		}
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
		T sum = 0;
		int sz = size;
		int pos = 0;
		T all = query((int)dat.size()-2);
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
	BIT<int> bit(128);
	for (int i = 0; i < 128; i++) bit.add(i, i);
	
	int val; cin >> val;
	cout << bit.query(127) << endl;
	cout << bit.lower_bound(val) << endl;

	return (0);
}
