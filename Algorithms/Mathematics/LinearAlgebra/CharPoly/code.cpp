void transform(vector<vector<int>>& a) {
  int n = sz(a);
  for (int j = 0; j + 2 < n; j++) {
    int i = j+2; while (i < n && a[i][j] == 0) i++;
    if (i == n) continue;
    if (a[j+1][j] == 0) {
      swap(a[i], a[j+1]);
      for (int k = 0; k < n; k++)
        swap(a[k][i], a[k][j+1]);
    }
    int v = pw(a[j+1][j], mod-2);
    for (int k = j+2; k < n; k++) {
      int u = a[k][j] * 1ll * v % mod;
      for (int l = 0; l < n; l++) {
        a[k][l] = (a[k][l] - u * 1ll * a[j+1][l]) % mod;
        a[k][l] += a[k][l] < 0 ? mod : 0;
        a[l][j+1] = (a[l][j+1] + u * 1ll * a[l][k]) % mod;
      }
    }
  }
}
vector<int> calc(vector<vector<int>>& a) {
  transform(a);
  int n = sz(a);
  vector<vector<int>> p(n+1); p[0] = {1};
  for (int k = 0; k < n; k++) {
    p[k+1] = vector<int>({!a[k][k] ? 0 : mod-a[k][k], 1}) * p[k];
    int v = 1;
    for (int i = 0; i < k; i++) {
      v = v * 1ll * a[k-i][k-i-1] % mod;
      p[k+1] = p[k+1] - (v * 1ll * a[k-i-1][k] % mod) * p[k-i-1];
    }
  }
  return p[n];
}