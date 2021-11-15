#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
using namespace std;
const int mod = 998244353;
struct Poly : vector<int> {
  Poly() : vector<int>() {}
  Poly(int n) : vector<int>(n) {}
  Poly(vector<int> a) : vector<int>(a) {}
  int pw(int x, int y) {
    int r = 1;
    for (; y; y /= 2, x = x * 1ll * x % mod)
      if (y & 1)
        r = x * 1ll * r % mod;
    return r;
  }
  void mirror() {
    reverse((*this).begin(), (*this).end());
  }
  Poly range(int l, int r) {
    return vector<int>(begin()+l, begin()+r+1);
  }
  Poly invert() {
    Poly ret = vector<int>({pw((*this)[0], mod - 2)});
    int k = 1;
    for (; k < size(); k *= 2) {
      ret = ret + ret - (ret * ret) * (*this).range(0, 2*k-1);
      ret.resize(2*k);
    }
    ret.resize(size());
    return ret;
  }
  // replace with fft
  friend Poly operator*(const Poly& x, const Poly& y) {
    Poly r(sz(x) + sz(y) - 1);
    for (int i = 0; i < sz(x); i++)
      for (int j = 0; j < sz(y); j++)
        r[i + j] = (r[i + j] + x[i] * 1ll * y[j]) % mod;
    return r;
  }
  friend Poly operator+(const Poly& x, const Poly& y) {
    Poly r = x; r.resize(max(sz(x), sz(y)));
    for (int i = 0; i < sz(y); i++)
      r[i] = (r[i] + y[i]) % mod;
    return r;
  }
  friend Poly operator-(const Poly& x, const Poly& y) {
    Poly r = x; r.resize(max(sz(x), sz(y)));
    for (int i = 0; i < sz(y); i++)
      r[i] = (r[i] - y[i] + mod) % mod;
    return r;
  }
  vector<int> eval(const vector<int>& b) {
    int n = size();
    vector<int> L(2*n-1, 0), R(2*n-1, 0), pos(n);
    vector<Poly> p(2*n-1), q(2*n-1);
    int cnt = 0;
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
    q[0].mirror(); q[0] = q[0].invert(); q[0].mirror();
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

int main() {
  Poly p({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21});
  vector<int> b({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21});
  auto r = p.evaluate(b);
  for (int i = 0; i < sz(b); i++) {
    int v = 0;
    for (int j = sz(p)-1; ~j; j--)
      v = (v * 1ll * b[i] + p[j]) % mod;
    cout << r[i] << " " << v << "\t" << r[i] - v << endl;
  }
}