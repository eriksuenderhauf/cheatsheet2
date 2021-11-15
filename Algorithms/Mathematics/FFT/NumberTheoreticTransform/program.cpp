// Codeforces Task 1096G - Lucky Tickets

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// return a % b (positive value)
ll mod(ll a, ll m) {
	return ((a % m) + m) % m;
}

// returns d = gcd(a,b); finds x,y such that d = ax + by
int extended_euclid(int a, int b, int &x, int &y) {
	int xx = y = 0;
	int yy = x = 1;
	while(b) {
		int q = a / b;
		int t = b;
		b = a % b;
		a = t;
		t = xx;
		xx = x - q * xx;
		x = t;
		t = yy;
		yy = y - q * yy;
		y = t;
	}
	return a;
}

// computes b such that ab = 1 (mod n), returns -1 on failure
int mod_inverse(int a, int n) {
	int x, y;
	int d = extended_euclid(a, n, x, y);
	if(d > 1) return -1;
	return mod(x, n);
}

// return a^b mod m
ll powmod(ll a, ll b, ll m) {
	ll res = 1;
	while(b > 0)
		if(b & 1)
			res = (res * a) % m, --b;
		else
			a = (a * a) % m, b >>= 1;
	return res % m;
}

const int MOD = 998244353; // 119 * 2^23 + 1
const int root = 565042129; // 3^(119 * 2^3)
const int root_pw = 1 << 20; // order of root
const int root_1 = mod_inverse(root, MOD);

void fft(vector<int> & a, bool invert) {
	int n = a.size();

	for(int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for(; j & bit; bit >>= 1)
			j ^= bit;
		j ^= bit;

		if(i < j)
			swap(a[i], a[j]);
	}

	for(int len = 2; len <= n; len <<= 1) {
		int wlen = invert ? root_1 : root;
		for(int i = len; i < root_pw; i <<= 1)
			wlen = (int)(1LL * wlen * wlen % MOD);

		for(int i = 0; i < n; i += len) {
			int w = 1;
			for(int j = 0; j < len / 2; j++) {
				int u = a[i + j], v = (int)(1LL * a[i + j + len / 2] * w % MOD);
				a[i + j] = u + v < MOD ? u + v : u + v - MOD;
				a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
				w = (int)(1LL * w * wlen % MOD);
			}
		}
	}

	if(invert) {
		int n_1 = mod_inverse(n, MOD); // modular inverse
		for(int & x : a)
			x = (int)(1LL * x * n_1 % MOD);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(12) << fixed;

	int n, k;
	cin >> n >> k;
	vector <int> f(root_pw, 0);

	for(int i = 0; i < k; ++i) {
		int d;
		cin >> d;
		f[d]++;
	}
	n /= 2;

	fft(f, false);

	for(int i = 0; i < root_pw; ++i) {
		f[i] = powmod(f[i], n, MOD);
	}
	fft(f, true);
	ll result = 0;
	for(auto x : f) {
		result += ((ll)x) * x;
		result %= MOD;
	}
	cout << result << endl;

	return 0;
}
