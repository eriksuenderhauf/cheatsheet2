#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct persistent_segment_tree {
  // data (sum and length of a segment)
  struct data {
    ll s = 0, l = 0;
  };
  // operation on the data (x -> a * x + b)
  struct operation {
    ll a = 1, b = 0;
  };
  // alternatively use typedefs for simpler data and operations
  // combine the data from different segments
  static data combine(data dl, data dr) {
    return {dl.s + dr.s, dl.l + dr.l};
  }
  // calculate the result of an operation on the data
  static data calculate(operation o, data d) {
    return {o.a * d.s + o.b * d.l, d.l};
  }
  // merge an operation onto another operation
  static operation merge(operation ot, operation ob) {
    return {ot.a * ob.a, ot.b + ot.a * ob.b};
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
  int n, q, v, l, r;
  char t;
  cin >> n >> q;
  vector<persistent_segment_tree::data> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i].s, a[i].l = 1;
  persistent_segment_tree pst(a);
  for (int i = 0; i < q; i++) {
    cin >> t;
    if (t == 'C') {
      cin >> l >> r >> v, l--;
      pst.apply(l, r, {1, v});
    } else if (t == 'Q') {
      cin >> l >> r, l--;
      ll s = pst.query(l, r).s;
      cout << s << "\n";
    } else if (t == 'H') {
      cin >> l >> r >> v, l--;
      ll s = pst.query(v, l, r).s;
      cout << s << "\n";
    } else {
      cin >> v;
      while (v < (int) pst.t.size() - 1)
        pst.t.pop_back();
    }
  }
}
