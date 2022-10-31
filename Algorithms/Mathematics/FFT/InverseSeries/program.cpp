#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define Poly vector<int>
#define pb push_back
typedef long long ll;
using namespace std;
const int mod = 998244353;
const int root = 15311432;
const int iroot = 469870224;
const int mxpw = 1 << 23;

int pw(int x, int y) {
  int r = 1;
  for (; y; y /= 2, x = x * 1ll * x % mod)
    if (y & 1)
      r = x * 1ll * r % mod;
  return r;
}
// returns the coefficients [l, r[ of p
Poly range(const Poly& p, int l, int r) {
  return Poly(p.begin()+l, p.begin()+min(r,sz(p)));
}
// replace with fft
Poly operator*(const Poly& x, const Poly& y) {
  Poly r(sz(x) + sz(y) - 1);
  for (int i = 0; i < sz(x); i++)
    for (int j = 0; j < sz(y); j++)
      r[i + j] = (r[i + j] + x[i] * 1ll * y[j]) % mod;
  return r;
}
Poly operator+(const Poly& x, const Poly& y) {
  Poly r = x; r.resize(max(sz(x), sz(y)));
  for (int i = 0; i < sz(y); i++)
    r[i] = (r[i] + y[i]) % mod;
  return r;
}
Poly operator-(const Poly& x, const Poly& y) {
  Poly r = x; r.resize(max(sz(x), sz(y)));
  for (int i = 0; i < sz(y); i++)
    r[i] = (r[i] - y[i] + mod) % mod;
  return r;
}
Poly invert(const Poly& x, int s) {
  Poly ret = {pw(x[0], mod - 2)};
  int k = 1;
  for (; k < s; k *= 2) {
    ret = ret + ret - (ret * ret) * range(x, 0, 2 * k);
    ret.resize(2 * k);
  }
  ret.resize(s);
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  vector<int> p(n + 1,0);
  for (int i = 0; i <= n; i++)
    cin >> p[i];
  p = invert(p, m);
  for (int x: p)
    cout << x << " ";
  cout << "\n";
}