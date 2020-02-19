#include <bits/stdc++.h>
using namespace std;

template<typename T>
T largestSquare(vector<vector<T>> &dp) {
	T maxv = 0;
	int H = dp.size();
	int W = dp[0].size();
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i && j && dp[i][j]) {
				dp[i][j] = min({dp[i-1][j-1], dp[i][j-1], dp[i-1][j]}) + 1;
			}
			maxv = max(maxv, dp[i][j]);
		}
	}
	return (maxv);	
}

//verified with https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/3/DPL_3_A

int main() {
	int H, W; cin >> H >> W;
	vector<vector<int>> dp(H, vector<int>(W, 0));
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> dp[i][j];
			dp[i][j] = 1 - dp[i][j];
		}
	}
	int d = largestSquare(dp);

	cout << d*d << endl;
	return (0);
}
