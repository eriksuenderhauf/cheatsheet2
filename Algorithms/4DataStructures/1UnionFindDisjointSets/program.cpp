#include <bits/stdc++.h>

using namespace std;

struct DSU {
  vector<int> hist, lst = {0}, par, sz;
  DSU(int n) : par(n+1), sz(n+1) {
    iota(par.begin(), par.end(), 0);
    fill(sz.begin(), sz.end(), 1);
  }
  int qry(int x) {
    return par[x] == x ? x : qry(par[x]);
  }
  void join(int x, int y) {
    x = qry(x), y = qry(y);
    if (x == y) {
        hist.push_back(-1);
      return;
    }
    if (sz[y] < sz[x])
      swap(x, y);
    par[x] = y;
    sz[y] += sz[x];
    hist.push_back(x);
  }
  void snapshot() {
    lst.push_back((int)hist.size());
  }
  void rollback() {
    while (hist.size() != lst.back()) {
      int u = hist.back();
      if (0 <= u) {
        sz[par[u]] -= sz[u];
        par[u] = u;
      }
      hist.pop_back();
    }
    lst.pop_back();
  }
};

int main() {
  int n, q, t, a, b;
  cin >> n >> q;
  DSU u(n);
  for (int i = 0; i < q; i++) {
    cin >> t >> a, a--;
    if (t < 3)
      cin >> b, b--;
    if (t == 1)
      u.join(a, b);
    else if (t == 2)
      cout << (u.qry(a) == u.qry(b) ? "In same set\n" : "Not in same set\n");
    else
      cout << u.sz[u.qry(a)] << "\n";
  }
}
