struct DSU {
  vector<int> hist, lst = {0}, par, s;
  DSU(int n) : par(n+1), s(n+1) {
    iota(par.begin(), par.end(), 0);
    fill(s.begin(), s.end(), 1);
  }
  int qry(int x) {
    return par[x] == x ? x : qry(par[x]);
  }
  void join(int x, int y) {
    if ((x=qry(x)) == (y=qry(y))) {
        hist.push_back(-1);
      return;
    }
    if (s[y] < s[x])
      swap(x, y);
    s[par[x] = y] += s[x];
    hist.push_back(x);
  }
  void snapshot() {
    lst.push_back((int)hist.size());
  }
  void rollback() {
    while (hist.size() != lst.back()) {
      int u = hist.back();
      if (0 <= u)
        s[par[u]] -= s[u], par[u] = u;
      hist.pop_back();
    }
    lst.pop_back();
  }
};