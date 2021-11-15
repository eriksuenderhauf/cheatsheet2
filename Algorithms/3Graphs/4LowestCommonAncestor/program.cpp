#include <bits/stdc++.h>

using namespace std;

#define log2(x) (31 - __builtin_clz(x))

struct sparse_table {
  int n;
  vector<int> a;
  vector<vector<int>> st;
  int combine(int dl, int dr) {
    return a[dl] > a[dr] ? dl : dr;
  }
  sparse_table() {}
  sparse_table(vector<int> & a) : n(a.size()), a(a), st(log2(n) + 1, vector<int>(n)) {
    for (int i = 0; i < n; i++)
      st[0][i] = i;
    for (int j = 1; 1 << j <= n; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[j][i] = combine(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
  }
  // query the data on the range [l, r[
  int query(int l, int r) {
    int s = log2(r - l);
    return combine(st[s][l], st[s][r - (1 << s)]);
  }
};

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

int main() {
  int n, q, r, a, b;
  cin >> n >> q >> r, r--;
  vector<vector<int>> e(n);
  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b, a--, b--;
    e[a].push_back(b);
    e[b].push_back(a);
  }
  lowest_common_ancestor lca(e, r);
  for (int i = 0; i < q; i++) {
    cin >> a >> b, a--, b--;
    cout << lca.lca(a, b) + 1 << "\n";
  }
}
