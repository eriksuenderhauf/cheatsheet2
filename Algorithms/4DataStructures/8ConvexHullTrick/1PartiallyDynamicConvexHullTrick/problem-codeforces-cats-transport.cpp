#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = LLONG_MAX;

ll divide(ll a, ll b) {
  return a / b - ((a ^ b) < 0 && a % b);
}
// for doubles, use inf = 1.0 / 0 and div(a, b) = a / b

// for non-increasing queries, use commented lines
struct line {
  ll a, b, r;
  // bool operator<(ll x) const {
  //   return r < x;
  // }
};

struct convex_hull : vector<line> {
  int p = 0;
  bool isect(line & x, line & y) {
    if (x.a == y.a)
      x.r = x.b > y.b ? inf : -inf;
    else
      x.r = divide(y.b - x.b, x.a - y.a);
    return x.r >= y.r;
  }
  // add the line a * x + b to the convex hull, added lines must have increasing slope
  void add(ll a, ll b) {
    line l = {a, b, inf};
    if (size() - p > 0 && isect(back(), l))
      return;
    while (size() - p > 1 && (--(--end()))->r >= back().r)
      pop_back(), isect(back(), l);
    push_back(l);
  }
  // query the maximal value at position x
  ll query(ll x) {
    while (x > at(p).r)
      p++;
    return at(p).a * x + at(p).b;
    // auto l = *lower_bound(begin(), end(), x);
    // return l.a * x + l.b;
  }
};

int main() {
  int n, m, p;
  cin >> n >> m >> p;
  vector<ll> d(n), h(m), t(m), s(m);
  for (int i = 1; i < n; i++)
    cin >> d[i], d[i] += d[i - 1];
  for (int i = 0; i < m; i++)
    cin >> h[i] >> t[i], h[i]--, t[i] -= d[h[i]];
  sort(t.begin(), t.end());
  s[0] = t[0];
  for (int i = 1; i < m; i++)
    s[i] = t[i] + s[i - 1];
  vector<convex_hull> ch(p + 1);
  for (int i = 0; i <= p; i++)
    ch[i].add(-1, 0);
  ll r;
  for (int i = 0; i < m; i++)
    for (int j = 1; j <= p; j++) {
      ll o = - s[i] + i * t[i] - ch[j - 1].query(t[i]);
      if (i < m - 1)
        ch[j].add(i, - s[i] - o);
      if (i == m - 1 && j == p)
        r = o;
    }
  cout << r << "\n";
}
