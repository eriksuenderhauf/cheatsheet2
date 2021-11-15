void fwht(vector<int>& a, bool inv = 0) {
  int n = int(a.size()); assert((n&-n) == 0);
  for (int i = 2; i <= n; i *= 2)
    for (int j = 0; j < n; j += i)
      for (int k = j; k < j+i/2; k++) {
        int u = a[k], v = a[k+i/2];
        a[k] = u+v >= mod ? u+v : u+v-mod;
        a[k+i/2] = u-v < 0 ? u-v+mod : u-v;
      }
  if (inv) {
    n = pw(n, mod-2);
    for (int i = 0; i < n; i++)
      a[i] = a[i] * 1ll * n % mod;
  }
}