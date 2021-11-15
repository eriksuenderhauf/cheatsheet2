struct persistent_segment_tree {
  struct data;
  struct operation;
  static data combine(data dl, data dr);
  static data calculate(operation o, data d);
  static operation merge(operation ot, operation ob);
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
