#include <bits/stdc++.h>
using namespace std;

//This is a Z_algorithm code=============================

vector<int> Z_algorithm(string &W) {
    int i = 1, j = 0;
    vector<int> Z(W.size());
    Z[0] = W.size();
    while (i < W.size()) {
        while (i + j < W.size() && W[i + j] == W[j]) ++j;
        Z[i] = j; 
        if (j == 0) { ++i; continue; }
        int k = 1;
        while (Z[k] + k < j) Z[i + k] = Z[k], ++k;
        i += k, j -= k;
    }
    return (Z);
}

vector<int> Z_algorithm(vector<int> &W) {
    int i = 1, j = 0;
    vector<int> Z(W.size());
    Z[0] = W.size();
    while (i < W.size()) {
        while (i + j < W.size() && W[i + j] == W[j]) ++j;
        Z[i] = j; 
        if (j == 0) { ++i; continue; }
        int k = 1;
        while (Z[k] + k < j) Z[i + k] = Z[k], ++k;
        i += k, j -= k;
    }
    return (Z);
}
//=======================================================

//verified https://atcoder.jp/contests/arc060/tasks/arc060_d

vector < bool > isgood(string &W) {
    vector < int > Z;
    vector < bool > ret(W.size() + 1, true);
    Z = Z_algorithm(W);
    
    for (int p = 1; p < W.size(); p++) {
        if (!ret[p]) continue;
        for (int k = 2; (k - 1) * p <= Z[p]; k++) {
            ret[k * p] = false;
        }
    }
    return (ret); 
}

int main() {
    string W, RW;
    cin >> W;

    RW = W;
    reverse(begin(RW), end(RW));
    
    vector < bool > ans1, ans2;

    ans1 = isgood(W); //prefix
    ans2 = isgood(RW);
    reverse(begin(ans2), end(ans2)); //suffix
    
    int ans = 0;
    for (int i = 0; i <= W.size(); i++) {
        ans += (ans1[i] && ans2[i]);
    }
    if (ans == 0) cout << W.size() << endl << 1 << endl;
    else if (ans1[W.size()]) cout << 1 << endl << 1 << endl;
    else cout << 2 << endl << ans << endl;
    
    return (0);
}
