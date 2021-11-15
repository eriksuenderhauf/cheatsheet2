struct lis {
  int n, l = 0;
  vector<int> v, e, p;
  lis(vector<int> & a) : n(a.size()), v(n), e(n), p(n) {
    for (int i = 0; i < n; i++) {
      int j = lower_bound(v.begin(), v.begin() + l, a[i]) - v.begin();
      v[j] = a[i]; e[j] = i; p[i] = (j > 0 ? e[j - 1] : -1);
      l = max(l, j + 1);
    }
  }
};
