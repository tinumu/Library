#include <bits/stdc++.h>
using namespace std;

//Verified with https://hoj.hamako-ths.ed.jp/onlinejudge/problems/685
//Verified with https://atcoder.jp/contests/abc060/tasks/arc073_b

//正当性はおそらくある。制限なしデータだとおそらく N <= 44 くらいまでなら耐えてくれる。
//コーナーケースのないランダムデータなら N <= 50 とかでも行けると思う。もっといけるか。
//また、最終的な使われる価値のリストや、重みのリストが少ない際にも使える。O(N min(V,W)) くらい?
//V, W ... それぞれ総和の取りうる値の数

//=====================================================================================
template<typename T> 
inline vector<pair<T, T>> merge(vector<pair<T, T>> &a, vector<pair<T, T>> &b, T W) {
        vector<pair<T, T>> ans;
        int i = 0, j = 0;
        T vmax = -1, wmax = -1;
        while (i < a.size() || j < b.size()) {
                if (i == a.size() || j != b.size() && a[i] >= b[j]) {
                        if (b[j].second > vmax && b[j].first <= W) {
                                vmax = b[j].second;
                                b[j].second = vmax;
                                if (wmax == b[j].first) ans.pop_back();
                                ans.push_back(b[j]);
                                wmax = max(wmax, b[j].first);
                        }
                        j++;
                } else {
                        if (a[i].second > vmax && a[i].first <= W) {
                                vmax = a[i].second;
                                a[i].second = vmax;
                                if (wmax == a[i].first) ans.pop_back();
                                ans.push_back(a[i]);
                                wmax = max(wmax, a[i].first);
                        }
                        i++;
                }
        }
        return (ans);
}

template<typename T>
long long knapsack(int N, T W, vector<pair<T, T>> &A) {
	int n = N-N/2, m = N/2;
	vector<pair<long long, long long>> x(n), y(m);
	for (int i = 0; i < n; i++) {
		x[i] = A[i];
	}
	sort(begin(x), end(x));
	for (int i = 0; i < m; i++) {
		y[i] = A[i+n];
	}
	sort(begin(y), end(y));

	vector<pair<long long, long long>> X, Y;
	X.emplace_back(0, 0);
	for (int i = 0; i < n; i++) {
		int size = X.size();
		vector<pair<long long, long long>> dat;
		for (int j = 0; j < size; j++) {
			if (X[j].first+x[i].first <= W) {
				dat.emplace_back(X[j].first+x[i].first, X[j].second+x[i].second);
			}
		}
		X = merge(X, dat, W);
	}

	Y.emplace_back(0, 0);
	for (int i = 0; i < m; i++) {
		int size = Y.size();
		vector<pair<long long, long long>> dat;
		for (int j = 0; j < size; j++) {
			if (Y[j].first+y[i].first <= W) {
				dat.emplace_back(Y[j].first+y[i].first, Y[j].second+y[i].second);
			}
		}
		Y = merge(Y, dat, W);
	}

	reverse(begin(Y), end(Y));        
	int j = 0;
	long long maxv = 0;
	for (int i = 0; i < X.size(); i++) {
		while (X[i].first + Y[j].first > W) j++;
		maxv = max(maxv, X[i].second + Y[j].second);
	}
	return (maxv);
}

//========================================================================================

int main() {
	using ll = long long;
	ll N, W; cin >> N >> W;
	vector<pair<ll, ll>> A(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i].second >> A[i].first;
	}
	cout << knapsack(N, W, A) << endl;
	return (0);
}
