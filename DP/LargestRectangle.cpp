#include <bits/stdc++.h>
using namespace std;

//Please copy under here========================================================

template<typename T>
T largestRectangle(vector<T> &v) {
	stack<pair<T, int>> st;
	T maxv = 0;
	v.push_back(0);
	for (int i = 0; i < v.size(); i++) {
		int minv = i;
		while (!st.empty() && st.top().first > v[i]) {
			auto dat = st.top(); st.pop();
			maxv = max(maxv, dat.first * (i - dat.second));
			minv = min(minv, dat.second);
		}
		st.emplace(v[i], minv);
	}
	v.pop_back();
	return (maxv);
}

//verified with http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_3_C

int main() {
	int N; cin >> N;
	vector<long long> H(N);
	for (auto &v : H) cin >> v;
	cout << largestRectangle(H) << endl;
	return (0);
}

