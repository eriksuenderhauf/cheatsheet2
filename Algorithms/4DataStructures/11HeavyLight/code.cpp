struct HLD {
  vector<int> par, depth, root, heavy, pos;
  vector<vector<int>>& e;

  HLD(int n, vector<vector<int>> & e) : e(e), par(n+1), depth(n+1), root(n+1), heavy(n+1), pos(n+1) {
    fill(heavy.begin(), heavy.end(), -1);
    par[1] = -1, depth[1] = 0;
    dfs(1);
    for (int i = 1, cur = 0; i <= n; i++)
      if (par[i] == -1 || heavy[par[i]] != i)
        for (int j = i; j != -1; j = heavy[j])
          root[j] = i, pos[j] = cur++;
  }
  int dfs(int u) {
    int sz = 1, mx = 0;
    for (int v: e[u]) if (v != par[u]) {
      par[v] = u;
      depth[v] = depth[u] + 1;
      int sub = dfs(v);
      if (sub > mx)
        mx = sub, heavy[u] = v;
      sz += sub;
    }
    return sz;
  }
  template<class T> void work(int u, int v, T op) {
    for (; root[u] != root[v]; v = par[root[v]]) {
      if (depth[root[u]] > depth[root[v]])
        swap(u, v);
      op(root[v], pos[root[v]], pos[v]);
    }
    if (depth[u] > depth[v]) swap(u, v);
    op(root[u], pos[u], pos[v]);
  }
  int dist(int u, int v) {
    int ret = -1;
    work(u, v, [this, &ret](int x, int l, int r) { 
      ret += r - l + 1;
    });
    return ret;
  }
};