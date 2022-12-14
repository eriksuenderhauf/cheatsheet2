const int mod = 998244353; // 119 * 2^23 + 1
const int root = 15311432; // 3^119
const int iroot = 469870224; // 1 / root
const int root_pw = 1 << 23;

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
			i = n * 1ll * i % mod;
	}
}

Poly operator*(Poly x, Poly y) {
	int n = 2, s = sz(x) + sz(y) - 1;
	while (n / 2 < max(sz(x), sz(y))) n *= 2;
	x.resize(n);
	y.resize(n);
	fft(x), fft(y);
	for (int i = 0; i < n; i++)
		x[i] = x[i] * 1ll * y[i] % mod;
	fft(x, 1);
	x.resize(s);
	return x;
}