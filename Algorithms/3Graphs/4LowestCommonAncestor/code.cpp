struct lowest_common_ancestor {
  int n, m = 0;
  vector<int> a, v, h;
  vector<vector<int>>& e;
  sparse_table st;
  lowest_common_ancestor(vector<vector<int>> & e, int r) : n(e.size()), a(n), v(2 * n - 1), h(2 * n - 1), e(e) {
    dfs(r);
    st = sparse_table(h);
  }
  void dfs(int i, int p = -1, int d = 0) {
    a[i] = m; v[m] = i; h[m++] = d;
    for (int j : e[i]) {
      if (j == p)
        continue;
      dfs(j, i, d - 1);
      v[m] = i; h[m++] = d;
    }
  }
  // calculate the lowest common ancestor of x and y
  int lca(int x, int y) {
    return v[st.query(min(a[x], a[y]), max(a[x], a[y]) + 1)];
  }
};
