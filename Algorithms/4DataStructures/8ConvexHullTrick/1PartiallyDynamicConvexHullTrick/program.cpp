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
  int n, q, a, b, x;
  cin >> n >> q;
  convex_hull ch;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    ch.add(a, b);
  }
  for (int i = 0; i < q; i++) {
    cin >> x;
    cout << ch.query(x) << "\n";
  }
}
