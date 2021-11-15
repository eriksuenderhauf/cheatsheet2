struct fenwick_tree {
  int n;
  vector<int> a, f;
  fenwick_tree(int n = 0) : n(n), a(n), f(n + 1) {}
  fenwick_tree(vector<int> & a) : fenwick_tree(a.size()) {
    for (int i = 0; i < n; i++)
      setValue(i, a[i]);
  }
  void changeValue(int i, int d) {
    for (a[i++] += d; i <= n; i += i & -i)
      f[i] += d;
  }
  void setValue(int i, int v) {
    changeValue(i, v - a[i]);
  }
  int getSum(int i) {
    int s = 0;
    for (i++; i; i -= i & -i)
      s += f[i];
    return s;
  }
  // get the sum of the range [l, r[
  int getSum(int l, int r) {
    return getSum(r - 1) - getSum(l - 1);
  }
};
