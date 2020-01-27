#include <bits/stdc++.h>
using namespace std;

constexpr char el = '\n';

template<typename T> 
struct Matrix {
	using V = vector<T>;
	using VV = vector<V>;
	VV mat;
     
	Matrix (int n) {
		mat.assign(n, V(n, 0));
	}
	
	friend istream& operator >>(istream& is, Matrix &d) {
		int n = d.mat.size();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				is >> d.mat[i][j];
			}
		}
        return (is);
	}

	friend ostream& operator <<(ostream& os, Matrix &d) {
		int n = d.mat.size();
		for (int i = 0; i < n; i++) {
			os << d.mat[i][0];
			for (int j = 1; j < n; j++) {
				os << " " << d.mat[i][j];
			}
			os << el;
		}
        return (os);
	}

	Matrix operator + ( const Matrix &d ) const {
		int n = mat.size();
		Matrix ret(n);
		if (n == d.mat.size()) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					ret.mat[i][j] = mat[i][j] + d.mat[i][j];
				}
			}
		}
		return (ret);
	}

	Matrix operator - (const Matrix &d) const {
		int n = mat.size();
		Matrix ret(n);
		if (n == d.mat.size()) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					ret.mat[i][j] = mat[i][j] - d.mat[i][j];
				}
			}
		}
		return (ret);
	}
	
	Matrix operator * (const Matrix &d) const {
		int n = mat.size();
		Matrix ret(n);
		if (n == d.mat.size()) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					for (int k = 0; k < n; k++) {
						ret.mat[i][j] += mat[i][k] * d.mat[k][j];
					}
				}
			}
		}
		return (ret);
	}
	
	V operator * (const V &d) const {
		int n = mat.size();
		V ret(n);
		if (n == d.size()) {
			for (int i = 0; i < n; i++) {
				for (int k = 0; k < n; k++) {
					ret[i] += mat[i][k] * d[k];
				}
			}
		}
		return (ret);
	}

	Matrix operator ^ ( int w ) const {
		Matrix ret = I(), pad = *this;
		
		while (w) {
			if (w & 1) ret = ret * pad;
			pad = pad * pad;
			w >>= 1;
		}

		return (ret);
	}

	Matrix I() const {
		int n = mat.size();
		Matrix ret(n);
		for (int i = 0; i < n; i++) {
			ret.mat[i][i] = 1;
		}
		return (ret);
	}
};

int main() {
	Matrix<int> a(3), b(3), ans(3);
    cin >> a;

	ans = a^4;

    cout << ans;

	return (0);
}
