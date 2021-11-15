#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
using namespace std;
const int MOD = 998244353;
const int root = 15311432;
const int iroot = 469870224;
const int mxpw = 1 << 23;

int pw(int a, int b) {
  int r = 1;
  while (b)
    if (b & 1)
      r = (ll)r * (ll)a%MOD, b--;
    else
      a = (ll)a * (ll)a%MOD, b /= 2;
  return r;
}

void fft(vector<int>& x, bool inv) {
  int n = sz(x);
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n>>1;
    for (; j & bit; bit /= 2)
      j ^= bit;
    j ^= bit;
    if (i < j)
      swap(x[i], x[j]);
  }
  vector<int> tmp;
  int cw = inv ? iroot : root;
  for (int i = 2; i < mxpw; i *= 2) {
    cw = (ll)cw * (ll)cw % MOD;
    tmp.pb(cw);
  }
  int id = sz(tmp)-1;
  for (int i = 2; i <= n; i *= 2) {
    cw =  tmp[id--];
    for (int j = 0; j < n; j += i) {
      for (int k = j, w = 1; 2*(k-j) < i; k++) {
        int a = x[k], b = (ll)w * (ll)x[k+i/2]%MOD;
        x[k] = a+b-(a+b<MOD?0:MOD), x[k+i/2] = a-b+(a-b<0?MOD:0);
        w = (ll)w * (ll)cw % MOD;
      }
    }
  }
  if (inv) {
    n = pw(n, MOD-2);
    for (int& t: x)
      t = (ll)t * (ll)n % MOD;
  }
}

vector<int> mul(vector<int> x, vector<int> y) {
  int m = 1; while (m < max(sz(x), sz(y))) m *= 2;
  x.resize(m*2); y.resize(m*2);
  fft(x, 0), fft(y, 0);
  for (int i = 0; i < sz(x); i++)
    x[i] = (ll)x[i]*(ll)y[i]%MOD;
  fft(x, 1);
  return x;
}

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

vector<int> sub(vector<int> x, vector<int> y) {
  for (int i = 0; i < min(sz(x), sz(y)); i++)
    x[i] = x[i]-y[i]+(x[i]<y[i]?MOD:0);
  for (int i = sz(x); i < sz(y); i++)
    x.pb(y[i]==0?0:MOD-y[i]);
  return x;
}

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

int main() {
  int n, m; cin >> n >> m;
  vector<int> a(n+1,0), b(m+1,0);
  for (int i = 0; i <= n; i++) {
    cin >> a[i];
    if (b[i] < 0) b[i] += MOD;
  }
  for (int i = 0; i <= m; i++) {
    cin >> b[i];
    if (b[i] < 0) b[i] += MOD;
  }
  vector<int> d, r;
  divide(a, b, d, r);
  for (int i: d)
    cout << i << " ";
  cout << "\n";
  for (int i: r)
    cout << i << " ";
  cout << "\n";
  return 0;
}