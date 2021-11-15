// Solves Codeforces Round #221 (Div. 1) Task E: Red and Black Tree

#include <bits/stdc++.h>

using namespace std;

typedef double T;
typedef vector<int> vi;
typedef vector<T> vd;
typedef vector<vd> vvd;

#define Debug(X)

const T eps = 1e-8, inf = 1 / .0;
#define MP make_pair
#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j
#define rep(i, a, b) for(int i = a; i < (b); ++i)

struct LPSolver {
	int m, n;
	vi N, B;
	vvd D;

	LPSolver(const vvd& A, const vd& b, const vd& c) :
		m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vd(n + 2)) {
		rep(i, 0, m) rep(j, 0, n) D[i][j] = A[i][j];
		rep(i, 0, m) {
			B[i] = n + i;
			D[i][n] = -1;
			D[i][n + 1] = b[i];
		}
		rep(j, 0, n) {
			N[j] = j;
			D[m][j] = -c[j];
		}
		N[n] = -1;
		D[m + 1][n] = 1;
	}

	void pivot(int r, int s) {
		T *a = D[r].data(), inv = 1 / a[s];
		rep(i, 0, m + 2) if(i != r && abs(D[i][s]) > eps) {
			T *b = D[i].data(), inv2 = b[s] * inv;
			rep(j, 0, n + 2) b[j] -= a[j] * inv2;
			b[s] = a[s] * inv2;
		}
		rep(j, 0, n + 2) if(j != s) D[r][j] *= inv;
		rep(i, 0, m + 2) if(i != r) D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool simplex(int phase) {
		int x = m + phase - 1;
		for(;;) {
			int s = -1;
			rep(j, 0, n + 1) if(N[j] != -phase) ltj(D[x]);
			if(D[x][s] >= -eps) return true;
			int r = -1;
			rep(i, 0, m) {
				if(D[i][s] <= eps) continue;
				if(r == -1 || MP(D[i][n + 1] / D[i][s], B[i])
						< MP(D[r][n + 1] / D[r][s], B[r])) r = i;
			}
			if(r == -1) return false;
			pivot(r, s);
		}
	}

	T solve(vd &x) {
		int r = 0;
		rep(i, 1, m) if(D[i][n + 1] < D[r][n + 1]) r = i;
		if(D[r][n + 1] < -eps) {
			pivot(r, n);
			if(!simplex(2) || D[m + 1][n + 1] < -eps) return -inf;
			rep(i, 0, m) if(B[i] == -1) {
				int s = 0;
				rep(j, 1, n + 1) ltj(D[i]);
				pivot(i, s);
			}
		}
		bool ok = simplex(1);
		x = vd(n);
		rep(i, 0, m) if(B[i] < n) x[B[i]] = D[i][n + 1];
		return ok ? D[m][n + 1] : inf;
	}
};


int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(12) << fixed;

	int n, x, R = 0;
	cin >> n >> x;

	vd C(n);
	for(int i = 0; i < n; ++i) {
		cin >> C[i];
		if(C[i])++R;
		C[i] =  - 1 +  C[i];
	}
	vvd A(2 * n + 1, vd(n));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			A[i][j] = inf;
		}
		A[i][i] = 0;
	}
	for(int i = 0; i < n - 1; ++i) {
		int a, b, w;
		cin >> a >> b >> w;
		--a;
		--b;
		A[a][b] = w;
		A[b][a] = w;
	}


	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if(A[i][k] < inf && A[k][j] < inf && A[i][k] + A[k][j] < A[i][j])
					A[i][j] = A[i][k] + A[k][j];

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			if(A[i][j] <= x) {
				A[i][j] =  - 1;
			} else {
				A[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < n; ++i) {
        A[n][i] = 1;
	}
	for(int i = 0; i < n; ++i) {
		A[n + 1 + i][i] =  - 1;
	}

	vd B(2 * n + 1);
	for(int i = 0; i < n; ++i) {
		B[i] =  - 1;
	}
	B[n] = R;

	vd X;

Debug(	cout << "A: " << endl;
	for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < n; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
	}

	cout << "B: " << endl;
	for (int i = 0; i < B.size(); ++i) {
        cout << B[i] << endl;
	}

	cout << "C: " << endl;
	for (int i = 0; i < C.size(); ++i) {
        cout << C[i] << endl;
	})

	double res = LPSolver(A, B, C).solve(X);


Debug(	cout << "X: " << endl;
	for (int i = 0; i < X.size(); ++i) {
        cout << X[i] << endl;
	}

	cout << "res: " << res << endl;)

	if (res <  - n - 100){
        cout <<  - 1 << endl;
	} else {
        cout << (int )( - res + 0.1) << endl;
	}
	return 0;
}
