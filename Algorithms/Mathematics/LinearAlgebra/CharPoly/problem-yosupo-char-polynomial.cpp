#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
const int mod = 998244353;
using namespace std;

int pw(int x, int y) {
  int r = 1;
  for (; y; y /= 2, x = x * 1ll * x % mod)
    if (y & 1)
      r = x * 1ll * r % mod;
  return r;
}

vector<int> operator*(const vector<int>& x, const vector<int>& y) {
  vector<int> r(sz(x) + sz(y) - 1);
  for (int i = 0; i < sz(x); i++)
    for (int j = 0; j < sz(y); j++)
      r[i + j] = (r[i + j] + x[i] * 1ll * y[j]) % mod;
  return r;
}

vector<int> operator*(int x, vector<int> y) {
  for (int i = 0; i < sz(y); i++)
    y[i] = y[i] * 1ll * x % mod;
  return y;
}

vector<int> operator-(const vector<int>& x, const vector<int>& y) {
  vector<int> r = x;
  r.resize(max(sz(x), sz(y)));
  for (int i = 0; i < sz(y); i++)
    r[i] = (r[i] - y[i] + mod) % mod;
  return r;
}

void transform(vector<vector<int>>& a) {
  int n = sz(a);
  for (int j = 0; j + 2 < n; j++) {
    int i = j+2; while (i < n && a[i][j] == 0) i++;
    if (i == n) continue;
    if (a[j+1][j] == 0) {
      swap(a[i], a[j+1]);
      for (int k = 0; k < n; k++)
        swap(a[k][i], a[k][j+1]);
    }
    int v = pw(a[j+1][j], mod-2);
    for (int k = j+2; k < n; k++) {
      int u = a[k][j] * 1ll * v % mod;
      for (int l = 0; l < n; l++) {
        a[k][l] = (a[k][l] - u * 1ll * a[j+1][l]) % mod;
        a[k][l] += a[k][l] < 0 ? mod : 0;
        a[l][j+1] = (a[l][j+1] + u * 1ll * a[l][k]) % mod;
      }
    }
  }
}
vector<int> calc(vector<vector<int>>& a) {
  transform(a);
  int n = sz(a);
  vector<vector<int>> p(n+1); p[0] = {1};
  for (int k = 0; k < n; k++) {
    p[k+1] = vector<int>({!a[k][k] ? 0 : mod-a[k][k], 1}) * p[k];
    int v = 1;
    for (int i = 0; i < k; i++) {
      v = v * 1ll * a[k-i][k-i-1] % mod;
      p[k+1] = p[k+1] - (v * 1ll * a[k-i-1][k] % mod) * p[k-i-1];
    }
  }
  return p[n];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  vector<vector<int>> a(n, vector<int>(n, 0));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> a[i][j];
  auto p = calc(a);
  for (int i: p)
    cout << i << " ";
  cout << endl;
}