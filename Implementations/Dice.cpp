#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Die {
	T s[6];
	T &left() { return (s[0]); }
	T &right() { return (s[1]); }
	T &front() { return (s[2]); }
	T &back() { return (s[3]); }
	T &bottom() { return (s[4]); }
	T &top() { return (s[5]); }

	Die(T l, T r, T f, T b, T d, T u) {
		tie(s[0], s[1], s[2], s[3], s[4], s[5]) = tie(l, r, f, b, d, u);
	}
	
	void roll(char c) {
		string S = "ENWS";
		int indexes[4][4] = {
			{1, 5, 0, 4},
			{3, 5, 2, 4},
			{0, 5, 1, 4},
			{2, 5, 3, 4}
		};
		for (int i = 0; i < 4; i++) {
			if (c != S[i]) continue;
			T temp = s[indexes[i][0]];
			s[indexes[i][0]] = s[indexes[i][1]];
			s[indexes[i][1]] = s[indexes[i][2]];
			s[indexes[i][2]] = s[indexes[i][3]];
			s[indexes[i][3]] = temp;
		}
	}
};

int main() {
	int u, f, r, l, b, d;
	string S;
	cin >> u >> f >> r >> l >> b >> d;
	Die<int> dice(l, r, f, b, d, u);

	cin >> S;
	for (int i = 0; i < S.size(); i++) {
		dice.roll(S[i]);
	}
	cout << dice.top() << endl;
	return (0);
}

