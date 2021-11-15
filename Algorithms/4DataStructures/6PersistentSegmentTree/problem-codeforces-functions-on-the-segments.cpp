#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct persistent_segment_tree {
  // data (sum and length of a segment)
  struct data {
    ll a = 0, b = 0;
  };
  // operation on the data (x -> a * x + b)
  struct operation {
    ll o = 0, a = 0, b = 0;
  };
  // alternatively use typedefs for simpler data and operations
  // combine the data from different segments
  static data combine(data dl, data dr) {
    return {dl.a + dr.a, dl.b + dr.b};
  }
  // calculate the result of an operation on the data
  static data calculate(operation o, data d) {
    if (!o.o)
      return d;
    return {o.a, o.b};
  }
  // merge an operation onto another operation
  static operation merge(operation ot, operation ob) {
    if (!ot.o)
      return ob;
    return ot;
  }
  struct node {
    node *l, *r;
    data t;
    operation o;
    node(node *l, node *r) : l(l), r(r) {
      t = combine(l->t, r->t);
    }
    node(data t) : t(t) {}
    node(node *l, node *r, data t, operation o) : l(l), r(r), t(t), o(o) {}
  };
  int n;
  vector<node*> t;
  persistent_segment_tree(vector<data> & a) : n(a.size()) {
    t.push_back(build(a, 0, n));
  }
  node* build(vector<data> & a, int l, int r) {
    if (l + 1 == r)
      return new node(a[l]);
    int m = (l + r) / 2;
    return new node(build(a, l, m), build(a, m, r));
  }
  data query(node *x, int l, int r, int xl, int xr) {
    if (l <= xl && xr <= r)
      return x->t;
    if (xr <= l || r <= xl)
      return data();
    int xm = (xl + xr) / 2;
    return calculate(x->o, combine(query(x->l, l, r, xl, xm), query(x->r, l, r, xm, xr)));
  }
  // query the data on the range [l, r[ for version v
  data query(int v, int l, int r) {
    return query(t[v], l, r, 0, n);
  }
  // query the data on the range [l, r[
  data query(int l, int r) {
    return query(t.back(), l, r, 0, n);
  }
  node* apply(node *x, int l, int r, operation o, int xl, int xr, operation xo) {
    if (l <= xl && xr <= r)
      return new node(x->l, x->r, calculate(merge(o, xo), x->t), merge(merge(o, xo), x->o));
    if (xr <= l || r <= xl)
      return new node(x->l, x->r, calculate(xo, x->t), merge(xo, x->o));
    int xm = (xl + xr) / 2;
    xo = merge(xo, x->o);
    return new node(apply(x->l, l, r, o, xl, xm, xo), apply(x->r, l, r, o, xm, xr, xo));
  }
  // apply an operation on the range [l, r[ for version v
  void apply(int v, int l, int r, operation o) {
    t.push_back(apply(t[v], l, r, o, 0, n, operation()));
  }
  // apply an operation on the range [l, r[
  void apply(int l, int r, operation o) {
    t.push_back(apply(t.back(), l, r, o, 0, n, operation()));
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  int n, q, l, r, x;
  cin >> n;
  vector<int> x1(n), x2(n), y1(n), a(n), b(n), y2(n);
  vector<pair<int, int>> e(2 * n);
  vector<persistent_segment_tree::data> d(n);
  for (int i = 0; i < n; i++) {
    cin >> x1[i] >> x2[i] >> y1[i] >> a[i] >> b[i] >> y2[i];
    d[i].b = y1[i];
    e[2 * i] = {x1[i], i};
    e[2 * i + 1] = {x2[i], i};
  }
  sort(e.begin(), e.end());
  persistent_segment_tree pst(d);
  for (int i = 0; i < 2 * n; i++) {
    int j = e[i].second;
    if (e[i].first == x1[j])
      pst.apply(j, j + 1, {1, a[j], b[j]});
    else
      pst.apply(j, j + 1, {1, 0, y2[j]});
  }
  cin >> q;
  ll y = 0;
  for (int i = 0; i < q; i++) {
    cin >> l >> r >> x, l--;
    x = (x + y) % 1000000000;
    int j = lower_bound(e.begin(), e.end(), make_pair(x, 0)) - e.begin();
    persistent_segment_tree::data f = pst.query(j, l, r);
    y = f.a * x + f.b;
    cout << y << "\n";
  }
}
