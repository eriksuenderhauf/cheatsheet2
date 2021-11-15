#include <bits/stdc++.h>

using namespace std;

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

void dfs(int x, vector<ll>& a, vector<ll>& b, vector<ll>& r, vector<vector<int>>& e, vector<convex_hull>& ch, int p = -1) {
  for (int y : e[x]) {
    if (y == p)
      continue;
    dfs(y, a, b, r, e, ch, x);
    if (ch[y].size() > ch[x].size())
      swap(ch[y], ch[x]);
    for (const line& l : ch[y])
      ch[x].add(l.a, l.b);
  }
  if (!ch[x].empty())
    r[x] = -ch[x].query(a[x]);
  ch[x].add(-b[x], -r[x]);
}

int main() {
  int n, x, y;
  cin >> n;
  vector<ll> a(n), b(n), r(n);
  vector<vector<int>> e(n);
  vector<convex_hull> ch(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  for (int i = 0; i < n - 1; i++) {
    cin >> x >> y, x--, y--;
    e[x].push_back(y);
    e[y].push_back(x);
  }
  dfs(0, a, b, r, e, ch);
  for (int i = 0; i < n; i++)
    cout << r[i] << (i < n - 1 ? " " : "\n");
}
