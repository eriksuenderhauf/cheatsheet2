#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// sum a+b*i from i = 1 to c
ll prog(ll a, ll b, ll c) {
  // for (ll i = 1; i <= c; i++)
  //   r += a + b * i;
  return c * a + b * c * (c + 1) / 2;
}

// sum (a+b*i)/c from i = 1 to d
ll sum(ll a, ll b, ll c, ll d) {
  // for (ll i = 1; i <= d; i++)
  //   r += (a + b * i) / c;
  if ((a + b * d) / c == 0 || d < 1)
    return 0;
  ll r = prog(a < 0 ? (a - c + 1) / c : a / c, b / c, d);
  if (b % c != 0) {
    a = (a % c + c) % c, b = (b % c + c) % c;
    r += sum((a + b * d) % c + b - c, c, b, (a + b * d) / c);
  }
  return r;
}

void solve() {
  ll n, m, a, b; cin >> n >> m >> a >> b;
  cout << sum(b, a, m, n-1) - (b/m) << "\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int t; cin >> t;
  while (t--)
    solve();
  return 0;
}
