#include <bits/stdc++.h>
#define st first
#define nd second
using namespace std;
const int inf = 1e9 + 7;
struct segment_tree {
  typedef pair<int,int> data;
  typedef int operation;
  static data combine(data dl, data dr) {
    if (dl.st <= dr.st)
      return dl;
    return dr;
  }
  static data calculate(operation o, data d) {
    return {d.st + o, d.nd};
  }
  static operation merge(operation ot, operation ob) {
    return ot + ob;
  }
  int n, h;
  vector<data> t;
  vector<operation> o;
  segment_tree(int n = 0) : n(n), h(32 - __builtin_clz(n)), t(2 * n), o(n) {}
  segment_tree(vector<data> & a) : segment_tree(a.size()) {
    for (int i = 0; i < n; i++)
      t[i + n] = a[i];
    for (int x = n - 1; x > 0; x--)
      t[x] = combine(t[x << 1], t[x << 1 | 1]);
  }
  void apply(int x, operation op) {
    t[x] = calculate(op, t[x]);
    if (x < n)
      o[x] = merge(op, o[x]);
  }
  void push(int x) {
    for (int s = h; s > 0; s--) {
      int c = x >> s;
      apply(c << 1, o[c]);
      apply(c << 1 | 1, o[c]);
      o[c] = operation();
    }
  }
  void build(int x) {
    while (x >>= 1)
      t[x] = calculate(o[x], combine(t[x << 1], t[x << 1 | 1]));
  }
  // set the data at the position i
  void setValue(int i, data d) {
    i += n;
    push(i);
    t[i] = d;
    build(i);
  }
  // query the data on the range [l, r[
  data query(int l, int r) {
    l += n; r += n;
    push(l); push(r - 1);
    data dl = {inf, -1}, dr = {inf, -1};
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        dl = combine(dl, t[l++]);
      if (r & 1)
        dr = combine(t[--r], dr);
    }
    return combine(dl, dr);
  }
  // apply an operation on the range [l, r[
  void apply(int l, int r, operation op) {
    l += n; r += n;
    push(l); push(r - 1);
    int xl = l, xr = r;
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        apply(l++, op);
      if (r & 1)
        apply(--r, op);
    }
    build(xl); build(xr - 1);
  }
};

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
const int mod = 998244353;
int ans = 0, x;
permutation_tree p;
void dfs(int u) {
  if (p.cmb[u]) {
    vector<int> a;
    for (int v: p.nx[u])
      a.push_back(p.R[v] - p.L[v] + 1);
    for (int i = 0, j = 0, y = 0;; i++) {
      while (j < a.size() && y < x)
        y += a[j++];
      if (y < x) break;
      ans += i * 1ll * (a.size() - j) * 1ll * (a.size() - j + 1) / 2 % mod;
      if (ans >= mod)
        ans -= mod;
      y -= a[i];
    }
  }
  for (int v: p.nx[u])
    dfs(v);
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n >> x;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  p = permutation_tree(n, a);
  p.build();
  dfs(p.root);
  cout << ans * 2 % mod << endl;
}