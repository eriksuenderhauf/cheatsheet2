const int mod = 998244353;
struct Poly : vector<int> {
Poly() : vector<int>() {}
Poly(int n) : vector<int>(n) {}
Poly(vector<int> a) : vector<int>(a) {}
Poly range(int l, int r) {
  return vector<int>(begin()+l, begin()+r+1);
}
vector<int> eval(const vector<int>& b) {
  int n = size(), cnt = 0;
  vector<int> L(2*n-1,0), R(2*n-1,0), pos(n);
  vector<Poly> p(2*n-1), q(2*n-1);
  function<int(int,int)> dfs = [&](int l, int r) {
    if (l == r) {
      q[cnt] = Poly({mod-b[l], 1});
      return pos[l] = cnt++;
    }
    int m = (l+r) / 2, nk = cnt++;
    L[nk] = dfs(l, m), R[nk] = dfs(m+1, r);
    q[nk] = q[L[nk]] * q[R[nk]];
    return nk;
  };
  dfs(0, n-1); resize(2*n); n *= 2;
  reverse(all(q[0])); q[0] = q[0].invert(); 
  reverse(all(q[0]));
  p[0] = ((*this) * q[0]).range(sz(q[0])-1, n-1);
  for (int i = 0; i < n - 1; i++) if (L[i]) {
    p[L[i]] = (p[i] * q[R[i]]).range(sz(q[R[i]])-1, sz(p[i])-1);
    p[R[i]] = (p[i] * q[L[i]]).range(sz(q[L[i]])-1, sz(p[i])-1);
  }
  vector<int> ret(n);
  for (int i = 0; i < n / 2; i++)
    ret[i] = p[pos[i]][0];
  return ret;
}
vector<int> evaluate(const vector<int>& b) {
  if (size() == 1)
    return vector<int>(sz(b), (*this)[0]);
  int m = max((int)size() + 1, sz(b));
  vector<int> tmp = b; tmp.resize(m);
  Poly cp = *this; cp.resize(m);
  vector<int> ret = cp.eval(tmp); ret.resize(sz(b));
  return ret;
}
};