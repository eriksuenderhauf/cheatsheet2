struct permutation_tree {
  vector<int> p, na, nb, L, R, cmb;
  vector<vector<int>> nx;
  segment_tree seg;
  int n, cnt = 0, root = 0;
  permutation_tree() : n(0) {}
  permutation_tree(int n, vector<int>& p) : n(n), p(p), na(n), nb(n), L(2*n), R(2*n), cmb(2*n), nx(2*n) {}
  void build() {
    vector<pair<int,int>> dat;
    for (int i = 0; i < n; i++)
      dat.push_back({i, i});
    seg = segment_tree(dat);
    stack<int> s;
    for (int i = 0; i < n; i++) {
      for (na[i] = i-1; ~na[i] && p[na[i]] < p[i]; na[i] = na[na[i]])
        seg.apply(na[na[i]] + 1, na[i] + 1, p[i] - p[na[i]]);
      for (nb[i] = i-1; ~nb[i] && p[nb[i]] > p[i]; nb[i] = nb[nb[i]])
        seg.apply(nb[nb[i]] + 1, nb[i] + 1, p[nb[i]] - p[i]);
      int u = cnt++;
      L[u] = R[u] = i;
      auto ask = [&](int j) { return seg.query(j, j+1).st; };
      while (!s.empty() && seg.query(0, n).nd <= L[s.top()]) {
        if (cmb[s.top()] && ask(L[nx[s.top()][1]]) <= i) {
          R[s.top()] = i;
          nx[s.top()].push_back(u);
          u = s.top(); s.pop();
        } else if (ask(L[s.top()]) <= i) {
          cmb[cnt] = 1;
          L[cnt] = L[s.top()];
          R[cnt] = i;
          nx[cnt].push_back(s.top()); s.pop();
          nx[cnt].push_back(u);
          u = cnt++;
        } else {
          nx[cnt].push_back(u);
          int v = -1;
          do {
            v = s.top(); s.pop();
            nx[cnt].push_back(v);
          } while (ask(L[v]) > i);
          L[cnt] = L[v];
          R[cnt] = i;
          u = cnt++;
        }
      }
      s.push(u);
    }
    while (s.size() > 1)
      s.pop();
    root = s.top();
  }
};