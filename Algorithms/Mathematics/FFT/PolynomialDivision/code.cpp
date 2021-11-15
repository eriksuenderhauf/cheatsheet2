void divide(vector<int> a, vector<int> b, vector<int>& d, vector<int>& r) {
  int n = sz(a), m = sz(b);
  if (n-m+1 <= 0) { r = a; return; }
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  d = mul(a, inv(b, m)); d.resize(n-m+1);
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  reverse(d.begin(), d.end());
  r = sub(a, mul(b, d));
  r.resize(m);
}