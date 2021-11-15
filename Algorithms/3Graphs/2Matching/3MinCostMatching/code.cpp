struct minBPM {
  vector<ll> mi, s, t;
  vector<int> mt, id, vis;
  int n, m;
  minBPM(int n, int m) : n(n),m(m),mi(m+1),s(m+1),t(n+1),mt(m+1),id(m+1),vis(m+1) {}
  ll matching(vector<vector<ll>> & a) {
    for (int i = 1, x, nx, y; i <= n; i++) {
      fill(vis.begin(), vis.end(), 0);
      fill(mi.begin(), mi.end(), 1e18);
      mt[x=0] = i;
      do {
        vis[x] = 1, y = mt[x], nx = 0;
        ll d = 1e18;
        for (int j = 1; j <= m; j++) {
          if (vis[j]) continue;
          ll v = a[y][j] - s[j] - t[y];
          mi[j] = v<mi[j] ? id[j]=x,v : mi[j];
          d = mi[j] < d ? nx=j, mi[j] : d;
        }
        for (int j = 0; j <= m; mi[j++] -= d)
          if (vis[j])
            s[j] -= d, t[mt[j]] += d;
      } while (mt[x = nx] != 0);
      for (;x!=0; mt[x]=mt[id[x]], x=id[x]);
    }
    return -s[0];
  }
};