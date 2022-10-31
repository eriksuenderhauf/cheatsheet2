void fwht(vector<int>& a, int inv = 0) {
  int n = sz(a); assert((n&-n) == n);
  for (int i = 2; i <= n; i *= 2)
    for (int j = 0; j < n; j += i)
      for (int k = j; k < j+i/2; k++) {
        int u = a[k], v = a[k+i/2];
        a[k] = u+v >= mod ? u+v : u+v-mod;
        a[k+i/2] = u-v < 0 ? u-v+mod : u-v;
      }
  if (inv) {
    n = pw(n, mod-2);
    for (int& i: a)
      i = i * 1ll * n % mod;
  }
}