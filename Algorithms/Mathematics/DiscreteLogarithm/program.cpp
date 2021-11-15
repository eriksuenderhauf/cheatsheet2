// Codeforces round 536 div2 F: Lunar New Year and a Recursive Sequence (https://codeforces.com/problemset/problem/1106/F)

#include <bits/stdc++.h>

using namespace std;

#define D(x) x
#define REP(i,a,b) for (int i = (a); i < (b); ++i)
#define REPR(i,a,b) for (int i = (b) - 1; i >= (a); --i)
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<vector<int> > VII;

const ll p = 998244353;


ll  a[105][105], a2[105][105];
ll  b[105], res[105], res2[105];
ll k, n, m;

// return a^b mod m
ll powmod(ll a, ll b, ll m) {
	ll res = 1;
	while(b > 0) {
		if(b & 1) res = (res * a) % m;
		a = (a * a) % m;
		b /= 2;
	}
	return res % m;
}

// Return x such that x^a = b mod m or -1 otherwise. Runtime O(sqrt(m) * log(m)).
int dl(int a, int b, int m) {
	int n = sqrt((double)m) + 1;
	map<int, int> vals;
	for(int i = n; i >= 1; --i)
		vals[powmod(a, i * n, m)] = i;
	for(int i = 0; i <= n; ++i) {
		int cur = (powmod(a, i, m) * b) % m;
		if(vals.count(cur)) {
			int ans = vals[cur] * n - i;
			if(ans < m) return ans;
		}
	}
	return -1;
}


void solve() {
	cin >> k;
	for(int i = 0; i < k; ++i) {
		cin >> b[i];
		a[k - 1 - i][k - 1] = b[i];
	}
	for(int i = 0; i < k - 1; ++i) {
		a[i + 1][i] = 1;
	}
	cin >> n >> m;
	ll  x = n - k;
	res[k - 1] = 1;

	for(int i = 0; x > 0; ++i) {
		if(x % 2) {
			for(int j = 0; j < k; ++j) {
				res2[j] = 0;
				for(int l = 0; l < k; ++l) {
					res2[j] += res[l] * a[l][j];
					res2[j] %= p - 1;
				}
			}
			for(int j = 0; j < k; ++j) {
				res[j] = res2[j];
			}
		}
		x /= 2;
		for(int j = 0; j < k; ++j) {
			for(int s = 0; s < k; ++s) {
				a2[j][s] = 0;
				for(int t = 0; t < k; ++t) {
					a2[j][s] += a[j][t] * a[t][s];
					a2[j][s] %= p - 1;
				}
			}
		}
		for(int j = 0; j < k; ++j)
			for(int s = 0; s < k; ++s)
				a[j][s] = a2[j][s];
	}
	x = res[k - 1];
//	cout << x << endl;



	int y = dl(powmod(3, x, p), m, p);
	if(y ==  - 1) {
		cout <<  - 1 << endl;
	} else {
	//    int z = powmod(3, y, p);
		cout << powmod(3, y, p) << endl;
	//	cout << powmod(z, x,  p) << endl;
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(12) << fixed;

	solve();

	return 0;
}
