#include <bits/stdc++.h>

using namespace std;

#define ntype long long

const ntype inf = ((ntype) 1) << 60;

struct func {
  ntype a, b;
  ntype getV(ntype x) {
    return a * x + b;
  }
  bool operator<(func & o) {
    return a < o.a;
  }
  ntype getR(func & o) {
    if (a == o.a)
      return b > o.b ? inf : -inf;
    ntype d = b >= o.b ? 0 : o.a - a - 1;
    return (b - o.b - d) / (o.a - a);
  }
};

struct convexhullelement {
  bool q;
  mutable ntype r;
  func * f;
  bool operator<(const convexhullelement & o) const {
    if (!q && !o.q)
      return *f < *o.f;
    return r < o.r;
  }
};

struct convexhull : public multiset<convexhullelement> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end())
        return false;
      return y->f->getR(*z->f) == -inf;
    }
    auto x = prev(y);
    if (z == end())
      return x->f->getR(*y->f) == inf;
    return x->f->getR(*y->f) >= y->f->getR(*z->f);
  }
  void update(iterator y) {
    auto z = next(y);
    y->r = z == end() ? inf : y->f->getR(*z->f);
    if (y != begin())
      prev(y)->r = prev(y)->f->getR(*y->f);
  }
  // add a function to the convex hull
  void add(func * f) {
    convexhullelement e = {false, 0, f};
    auto y = insert(e);
    if (bad(y)) {
      erase(y);
      return;
    }
    while (next(y) != end() && bad(next(y)))
      erase(next(y));
    while (y != begin() && bad(prev(y)))
      erase(prev(y));
    update(y);
  }
  // get the function with maximum value at position p
  func * query(ntype p) {
    convexhullelement e = {true, p, 0};
    return lower_bound(e)->f;
  }
  ntype getV(ntype p) {
    func * f = query(p);
    return f->getV(p);
  }
};

#define MAXN 100000

int n;
func f[MAXN];
convexhull ch;

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> f[i].a >> f[i].b;
  for (int i = 0; i < n; i++)
    ch.add(&f[i]);
  int x;
  cin >> x;
  cout << ch.getV(x) << "\n";
}
