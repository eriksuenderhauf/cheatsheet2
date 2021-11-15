struct hafnian {
  inline int add(int x, int y) { return x+y < mod ? x+y : x+y-mod; }
  inline int sub(int x, int y) { return x-y >= 0 ? x-y : x-y+mod; }
  typedef vector<int> poly;
  typedef vector<vector<poly>> mat;
  typedef unsigned long long ull;
  int n; mat a;
  hafnian() {}
  hafnian(int n, vector<poly>& b) : n(n) {
    a.resize(n);
    for (int i = 0; i < n; i++) {
      a[i].resize(i);
      assert(b[i][i] == 0);
      for (int j = 0; j < i; j++) {
        a[i][j] = poly(n / 2 + 1);
        a[i][j][0] = b[i][j];
        assert(b[i][j] == b[j][i]);
      }
    }
  }
  poly solve(const mat& b) {
    if (b.empty()) {
      poly r(n / 2 + 1);
      r[0] = 1; return r;
    }
    int m = (int)b.size();
    mat c = b;
    c.resize(m - 2);
    poly r = solve(c);
    for (int i = 0; i + 2 < m; i++)
      for (int j = 0; j < i; j++)
        for (int k = 0; k < n / 2; k++) {
          ull v = 0;
          for (int l = 0; l <= k; l++)
            v += (ull) b[m-2][i][l] * (ull) b[m-1][j][k - l] + (ull) b[m-1][i][l] * (ull) b[m-2][j][k - l];
          c[i][j][k+1] = add(v % mod, c[i][j][k+1]);
        }
    poly t = solve(c);
    for (int i = 0; i <= n / 2; i++) {
      ull v = t[i];
      for (int j = 0; j < i; j++)
        v += t[j] * (ull) b[m-1][m-2][i-j-1];
      r[i] = sub(v % mod, r[i]);
    }
    return r;
  }
  int calc() {
    return solve(a)[n / 2];
  }
};