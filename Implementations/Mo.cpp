#include <bits/stdc++.h>
using namespace std;

//答えの管理は main の方で各自やるように。
//クエリの中身 {l, r, i} [l, r) の半開区間, インデックス i
//add, del, sub は auto で定義しないと速くない
template<typename Add, typename Del, typename Sub>
void Mo(int range, vector<tuple<int, int, int>> &queries, const Add &add, const Del &del, const Sub &sub) {
	int Q = queries.size();
	int division = ceil(range/sqrt(Q));
	sort(begin(queries), end(queries), [&](const tuple<int, int, int> &a, const tuple<int, int, int> &b) {
		return (pair<int, int>(get<0>(a)/division, get<1>(a)) < pair<int, int>(get<0>(b)/division, get<1>(b)));
	});

	int nowl = 0, nowr = 0;
	for (const auto &[l, r, i] : queries) {
		while (nowr < r) add(nowr++);
		while (nowr > r) del(--nowr);
		while (nowl < l) del(nowl++);
		while (nowl > l) add(--nowl);
		sub(i);
	}
}

//verified https://atcoder.jp/contests/abc174/tasks/abc174_f Range Set Query
int main() {
	using vint = vector<int>;
	using T3 = tuple<int, int, int>;
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int N, Q; cin >> N >> Q;
	vint C(N);
	for (auto &c : C) cin >> c;
	vint cnt(N+1);
	vector<T3> queries(Q);
	for (int i = 0; i < Q; i++) {
		int l, r; cin >> l >> r; --l;
		queries[i] = T3(l, r, i);
	}

	int now = 0;
	vint ans(Q);
	auto add = [&](int p) -> void {
		cnt[C[p]]++;
		if (cnt[C[p]] == 1) now++;
	};
	auto del = [&](int p) -> void {
		cnt[C[p]]--;
		if (cnt[C[p]] == 0) now--;
	};
	auto sub = [&](int i) -> void {
		ans[i] = now;
	};

	Mo(N, queries, add, del, sub);
	for (int i = 0; i < Q; i++) {
		cout << ans[i] << '\n';
	}
}
