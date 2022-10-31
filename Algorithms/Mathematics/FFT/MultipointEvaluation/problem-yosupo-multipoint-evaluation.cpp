#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define Poly vector<int>
using namespace std;
const int mod = 998244353; // 119 * 2^23 + 1
const int root = 15311432; // 3^119
const int iroot = 469870224; // 1 / root
const int root_pw = 1 << 23;

int pw(int x, int y) {
  int r = 1;
  for (; y; y /= 2, x = x * 1ll * x % mod)
    if (y & 1)
      r = x * 1ll * r % mod;
  return r;
}
void fft(Poly& a, int inv = 0) {
  int n = sz(a);
  for(int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (j ^= bit; !(j&bit); j ^= (bit>>=1));
    if (i < j)
      swap(a[i], a[j]);
  }
  for(int l = 1; 2 * l <= n; l *= 2) {
    int wl = inv ? iroot : root;
    for (int i = l; 2 * i < root_pw; i *= 2)
      wl = wl * 1ll * wl % mod;
    for(int i = 0; i < n; i += 2 * l) {
      for (int j = i, w = 1; j < i + l; j++) {
        int u = a[j], v = a[j+l]*1ll*w % mod;
        a[j] = u+v < mod ? u+v : u+v-mod;
        a[j + l] = u-v < 0 ? u-v+mod : u-v;
        w = w * 1ll * wl % mod;
      }
    }
  }
  if (inv) {
    n = pw(n, mod - 2);
    for (int& i: a)
      i = n * 1ll * i % mod;
  }
}
// returns the coefficients [l, r[ of p
Poly range(const Poly& p, int l, int r) {
  return Poly(p.begin()+l, p.begin()+min(r,sz(p)));
}
Poly operator*(Poly x, Poly y) {
  int n = 2, s = sz(x) + sz(y) - 1;
  while (n / 2 < max(sz(x), sz(y))) n *= 2;
  x.resize(n);
  y.resize(n);
  fft(x), fft(y);
  for (int i = 0; i < n; i++)
    x[i] = x[i] * 1ll * y[i] % mod;
  fft(x, 1);
  x.resize(s);
  return x;
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
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  Poly a(n), b(m);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < m; i++)
    cin >> b[i];
  Poly c = evaluate(a, b);
  for (int i: c)
    cout << i << " ";
  cout << endl;
}