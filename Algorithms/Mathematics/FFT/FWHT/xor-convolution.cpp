#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
using namespace std;

const int mod = 998244353;

int pw(int x, int y) {
  int r = 1;
  for (; y; y /= 2, x = x * 1ll * x % mod)
    if (y & 1)
      r = r * 1ll * x % mod;
  return r;
}

void transform(int& u, int& v, int inv) {
  // xor
  tie(u, v) = make_pair(u+v >= mod ? u+v-mod : u+v, u-v < 0 ? u-v+mod : u-v);
  // and
  //if (inv)
  //  tie(u, v) = make_pair(v-u < 0 ? v-u+mod : v-u, u);
  //else
  //  tie(u, v) = make_pair(v, u+v >= mod ? u+v-mod : u+v);
  // or
  //if (inv)
  //  tie(u, v) = make_pair(v, u-v < 0 ? u-v+mod : u-v);
  //else
  //  tie(u, v) = make_pair(u+v >= mod ? u+v-mod : u+v, u);
}

void fwht(vector<int>& a, int inv = 0) {
  int n = sz(a); assert((n&-n) == n);
  for (int i = 2; i <= n; i *= 2)
    for (int j = 0; j < n; j += i)
      for (int k = j; k < j+i/2; k++)
        transform(a[k], a[k+i/2], inv);
  if (inv) { // only for xor
    n = pw(n, mod-2);
    for (int& i: a)
      i = i * 1ll * n % mod;
  }
}

vector<int> convolution(vector<int>& a, vector<int>& b) {
  fwht(a), fwht(b);
  for (int i = 0; i < (int)a.size(); i++)
    a[i] = a[i] * 1ll * b[i] % mod;
  fwht(a, 1);
  return a;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  n = 1 << n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  auto c = convolution(a, b);
  for (int i: c)
    cout << i << " ";
  cout << endl;
}