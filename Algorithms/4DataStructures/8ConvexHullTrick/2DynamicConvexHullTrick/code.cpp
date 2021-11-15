typedef long long ll;
const ll inf = LLONG_MAX;

ll divide(ll a, ll b) {
  return a / b - ((a ^ b) < 0 && a % b);
}
// for doubles, use inf = 1.0 / 0 and div(a, b) = a / b

struct line {
  mutable ll a, b, r;
  bool operator<(const line & o) const {
    return a < o.a;
  }
  bool operator<(ll x) const {
    return r < x;
  }
};

struct convex_hull : multiset<line, less<>> {
  bool isect(iterator x, iterator y) {
    if (y == end()) {
      x->r = inf;
      return false;
    }
    if (x->a == y->a)
      x->r = x->b > y->b ? inf : -inf;
    else
      x->r = divide(y->b - x->b, x->a - y->a);
    return x->r >= y->r;
  }
  // add the line a * x + b to the convex hull
  void add(ll a, ll b) {
    auto y = insert({a, b, 0}), x = y++;
    while (isect(x, y))
      y = erase(y);
    if ((y = x) != begin() && isect(--x, y))
      isect(x, erase(y));
    while ((y = x) != begin() && (--x)->r >= y->r)
      isect(x, erase(y));
  }
  // query the maximal value at position x
  ll query(ll x) {
    auto l = *lower_bound(x);
    return l.a * x + l.b;
  }
};
