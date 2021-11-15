const int MOD = 1000000007; //prime!

//using fast exp ll fpow(ll a, ll b)
vector<ll> BerlekampMassey(vector<ll> s) {
	int n = s.size(), L = 0, m = 0;
	vector<ll> C(n), B(n), T;
	C[0] = B[0] = 1;
	ll b = 1;
	for (int i=0; i<n; i++) {
		++m; ll d = s[i] % MOD;
		for (int j=1; j<=L; j++)
			d=(d + C[j] * s[i - j])%MOD;
		if (!d) continue;
		T = C; ll coef = d * fpow(b, MOD-2)%MOD;
		for (int j=m; j<n; j++)
			C[j] = (C[j] - coef * B[j - m])%MOD;
		if (2 * L > i) continue;
		L = i + 1 - L; B = T; b = d; m = 0;
	}
	C.resize(L + 1); C.erase(C.begin());
	for (auto &x : C)
		x=(MOD-x)%MOD;
	return C;
}
//BerlekampMassey({0, 1, 1, 3, 5, 11}) -> {1,2}
