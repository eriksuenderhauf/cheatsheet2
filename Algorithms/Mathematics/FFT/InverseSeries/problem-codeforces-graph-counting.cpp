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

ll g(ll k) {
  return k * (3*k-1) / 2;
}

vector<int> mul(vector<int> x, vector<int> y) {
  fft(x, 0), fft(y, 0);
  for (int i = 0; i < sz(x); i++)
    x[i] = (ll)x[i]*(ll)y[i]%MOD;
  fft(x, 1);
  return x;
}

vector<int> inv(vector<int> x, int n) {
  vector<int> pol(1,1), cur(1,1);
  int c = 1, k = 1;
  for (; k <= n; k *= 2) {
    while (sz(pol) < 4*k)
      pol.push_back(0), cur.push_back(0);
    for (; c < 2*k; c++) pol[c] = c < sz(x) ? x[c] : 0;
    vector<int> tmp = mul(pol, cur);
    tmp[0] = 2 - tmp[0] + (2-tmp[0]<0 ? MOD : 0);
    for (int i = 1; i < 2*k; i++)
      tmp[i] = !tmp[i] ? 0 : MOD-tmp[i];
    for (int j = 2*k; j < 4*k; j++)
      tmp[j] = 0;
    cur = mul(cur, tmp);
  }
  while (sz(cur) > k) 
    cur.pop_back();
  return cur;
}

int main() {
  int n; cin >> n; n++;
  vector<int> pol(n+1,0);
  pol[0] = 1;
  for (int i = 0; g(i) <= n; i++)
    pol[g(i)] = (i&1?MOD-1:1);
  for (int i = 0; g(-i) <= n; i++)
    pol[g(-i)] = (i&1?MOD-1:1);
  pol = inv(pol, n);
  cout << (pol[n]-1+MOD) % MOD << "\n";
  return 0;
}