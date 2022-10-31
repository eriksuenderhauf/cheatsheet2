#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define Poly vector<int>
const double pi = acos(-1);
using namespace std;

const int mod = 998244353; // 119 * 2^23 + 1
const int root = 15311432; // 3^119
const int iroot = 469870224; // 1 / root
const int root_pw = 1 << 23;

int pw(int x, int y) {
	int r = 1;
	for (; y; y /= 2, x = x * 1ll * x % mod)
		if (y & 1)
			r = r * 1ll * x % mod;
	return r;
}

void fft(Poly& a, int inv = 0) {
	int n = sz(a);
	for(int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (j ^= bit; !(j&bit); j ^= (bit>>=1));
		if (i < j)
			swap(a[i], a[j]);
	}
	for(int l = 1; 2 * l <= n; l *= 2) {
		int wl = inv ? iroot : root;
		for (int i = l; 2 * i < root_pw; i *= 2)
			wl = wl * 1ll * wl % mod;
		for(int i = 0; i < n; i += 2 * l) {
			for (int j = i, w = 1; j < i + l; j++) {
				int u = a[j], v = a[j+l]*1ll*w % mod;
				a[j] = u+v < mod ? u+v : u+v-mod;
				a[j + l] = u-v < 0 ? u-v+mod : u-v;
				w = w * 1ll * wl % mod;
			}
		}
	}
	if (inv) {
		n = pw(n, mod - 2);
		for (int& i: a)
			i = i * 1ll * n % mod;
	}
}

Poly operator*(Poly a, Poly b) {
	int n = 2, s = sz(a) + sz(b) - 1;
	while (n / 2 < max(sz(a), sz(b))) n *= 2;
	a.resize(n);
	b.resize(n);
	fft(a), fft(b);
	for (int i = 0; i < n; i++)
		a[i] = a[i] * 1ll * b[i] % mod;
	fft(a, 1);
	a.resize(s);
	return a;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  Poly a(n), b(m);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < m; i++)
    cin >> b[i];
  a = a * b;
  for (int i = 0; i < n + m - 1; i++)
    cout << a[i] << " ";
  cout << endl;
}