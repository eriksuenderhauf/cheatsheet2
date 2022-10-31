#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define Poly vector<int>
#define pb push_back
typedef long long ll;
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
ll g(ll k) {
  return k * (3*k-1) / 2;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  vector<int> p(n);
  for (int& i: p)
    cin >> i;
  p = invert(p, n);
  for (int i: p)
    cout << i << " ";
  cout << endl;
}