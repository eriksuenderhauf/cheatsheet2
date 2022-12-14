#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define Poly vector<int>
using namespace std;
const int mod = 998244353;

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
Poly evaluate(const Poly& x, Poly b) {
  int n = max(sz(x) + 1, sz(b));
  vector<Poly> p(2 * n), q(2 * n);
  for (int i = 0; i < n; i++)
    q[i + n] = {i < sz(b) ? mod - b[i] : 0, 1};
  for (int i = n - 1; i > 0; i--)
    q[i] = q[2 * i] * q[2 * i + 1];
  reverse(all(q[1])); q[1] = invert(q[1], sz(q[1]));
  reverse(all(q[1]));
  p[1] = range(x * q[1], sz(q[1]) - 1, 2 * n);
  p[1].resize(2 * n - sz(q[1]) + 1);
  for (int i = 2; i < sz(b) + n; i++)
    p[i] = range(p[i / 2] * q[i ^ 1], sz(q[i ^ 1]) - 1, sz(p[i / 2]));
  for (int i = 0; i < sz(b); i++)
    b[i] = p[i + n][0];
  return b;
}

int main() {
  Poly p({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21});
  vector<int> b({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21});
  auto r = evaluate(p, b);
  for (int i = 0; i < sz(b); i++) {
    int v = 0;
    for (int j = sz(p)-1; ~j; j--)
      v = (v * 1ll * b[i] + p[j]) % mod;
    cout << r[i] << " " << v << "\t" << r[i] - v << endl;
  }
}