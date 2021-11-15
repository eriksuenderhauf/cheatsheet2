const int MOD = 998244353; // 119 * 2^23 + 1
const int root = 565042129; // 3^(119 * 2^3)
const int root_pw = 1 << 20; // order of root
const int root_1 = mod_inverse(root, MOD);

void fft(vector<int> & a, bool invert) {
	int n = a.size();
	for(int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (j ^= bit; !(j&bit); j ^= (bit>>=1));
		if (i < j)
			swap(a[i], a[j]);
	}
	for(int len = 2; len <= n; len <<= 1) {
		int wlen = invert ? root_1 : root;
		for(int i = len; i < root_pw; i <<= 1)
			wlen = 1LL * wlen * wlen % MOD;
		for(int i = 0; i < n; i += len) {
			for(int j=i, w=1; j < i + len/2; j++) {
				int u=a[j], v=1LL*a[j+len/2]*w % MOD;
				a[j] = u+v < MOD ? u+v : u+v-MOD;
				a[j+len/2] = u-v < 0 ? u-v+MOD : u-v;
				w = 1LL * w * wlen % MOD;
			}
		}
	}
	if(invert) {
		int n_1 = mod_inverse(n, MOD);
		for(int & x : a)
			x = 1LL * x * n_1 % MOD;
	}
}
