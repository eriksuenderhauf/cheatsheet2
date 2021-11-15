vector<int> inv(vector<int> x, int n) {
  vector<int> ret(1,pw(x[0], MOD-2));
  int k = 1;
  for (; k < n; k *= 2) {
    vector<int> tmp = mul(mul(ret, ret), vector<int>(x.begin(), x.begin() + min(2*k,sz(x)-1) + 1));
    for (int i = 0; i < sz(tmp); i++) {
      tmp[i] = (i < sz(ret) ? 2 * ret[i] : 0) - tmp[i];
      tmp[i] += tmp[i] < 0 ? MOD : (tmp[i] >= MOD ? -MOD : 0);
    }
    tmp.resize(2 * k); ret = tmp;
  }
  ret.resize(n);
  return ret;
}