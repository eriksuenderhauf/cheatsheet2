int inv[MAX];
void precompute_inverse(int n, int mod) {
	inv[1]=1;
	for (int i=2; i<=n; i++)
		inv[i] = (mod - (mod/i)*1LL*inv[mod%i] % mod) % mod;
}